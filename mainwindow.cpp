#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _counterUpdate = new QTimer(this);
    connect(_counterUpdate, &QTimer::timeout, this, &MainWindow::updateDisplay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendSleepSingals()
{
    _timer->stop();
    _counterUpdate->stop();
    ui->pushButton->setEnabled(true);
    ui->amountToSleep->setEnabled(true);
    system("pmset sleepnow");
}

void MainWindow::updateDisplay()
{
    ui->counter->setText(remainingTime());
}

void MainWindow::on_pushButton_clicked()
{
    bool valid = false;
    count = ui->amountToSleep->text().trimmed().toInt(&valid);

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
    _counterUpdate->start(1000);
    _timer->start();

    updateDisplay();

    connect(_timer, &QTimer::timeout, this, &MainWindow::sendSleepSingals);
    ui->pushButton->setEnabled(false);
    ui->amountToSleep->setEnabled(false);
}

void MainWindow::on_cancelSleeper_clicked()
{
    if (_timer)
        _timer->stop();

    if (_counterUpdate)
        _counterUpdate->stop();

    ui->amountToSleep->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

QString MainWindow::remainingTime()
{
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

QString MainWindow::prependZero(int val)
{
    return (val < 10)? "0" + QString::number(val) : QString::number(val);
}

