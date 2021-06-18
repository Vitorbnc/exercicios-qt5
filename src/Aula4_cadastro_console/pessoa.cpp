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
/**
**Provi a implementação básica do método para que o compilador não acuse erro ao *tentarmos fazer uma chamada polimórfica.Como o método é virtual, o compilador 
*chamará a versão da subclasse se ele for sobreescrito.
**Por exemplo, para que possamos fazer o seguinte:
Pessoa p = new Aluno();
p.retornarCurso();
**Sem a implementação aqui, isso geraria um erro de método puramente virtual.
*/
std::string Pessoa::retornarCurso(){return "";};
std::string Pessoa::retornarFormacao(){return "";};