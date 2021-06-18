#ifndef ALUNO_H
#define ALUNO_H
#include <string>
#include "pessoa.h"

class Aluno: public Pessoa{

private:
std::string curso;

public:
            Aluno(std::string nome, int idade, std::string curso);
            Aluno(std::string nome, int idade);

void        definirCurso(std::string curso);
//O especificador override é opcional
std::string retornarCurso() override;

};

#endif
