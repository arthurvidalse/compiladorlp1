#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include "../headers/cidade.h"
#include "../headers/viagem.h"
#include <string>
#include <list>

class Viagem;
class Cidade;


class Passageiro {
private:
    int cpf;
    std::string nome;
    list<Viagem*> viagens;
    bool emTransito;
    Cidade* cidadeAtual;

public:
    // Construtor
    Passageiro(string nome, Cidade* cidade);
    Viagem* viagemAtual;

    // Getters
    string getNome() ;
    Cidade* getCidadeAtual();
    string getCidadeOrigem() ;
    string getCidadeDestino() ;
    bool getEmTransito() ;
    list<Viagem*> getViagens();
    int getCpf();
    
    // Setters
    void setNome(string& nome);
    void setCidadeAtual(Cidade* cidadeAtual);
    void setEmTransito(bool emTransito);
    void setCpf(int cpf);
    void addViagem(Viagem* viagem);
;
};

#endif
