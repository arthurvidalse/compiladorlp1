#include "../headers/passageiro.h"

//utor
Passageiro::Passageiro(string nome, Cidade* cidade) : nome(nome), cidadeAtual(cidade){
    this->emTransito = false;
}

// Getters
string Passageiro::getNome(){
    return nome;
}

Cidade* Passageiro::getCidadeAtual() {
    return cidadeAtual;
}

string Passageiro::getCidadeOrigem(){
    if(emTransito){
        return viagemAtual->origem->getNome();
    }
    return nullptr;
}

string Passageiro::getCidadeDestino(){
    if(emTransito){
        return viagemAtual->destino->getNome();
    }
    return nullptr;
}

bool Passageiro::getEmTransito(){
    return emTransito;
}

list<Viagem*> Passageiro::getViagens(){
    return viagens;
}

int Passageiro::getCpf(){
    return cpf;
}


// Setters
void Passageiro::setNome(string& nome) {
    this->nome = nome;
}

void Passageiro::setCidadeAtual(Cidade* cidadeAtual) {
    this->cidadeAtual = cidadeAtual;
}

void Passageiro::setEmTransito(bool emTransito) {
    this->emTransito = emTransito;
}

void Passageiro::setCpf(int cpf){
    this->cpf = cpf;
}

void Passageiro::addViagem(Viagem *viagem){
    this->viagens.push_back(viagem);
}