#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>


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
    void on_slider_valueChanged(int value);

    void on_chkBlue_toggled(bool checked);

    void on_chkTam_toggled(bool checked);

    void on_chkBold_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *labelOpacity;
};
#endif // MAINWINDOW_H
