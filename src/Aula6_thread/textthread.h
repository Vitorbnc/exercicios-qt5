#ifndef TEXTTHREAD_H
#define TEXTTHREAD_H
#include <QThread>


class TextThread : public QThread
{
    Q_OBJECT

public:
    TextThread(int threadId);
    void run() override;
    //Funções inline, já que são bem simples
    void resume(){pauseRequested = false;}
    void pause(){pauseRequested = true;}

signals:
    void resultReady(const QString &s); //emite atualizações periódicas da execução
    void finished();

private:
    int id;
    bool pauseRequested;
};

#endif // TEXTTHREAD_H
