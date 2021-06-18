#include<string>
#include "pessoa.h"

Pessoa::Pessoa (std::string nome, int idade,Tipo tipo):nome(nome),idade(idade),tipo(tipo){}


void Pessoa::definirNome(std::string nome){
    this->nome = nome;
}

std::string Pessoa::retornarNome(){
    return this->nome;
}


void Pessoa::definirIdade(int idade){
    //Lançar exceção se a idade for negativa
    if(idade<0) throw "Idade negativa";
    this->idade = idade;
}

int  Pessoa::retornarIdade(){
    return this->idade;
}

Tipo Pessoa::retornarTipo(){
    return this->tipo;
}

std::string Pessoa::retornarCurso(){return "";};
std::string Pessoa::retornarFormacao(){return "";};