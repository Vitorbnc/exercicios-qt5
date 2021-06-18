/*
Autor: Vitor Barbosa 
vitorbarbosanc at gmail
Compile este código com g++ main.cpp aluno.cpp pessoa.cpp professor.cpp* -o main.exe
Ou simplesmente: g++ *.cpp -o main.exe
*/
#include <iostream>
//Para usar a função toupper() do C
#include <ctype.h>
#include "pessoa.h"
#include "aluno.h"
#include "professor.h"
#include <typeinfo>

//O std::vector permite acesso aleatório. A std::list não, mas tem inserção e remoção em tempo constante
//O std::array é como o vector, mas tem tamanho fixo

#include<vector>

using namespace std;

int main (int argc, char **argv){

    //É obrigatório que o vetor armazene os ponteiros 
    // Em c++, se você armazenar uma cópia da subclasse numa variável do tipo superclasse, ocorre o problema de slicing
    // O slicing consiste na perda das partes da subclasse. Só o que é da superclasse vai ser armazenado
    // Isso pode ser resolvido se armazenarmos os ponteiros para a subclasse na variável do tipo da superclasse
    vector<Pessoa*> pessoas;
    char opt;

    while(true){
        //Comandos para limpar o stdin. Sem eles, pode ficar algum caractere no buffer e as instruções serão impressas várias vezes
        cin.clear();
        fflush(stdin);

        cout<<"\nOla! Selecione uma opcao: \n";
        cout<<"A- Adicione aluno, P- Adicione professor, L- listar, S- Sair \n";
        cout<<"Ha "<<pessoas.size()<<" entradas\n";
        string nome;
        string extra;
        string opt_line;
        int idade ;
        getline(cin,opt_line);
        opt = opt_line[0];
        opt = toupper(opt);
        if(opt=='A'||opt=='P'){
            string s;
            cout<<"Digite o nome: \n";
            getline(cin,nome);
            cout<<"Digite a idade \n";
            getline(cin,s);
            bool except = false;
            try{idade = stoi(s);}catch(exception e){except = true;}
            if(idade<0||except) cout<<"Idade invalida \n";
            else if(opt=='A'){
                cout<<"Digite o curso: \n";
                cin>>extra;
                Aluno *a = new Aluno(nome,idade,extra);
                //cout<<a->retornarCurso();
                pessoas.push_back(a);
            }
            else{
                cout<<"Digite a formacao: \n";
                getline(cin,extra);
                Professor *prof = new Professor(nome,idade,extra);
                pessoas.push_back(prof);
            }
        }
        else if (opt=='L'){
            for(Pessoa *p :pessoas){
                cout<<"Nome: "<<p->retornarNome()<<endl;
                cout<<"Idade: "<<p->retornarIdade()<<endl;
                if(p->retornarTipo()==ALUNO){
                    cout<<"Eh um aluno."<<endl;
                    cout<<"Curso: "<<p->retornarCurso()<<endl;
                }
                else if (p->retornarTipo()==PROF){
                    cout<<"Eh um professor."<<endl;
                    cout<<"Formacao: "<<p->retornarFormacao()<<endl;
                } 
            }
        } 
        else if(opt=='S'){
            pessoas.clear();
            break;
        }
    }
    return 0;
}