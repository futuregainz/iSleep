#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _sleep = new SleepTimer();
    ui->mainLayout->addWidget(_sleep);

    connect(ui->sleepTimerButton, &QPushButton::clicked, this, &MainWindow::timerDisplay);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->digitalClockButton, &QPushButton::clicked, this, &MainWindow::digitalClockDisplay);
    connect(ui->stopWatchButton, &QPushButton::clicked, this, &MainWindow::stopWatchDisplay);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _sleep;
}

void MainWindow::digitalClockDisplay()
{
    _sleep->setLableDisplay(SleepTimer::clock);
}

void MainWindow::timerDisplay()
{
    _sleep->setLableDisplay(SleepTimer::timer);
}

void MainWindow::stopWatchDisplay()
{
    _sleep->setLableDisplay(SleepTimer::stopw);
}


