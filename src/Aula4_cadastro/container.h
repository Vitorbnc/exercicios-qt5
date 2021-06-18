#ifndef CONTAINER_H
#define CONTAINER_H

#include "libCadastro/pessoa.h"
#include <QVector>


class Container
{
public:
    Container();
    static QVector<Pessoa*> pessoas;
};

#endif // CONTAINER_H
