#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "textthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCreate1_clicked();
    void on_btnSuspend1_clicked();
    void on_btnActivate1_clicked();
    void on_btnFinish1_clicked();
    void on_btnCreate2_clicked();
    void on_btnSuspend2_clicked();
    void on_btnActivate2_clicked();
    void on_btnFinish2_clicked();

private:
    Ui::MainWindow *ui;
    TextThread *thread1;
    TextThread *thread2;

    void handleThreadResult(QString result);
    void disableGroup(int group);
};
#endif // MAINWINDOW_H
