#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace  std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread1 = new TextThread(1);
    thread2 = new TextThread(2);

    connect(thread1,&TextThread::resultReady,this,&MainWindow::handleThreadResult);
    connect(thread2, &TextThread::resultReady,this,&MainWindow::handleThreadResult);

    //Recomendado pela Documentação do Qt. Marca a Thread para deleção após a execução
    connect(thread1,&TextThread::finished,this,&QObject::deleteLater);
    connect(thread2,&TextThread::finished,this,&QObject::deleteLater);
    //connect(ui->btnCreate1,&QPushButton::clicked,this,[&](){this->thread1->start();});


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleThreadResult(QString result){
    QString lastTxt = ui->textEdit->toPlainText();
    ui->textEdit->setText(lastTxt.append(result));

}
void MainWindow::disableGroup(int groupId){
    //Armazenamos os botões num array bidimensional para desabilitar vários de uma vez
    QPushButton* arr[2][4] = {{(ui->btnCreate1),(ui->btnSuspend1),(ui->btnActivate1),(ui->btnFinish1)},
                              {(ui->btnCreate2),(ui->btnSuspend2),(ui->btnActivate2),(ui->btnFinish2)}};

    //Desabilita uma coluna inteira do array
    for(QPushButton* btn:arr[groupId-1])
        btn->setEnabled(false);
}

void MainWindow::on_btnCreate1_clicked()
{
    thread1->start();
    disableGroup(1);
    ui->btnSuspend1->setEnabled(true);
    ui->btnFinish1->setEnabled(true);
}

void MainWindow::on_btnSuspend1_clicked()
{
    thread1->pause();
    disableGroup(1);
    ui->btnActivate1->setEnabled(true);
    ui->btnFinish1->setEnabled(true);
}

void MainWindow::on_btnActivate1_clicked()
{
    thread1->resume();
    disableGroup(1);
    ui->btnSuspend1->setEnabled(true);
    ui->btnFinish1->setEnabled(true);
}

void MainWindow::on_btnFinish1_clicked()
{
    thread1->requestInterruption();
    disableGroup(1);
    ui->btnCreate1->setEnabled(true);
}
void MainWindow::on_btnCreate2_clicked()
{
    thread2->start();
    disableGroup(2);
    ui->btnSuspend2->setEnabled(true);
    ui->btnFinish2->setEnabled(true);
}

void MainWindow::on_btnSuspend2_clicked()
{
    thread2->pause();
    disableGroup(2);
    ui->btnActivate2->setEnabled(true);
    ui->btnFinish2->setEnabled(true);
}

void MainWindow::on_btnActivate2_clicked()
{
    thread2->resume();
    disableGroup(2);
    ui->btnSuspend2->setEnabled(true);
    ui->btnFinish2->setEnabled(true);
}

void MainWindow::on_btnFinish2_clicked()
{
    thread2->requestInterruption();
    disableGroup(2);
    ui->btnCreate2->setEnabled(true);
}
