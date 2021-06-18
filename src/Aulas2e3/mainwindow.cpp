#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Manter o alinhamento dos botões mesmo quando eles estiverem ocultos
    //O comportamento padrão com layout é que eles se expandam
    QSizePolicy retain = ui->btn1->sizePolicy();
    retain.setRetainSizeWhenHidden(true);
    ui->btn1->setSizePolicy(retain);
    ui->btn2->setSizePolicy(retain);
    ui->btn3->setSizePolicy(retain);


    labelOpacity = new QGraphicsOpacityEffect(this);

    ui->label->setGraphicsEffect(labelOpacity);
    ui->label->setAutoFillBackground(true);


    //Mostrando aqui uma forma alternativa para reagir a eventos simples
    //Conectamos o sinal "toggled" do radioBtn a uma função lambda
    //lambda c++11: [ "="( captura por valor) ou "&"(cap. ref.)](opcional, parametros){corpo} -> int (opcion. valor de retorno)
    QObject::connect(ui->radio1,&QRadioButton::toggled,ui->btn1,[=]{ui->btn1->setHidden(ui->radio1->isChecked());});
    QObject::connect(ui->radio2,&QRadioButton::toggled,ui->btn2,[=]{ui->btn2->setHidden(ui->radio2->isChecked());});
    QObject::connect(ui->radio3,&QRadioButton::toggled,ui->btn3,[=]{ui->btn3->setHidden(ui->radio3->isChecked());});



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_slider_valueChanged(int value)
{
    labelOpacity->setOpacity(value/100.0);

}

void MainWindow::on_chkBlue_toggled(bool checked)
{
    ui->label->setStyleSheet((checked?"color:blue":"color:red"));
}

void MainWindow::on_chkTam_toggled(bool checked)
{
    QFont font = ui->label->font();
    font.setPointSize(checked?12:22);
    ui->label->setFont(font);
}

void MainWindow::on_chkBold_toggled(bool checked)
{
    QFont font = ui->label->font();
    font.setBold(checked);
    ui->label->setFont(font);
}
