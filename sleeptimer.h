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

    const int secToMiliSecs = 1000 * 60;
    const int minToMiliSecs = 1000 * 60 * 60;

    QString prependZero(int val);
    QString remainingTime();
    void setLableDisplay(int const &disType);

    enum { clock, timer, stopw } displayType;


public slots:
    void sendSleepSingals();
    void updateDisplay();


private slots:
    void on_cancelSleeper_clicked();
    void on_startTimer_clicked();


private:
    Ui::SleepTimer *ui;

    QTimer *_timer = nullptr;
    QTimer *_counterUpdate = nullptr;
    QTimer *_stopTimer = nullptr;

    int buttonClicked = -1;
    int count;
};

#endif // SLEEPTIMER_H
