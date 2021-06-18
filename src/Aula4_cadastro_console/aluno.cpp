#include "aluno.h"

            //Este construtor inicializa a superclasse e a subclasse usando uma lista de inicialização
            Aluno::Aluno(std::string nome, int idade, std::string curso):Pessoa(nome, idade,ALUNO),curso(curso){}
            Aluno::Aluno(std::string nome, int idade):Pessoa(nome,idade,ALUNO){}

            
void Aluno::definirCurso(std::string curso){
    this->curso = curso;
}
std::string Aluno::retornarCurso() {
    return this->curso;
}