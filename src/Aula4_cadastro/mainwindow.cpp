#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newentry.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    janelaCadastro = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    //Não use delete ou o programa vai dar crash, o Qt já gerencia a memória de forma transparente
    //if(janelaCadastro!=nullptr) delete janelaCadastro;

    //MUITO IMPORTANTE
    //Precisamos passar o endereço de memória do nosso vetor de pessoas, para que ele seja modificado pela outra janela
    //Use ponteiros sempre que possível, e evite variáveis referência. Ex.: use Pessoa *p em vez de Pessoa &p
    janelaCadastro = new newEntry(this,&(this->pessoas));
    janelaCadastro->show();
    this->hide();

}


void MainWindow::updateList(){
    ui->listWidget->clear();
    for(Pessoa *p: pessoas){
        ui->listWidget->addItem((QString::fromStdString(p->retornarNome())));
    }
}

void MainWindow::changeEvent(QEvent *e){

    QWidget::changeEvent(e);

    if(e->type()==QEvent::ActivationChange)
        if(this->isActiveWindow()){
            //QTextStQTextStream(stdout)
           // QMessageBox::information(this,"Info","Active");
            updateList();

        }


}

void MainWindow::on_btnDelete_clicked()
{
    if(!pessoas.isEmpty())
        pessoas.pop_back(),updateList();
}

void MainWindow::on_btnClean_clicked()
{
    if(!pessoas.isEmpty())
        pessoas.clear(),updateList();
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    //Limite o índice ou teremos um bug ao acessar o vetor
    currentRow = currentRow>(pessoas.size()-1)? 0 : (currentRow<0? 0:currentRow);

    Pessoa* p = pessoas.at(currentRow);
    ui->labelAge->setText(QString::number(pessoas.at(currentRow)->retornarIdade()));
    if(p->retornarTipo()==PROF){
        ui->labelExtraTitle->setText("Prof. Formação:  ");
        ui->labelExtra->setText(QString::fromStdString(p->retornarFormacao()));
    }
    else if(p->retornarTipo()==ALUNO){
        ui->labelExtraTitle->setText("Aluno. Curso:    ");
        ui->labelExtra->setText(QString::fromStdString(p->retornarCurso()));

    }
}
