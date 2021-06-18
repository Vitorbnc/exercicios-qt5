#include "newentry.h"
#include "ui_newentry.h"
#include "container.h"

void newEntry::init(){
    QString strAluno = "Curso     ";
    QString strProf =  "Formação  ";

    QObject::connect(ui->radProf,&QRadioButton::toggled,this,[=]{
        ui->labelExtra->setText(ui->radProf->isChecked()?strProf:strAluno);});
}

// Note que pessoas precisa ser um ponteiro para um vetor de ponteiros de Pessoa
// Os ponteiros de Pessoa são para evitar o slicing (perda de dados ao passar um tipo subclasse para a superclasse
// O ponteiro para o vetor é porque desejamos modificar e repassar os dados no lugar
//Evite aramzenar referências, pois elas são confusas e causam erros
newEntry::newEntry(QWidget *parent,QVector<Pessoa*> *pessoas):QDialog(parent),
    ui(new Ui::newEntry),pessoas(pessoas){

    ui->setupUi(this);
    this->parent = parent;
   init();
   //QMessageBox::information(this,"Info","Pessoas passado");

}

newEntry::~newEntry()
{
    delete ui;
}

void newEntry::goBack(){
    this->close();
    parent->show();
}


void newEntry::on_btnOK_clicked()
{
    bool dadosOK = true;
    QString nome = ui->txtNome->toPlainText();
    int idade = ui->spinIdade->value();
    QString extra = ui->txtExtra->toPlainText();

    // Validando os dados
    if(nome.isEmpty()) dadosOK = false;
    if(dadosOK){
        if(ui->radAluno->isChecked())
            pessoas->push_back(new Aluno(nome.toStdString(),idade,extra.toStdString()));
        else if(ui->radProf->isChecked())
            pessoas->push_back(new Professor(nome.toStdString(),idade,extra.toStdString()));
    QMessageBox::about(this,QString::fromStdString(pessoas->last()->retornarNome()),"Cadastrado com Sucesso!");
    }
    else QMessageBox::warning(this,"Erro","O nome não pode estar em branco");

    if(dadosOK){
        goBack();
    }
}

void newEntry::on_btnCancelar_clicked()
{
    goBack();
}
