#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QChart>
#include <QResizeEvent>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    const int secToMiliSecs = 1000 * 60;
    const int minToMiliSecs = 1000 * 60 * 60;

    QString prependZero(int val);
    QString remainingTime();


public slots:
    void sendSleepSingals();
    void updateDisplay();

private slots:
    void on_pushButton_clicked();
    void on_cancelSleeper_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *_timer = nullptr;
    QTimer *_counterUpdate = nullptr;

    int count;
};

#endif // MAINWINDOW_H
