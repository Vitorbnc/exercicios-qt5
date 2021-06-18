#ifndef PESSOA_H
#define PESSOA_H
#include<string>

enum Tipo{GERAL,ALUNO,PROF};

class Pessoa{
    protected:
    std::string nome;
    int idade;
    Tipo tipo;


    public:
    Pessoa (std::string nome, int idade, Tipo tipo);
    void definirNome(std::string nome);
    std::string retornarNome();
    void definirIdade(int idade);
    int retornarIdade();
    //Adicionei o Tipo para definir se é aluno ou prof ou qualquer outra coisa
    Tipo retornarTipo();

    virtual std::string retornarCurso();
    virtual std::string retornarFormacao();



};

#endif