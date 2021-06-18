#include "professor.h"

            //Construtores com lista de inicialização
            Professor::Professor(std::string nome, int idade, std::string formacao):Pessoa(nome,idade,PROF),formacao(formacao){}
            Professor::Professor(std::string nome, int idade):Pessoa(nome,idade,PROF){}

void        Professor::definirFormacao(std::string formacao){
    this->formacao = formacao;
}
std::string Professor::retornarFormacao(){
    return this->formacao;
}