#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _sleep = new SleepTimer();
    ui->mainLayout->addWidget(_sleep);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _sleep;
}

void MainWindow::digitalClock()
{
    _sleep->setLableDisplay(SleepTimer::clock);
}

void MainWindow::timerDisplay()
{
    _sleep->setLableDisplay(SleepTimer::timer);
}

void MainWindow::on_sleepTimerButton_clicked()
{
    timerDisplay();
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::exit(0);
}

void MainWindow::on_digitalClockButton_clicked()
{
    digitalClock();
    //QDate cd = QDate::currentDate();
    //QTime ct = QTime::currentTime();
}

void MainWindow::on_stopWatchButton_clicked()
{
    _sleep->setLableDisplay(SleepTimer::stopw);
}

