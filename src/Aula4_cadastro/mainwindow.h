#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newentry.h"
#include "libCadastro/aluno.h"
#include "libCadastro/professor.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnClean_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    newEntry *janelaCadastro;
    QVector<Pessoa*> pessoas;

    void updateList();

    void changeEvent(QEvent *event);

};
#endif // MAINWINDOW_H
