#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "pessoa.h"

class Professor: public Pessoa{

private:
std::string formacao;

public:
            Professor(std::string nome, int idade, std::string formacao);
            Professor(std::string nome, int idade);

void        definirFormacao(std::string);
std::string retornarFormacao() override;


};

#endif