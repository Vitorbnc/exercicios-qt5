#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //O Qt exige que uma QMainWindow tenha pelo menos um Widget Central;
    QWidget *centralWidget = new QWidget();

    //É ao central widget que devemos adicionar o layout
    QHBoxLayout *hBox = new QHBoxLayout(centralWidget);
    // centralWidget->setLayout(hBox);

    this->setCentralWidget(centralWidget);
    lbDisplay = new QLabel("Aguardando início do treino...\n");
    lbDisplay->setAlignment(Qt::AlignTop);
    hBox->addWidget(lbDisplay);
    //"Esticar" o último widget adicionado
    hBox->addStretch(1);

    QVBoxLayout *vBox = new QVBoxLayout();
    hBox->addLayout(vBox);
    vBox->setAlignment(Qt::AlignTop);
    vBox->setSpacing(20);

    QString strId = "ID da Equipe";
    QString strRest = "Descanso (ms)";
    QString strCriar = "Criar";
    QString strStopAll = "Finalizar Todos os Treinos";
    strCount = "Total de Equipes Criadas: ";
    QString strLimpar = "Limpar Texto";
    QGroupBox *boxCarro = new QGroupBox("Equipe de Carro");
    QVBoxLayout *v = new QVBoxLayout();
    boxCarro->setLayout(v);

    v->addWidget(btnCriaCarro = new QPushButton(strCriar));
    v->addWidget(new QLabel(strId));
    v->addWidget(inIdCarro=new QLineEdit());
    v->addWidget(new QLabel(strRest));
    v->addWidget(inRestCarro=new QLineEdit());

    QGroupBox *boxMoto = new QGroupBox("Equipe de Moto");
    //Como os ponteiros são passados por valor, é seguro reutilizar v
    //Isto é, passamos para as funções anteriores só valor do endereço de memória apontado pela variável
    v = new QVBoxLayout();
    boxMoto->setLayout(v);

    v->addWidget(btnCriaMoto = new QPushButton(strCriar));
    v->addWidget(new QLabel(strId));
    v->addWidget(inIdMoto=new QLineEdit());
    v->addWidget(new QLabel(strRest));
    v->addWidget(inRestMoto=new QLineEdit());

    vBox->setMargin(20);
    vBox->addWidget(boxCarro);
    vBox->addWidget(boxMoto);
    vBox->addWidget(lbCount = new QLabel(strCount));
    vBox->addWidget(btnStopAll = new QPushButton(strStopAll));
    QPushButton *btnLimpar = new QPushButton(strLimpar);
    vBox->addWidget(btnLimpar);

    connect(btnStopAll,&QPushButton::clicked,this,&MainWindow::stopAll);
    connect(btnCriaMoto,&QPushButton::clicked,this,&MainWindow::criarMoto);
    connect(btnCriaCarro,&QPushButton::clicked,this,&MainWindow::criarCarro);
    connect(btnLimpar, &QPushButton::clicked,this,[&](){this->lbDisplay->setText("");});

    inIdMoto->setText("1");
    inIdCarro->setText("1");
    inRestMoto->setText("10000");
    inRestCarro->setText("10000");

}

void MainWindow::updateVehicleCount(){
    QString s="";
    s.append(strCount).append(QString::number(Vehicle::getCount()));
    lbCount->setText(s);
}

void MainWindow::criarCarro(){
   // QMessageBox::information(this,"carro","click");

    Carro *m =new Carro(inIdCarro->text(),inRestCarro->text().toInt());
    connect(m,&Vehicle::sendMsg,this,&MainWindow::vehicleMsg);
    vehicles.push_back(m);
    m->init();

    QThreadPool::globalInstance()->start(m);
    inIdCarro->setText(QString::number(inIdCarro->text().toInt()+1));
    updateVehicleCount();

}
void MainWindow::criarMoto(){

    Moto *m =new Moto(inIdMoto->text(),inRestMoto->text().toInt());
    connect(m,&Vehicle::sendMsg,this,&MainWindow::vehicleMsg);
    vehicles.push_back(m);
    m->init();

     QThreadPool::globalInstance()->start(m);
     inIdMoto->setText(QString::number(inIdMoto->text().toInt()+1));
     updateVehicleCount();

}
void MainWindow::stopAll(){
    for(Vehicle *v:vehicles)
        if(v!=nullptr) v->requestAbort();
    vehicles.clear();
}


void MainWindow::vehicleMsg(QString msg){
    lbDisplay->setText(lbDisplay->text().append(msg));
    updateVehicleCount();
}

MainWindow::~MainWindow()
{
}

