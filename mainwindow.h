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


private slots:
    void digitalClockDisplay();
    void timerDisplay();
    void stopWatchDisplay();


private:
    Ui::MainWindow *ui;

    SleepTimer *_sleep;

};

#endif // MAINWINDOW_H
