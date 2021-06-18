#include <QApplication>
#include<QWidget>
#include <QLabel>

class Hello:public QWidget{
public:
    Hello(QWidget *parent = 0):QWidget(parent){
        QLabel *label  = new QLabel("Hello World!",this);
        label->setGeometry(75,50,100,50);
    }

};

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Hello window;
    window.show();
    window.resize(210,150);
    return app.exec();
}
