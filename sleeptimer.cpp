#include "sleeptimer.h"
#include "ui_sleeptimer.h"

SleepTimer::SleepTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SleepTimer)
{
    ui->setupUi(this);
    _counterUpdate = new QTimer(this);
    _counterUpdate->start(1000);
    connect(_counterUpdate, &QTimer::timeout, this, &SleepTimer::updateDisplay);
}

SleepTimer::~SleepTimer()
{
    delete ui;
}

void SleepTimer::sendSleepSingals()
{
    _timer->stop();
    _counterUpdate->stop();
    ui->startTimer->setEnabled(true);
    ui->amountToSleep->setEnabled(true);
    system("pmset sleepnow");
}

void SleepTimer::updateDisplay()
{
    switch (buttonClicked)
    {
    case clock:
        ui->counter->setText(QTime::currentTime().toString("HH:mm:ss"));
        break;
    case timer:
        ui->counter->setText(remainingTime());
        break;
    case stopw:
        ui->counter->setText("00:00:00");
        break;
    default:
        ui->counter->setText("00:00:00");
        break;
    }
}

void SleepTimer::on_startTimer_clicked()
{
    bool valid = false;
    count = ui->amountToSleep->text().trimmed().toInt(&valid);
    buttonClicked = timer;

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

    ui->counter->setText(remainingTime());

    connect(_timer, &QTimer::timeout, this, &SleepTimer::sendSleepSingals);
    ui->startTimer->setEnabled(false);
    ui->amountToSleep->setEnabled(false);
}

void SleepTimer::on_cancelSleeper_clicked()
{
    if (_timer)
        _timer->stop();

    if (_counterUpdate)
    _counterUpdate->stop();

    ui->amountToSleep->setEnabled(true);
    ui->startTimer->setEnabled(true);
}

QString SleepTimer::remainingTime()
{
    if (!_timer)
        return "00:00:00";

    QString writeTime;
    int miliseconds = _timer->remainingTime();
    QTime time(0,0,0,0);
    time = time.addMSecs(miliseconds);

    // if less than 60 seconds
    if (miliseconds < secToMiliSecs)
    {
        writeTime = "00:00:" + prependZero(time.second());
    }
    else if (miliseconds < minToMiliSecs)
    {
        writeTime = "00:" + prependZero(time.minute()) + ":" + prependZero(time.second());
    }
    else //longer than one hour
    {
        writeTime = prependZero(time.hour()) + ":" + prependZero(time.minute()) + ":" + prependZero(time.second());
    }

    return writeTime;
}

void SleepTimer::setLableDisplay(const int &disType)
{
    if (!_counterUpdate->isActive())
        _counterUpdate->start();

    buttonClicked = disType;

    switch (buttonClicked)
    {
    case clock:
        ui->counter->setText(QTime::currentTime().toString("HH:mm:ss"));
        ui->controls->setVisible(false);
        break;
    case timer:
        ui->counter->setText(remainingTime());
        ui->controls->setVisible(true);
        ui->label->setVisible(true);
        ui->amountToSleep->setVisible(true);
        break;
    case stopw:
        ui->controls->setVisible(true);
        ui->label->setVisible(false);
        ui->amountToSleep->setVisible(false);
        ui->counter->setText("00:00:00");
        break;
    default:
        ui->counter->setText("00:00:00");
        break;
    }
}

QString SleepTimer::prependZero(int val)
{
    return (val < 10)? "0" + QString::number(val) : QString::number(val);
}

