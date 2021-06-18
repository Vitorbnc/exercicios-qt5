#ifndef NEWENTRY_H
#define NEWENTRY_H

#include <QDialog>
#include "libCadastro/aluno.h"
#include "libCadastro/professor.h"
#include <QMessageBox>

namespace Ui {
class newEntry;
}

class newEntry : public QDialog
{
    Q_OBJECT

public:
    newEntry(QWidget *parent, QVector<Pessoa*> *pessoas);
    ~newEntry();

private slots:


    void on_btnOK_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::newEntry *ui;
    QWidget *parent;
    QVector <Pessoa*> *pessoas;

    void init();

    void goBack();

};

#endif // NEWENTRY_H
