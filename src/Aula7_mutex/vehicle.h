#ifndef VEHICLE_H
#define VEHICLE_H
#include <QRunnable>
#include <QString>
#include <QSemaphore>
#include <QObject>


class Vehicle : public QObject,public QRunnable
{
    //Precisamos de um sinal para as threads
    Q_OBJECT
public:
    const static int MAX_COUNT = 5;
    Vehicle(QString equipe, int lapInterval_ms);
    virtual void run() = 0; //função puramente virtual, forçamos a implementação na subclasse
    void requestAbort(); // mata gentilmente a thread
    static int getCount(){return count;} //contagem de threads

    ~Vehicle();
protected:
    QString equipe;
    static QSemaphore sem;
    int lapInterval;
    bool abortRequested;
    static int count;
    virtual void finish()=0;

signals:
    void sendMsg(QString msg);

};

class Moto: public Vehicle{
public:
    Moto(QString equipe, int lapInterval_ms);
    const static int MAX_LAPS = 2;
    void run() override;
    void init();//chame para inicializar a classe após conectar seus sinais aos devidos slots
private:
    void finish(); //emite mensagem de término
};
class Carro: public Vehicle{
public:
    Carro(QString equipe, int lapInterval_ms);
    const static int MAX_LAPS = 3;
    void run() override;
    void init();//chame para inicializar a classe após conectar seus sinais aos devidos slots
private:
    void finish(); //emite mensagem de término
};

#endif // VEHICLE_H
