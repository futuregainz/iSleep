#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QChart>
#include <QResizeEvent>
#include <QMessageBox>
#include <QTime>
#include <QDate>

namespace Ui {
class SleepTimer;
}

class SleepTimer : public QWidget
{
    Q_OBJECT

public:
    explicit SleepTimer(QWidget *parent = nullptr);
    ~SleepTimer();

    const int miliSectoCen = 100;
    const int milisecToSec = 1000;
    const int milisecToMin = milisecToSec * 60;
    const int milisecsTohour = milisecToMin * 60;
    const int _24hours = 24 * milisecsTohour;

    QString prependZero(int val);
    void setLableDisplay(int const &disType);

    enum { clock, timer, stopw } displayType;


public slots:
    void sendSleepSingals();
    void updateDisplay();


private slots:
    void on_cancelSleeper_clicked();
    void on_startTimer_clicked();
    void on_stopWatchStart_clicked();
    void on_stopWatchStop_clicked();

private:
    Ui::SleepTimer *ui;

    //void disableTimerButtons(bool enabled);

    QString remainingTime(int miliseconds);

    QTimer *_timer = nullptr;
    QTimer *_counterUpdate = nullptr;
    QTimer *_stopTimer = nullptr;

    int buttonClicked = -1;
    int count;
};

#endif // SLEEPTIMER_H
