#include "sleeptimer.h"
#include "ui_sleeptimer.h"

SleepTimer::SleepTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SleepTimer)
{
    ui->setupUi(this);
    //_sleepAndWatchCounter = new QTimer(this);
    _watchCounter = new QTimer(this);
    _stopTimer = new QTimer(this);
    _timer = new QTimer(this);
    //connect(_sleepAndWatchCounter, &QTimer::timeout, this, &SleepTimer::updateDisplay);
    connect(_watchCounter, &QTimer::timeout, this, &SleepTimer::updateDisplay);
    ui->stopWatchStart->setVisible(false);
    ui->stopWatchStop->setVisible(false);
}

SleepTimer::~SleepTimer()
{
    delete ui;
}

void SleepTimer::sendSleepSingals()
{
    _timer->stop();
    //_sleepAndWatchCounter->stop();
    _watchCounter->stop();
    _stopTimer->stop();
    ui->startTimer->setEnabled(true);
    ui->amountToSleep->setEnabled(true);
    system("pmset sleepnow");
}

void SleepTimer::updateDisplay()
{
    switch (buttonClicked)
    {
    case clock:
        ui->counter->setText(QTime::currentTime().toString("HH:mm:ss.zzz"));
        break;
    case timer:
        if (_timer->isActive())
            ui->counter->setText(remainingTime(_timer->remainingTime()));
        break;
    case stopw:
        if (_stopTimer->isActive())
            ui->counter->setText(remainingTime(_24hours - _stopTimer->remainingTime()));
        break;
    default:
        break;
    }
}

void SleepTimer::on_startTimer_clicked()
{
    bool valid = false;
    count = ui->amountToSleep->text().trimmed().toInt(&valid);
    buttonClicked = timer;

    //if (!_sleepAndWatchCounter->isActive())
        //_sleepAndWatchCounter->start(1000);

    if (!valid)
    {
        QMessageBox::critical(this, "Invalid Entry", "Enter number of minutes!", QMessageBox::Ok);
        return;
    }

    if (_timer != nullptr)
        delete _timer;

    _timer = new QTimer(this);
    _timer->setInterval(count * 60000);
    _timer->setSingleShot(true);
    _timer->start();

    ui->counter->setText(remainingTime(_timer->remainingTime()));

    connect(_timer, &QTimer::timeout, this, &SleepTimer::sendSleepSingals);
    ui->startTimer->setEnabled(false);
    ui->amountToSleep->setEnabled(false);
}

void SleepTimer::on_cancelSleeper_clicked()
{
    if (_timer->isActive())
        _timer->stop();

    //if (_sleepAndWatchCounter->isActive())
        //_sleepAndWatchCounter->stop();

    ui->amountToSleep->setEnabled(true);
    ui->startTimer->setEnabled(true);
}

void SleepTimer::on_stopWatchStart_clicked()
{
    if (_stopTimer != nullptr)
        delete _stopTimer;

    if (!_watchCounter->isActive())
        _watchCounter->start(10);

    _stopTimer = new QTimer(this);

    _stopTimer->setInterval(_24hours);
    _stopTimer->setSingleShot(true);
    _stopTimer->start();

    ui->counter->setText(remainingTime(_24hours - _stopTimer->remainingTime()));
    ui->stopWatchStart->setEnabled(false);
}

void SleepTimer::on_stopWatchStop_clicked()
{
    if (_watchCounter->isActive())
        _watchCounter->stop();

    if (_stopTimer->isActive())
        _stopTimer->stop();

    ui->stopWatchStart->setEnabled(true);
}

QString SleepTimer::remainingTime(int miliseconds)
{
    QString writeTime;
    QTime time(0,0,0,0);
    time = time.addMSecs(miliseconds);

    // if less than 60 seconds
    if (miliseconds < milisecToMin)
    {
        writeTime = prependZero(time.second()) + "." + prependZero(time.msec());
    }
    else if (miliseconds < milisecsTohour)
    {
        writeTime = prependZero(time.minute()) + ":" + prependZero(time.second()) + "." + prependZero(time.msec());
    }
    else //longer than one hour
    {
        writeTime = prependZero(time.hour()) + ":" + prependZero(time.minute()) + ":" + prependZero(time.second()) + "." + prependZero(time.msec());
    }

    return writeTime;
}

void SleepTimer::setLableDisplay(const int &disType)
{

    buttonClicked = disType;

    switch (buttonClicked)
    {
    case clock:
        ui->counter->setText(QTime::currentTime().toString("HH:mm:ss.zzz"));
        ui->controls->setVisible(false);
        //_sleepAndWatchCounter->start(1000);
        _watchCounter->start(10);
        break;
    case timer:
        //if (_timer->isActive())
        ui->counter->setText(remainingTime(_timer->remainingTime()));

        //_sleepAndWatchCounter->start(1000);
        _watchCounter->start(10);
        ui->controls->setVisible(true);
        ui->label->setVisible(true);
        ui->amountToSleep->setVisible(true);
        ui->startTimer->setVisible(true);
        ui->cancelSleeper->setVisible(true);
        ui->stopWatchStart->setVisible(false);
        ui->stopWatchStop->setVisible(false);
        break;
    case stopw:
        //if (_stopTimer->isActive())
        ui->counter->setText(remainingTime(_24hours - _stopTimer->remainingTime()));

        _watchCounter->start(10);
        ui->controls->setVisible(true);
        ui->label->setVisible(false);
        ui->amountToSleep->setVisible(false);
        ui->startTimer->setVisible(false);
        ui->cancelSleeper->setVisible(false);
        ui->stopWatchStart->setVisible(true);
        ui->stopWatchStop->setVisible(true);
        break;
    default:
        break;
    }
}

QString SleepTimer::prependZero(int val)
{
    return (val < 10)? "0" + QString::number(val) : QString::number(val);
}

