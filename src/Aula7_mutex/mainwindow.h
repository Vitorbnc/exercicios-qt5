#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <vector>
#include "vehicle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void vehicleMsg(QString msg);
private:
    QLabel *lbDisplay, *lbCount;
    QLineEdit *inIdCarro, *inRestCarro, *inIdMoto, *inRestMoto;
    QPushButton *btnCriaCarro, *btnCriaMoto, *btnStopAll;
    QString strCount;


    std::vector<Vehicle *> vehicles;

    void criarMoto();
    void criarCarro();
    void stopAll();
    void updateVehicleCount();


};
#endif // MAINWINDOW_H
