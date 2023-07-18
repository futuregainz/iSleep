#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <sleeptimer.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void digitalClock();
    void timerDisplay();


private slots:
    void on_sleepTimerButton_clicked();
    void on_exitButton_clicked();
    void on_digitalClockButton_clicked();
    void on_stopWatchButton_clicked();


//protected:
//void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    SleepTimer *_sleep;
    QTimer *_timer;

};

#endif // MAINWINDOW_H
