#include "../headers/transporte.h"
#include "../headers/cidade.h"


Transporte::Transporte(int indiceT, string nome, string tipo, int capacidade, int velocidade, int distanciaDescanso, int tempoDescanso, Cidade* localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), distanciaDescanso(distanciaDescanso), tempoDescanso(tempoDescanso), localAtual(localAtual), cidadeAtual(localAtual) ,indiceT(indiceT) {}

void Transporte::partir() {
    emTransito = true;

}

void Transporte::chegar(Cidade* destino) {
    this->cidadeAtual = destino;
    this->localAtual = destino;
    emTransito = false;
}

// Getters
string Transporte::getNome() {
    return nome;
}

string Transporte::getTipo() {
    return tipo;
}

int Transporte::getCapacidade() {
    return capacidade;
}

int Transporte::getVelocidade() {
    return velocidade;
}

int Transporte::getDistanciaDescanso() {
    return distanciaDescanso;
}

int Transporte::getTempoDescanso() {
    return tempoDescanso;
}

Cidade* Transporte::getCidade() {
    return localAtual;
}

Cidade* Transporte::getCidadeAtual() {
    return cidadeAtual;
}

Cidade* Transporte::getDestino() {
    return destino;
}

bool Transporte::getEmTransito(){
    return emTransito;
}


// Setters
void Transporte::setNome(string nome) {
    this->nome = nome;
}

void Transporte::setTipo(string tipo) {
    this->tipo = tipo;
}

void Transporte::setCapacidade(int capacidade) {
    this->capacidade = capacidade;
}

void Transporte::setVelocidade(int velocidade) {
    this->velocidade = velocidade;
}

void Transporte::setDistanciaDescanso(int distanciaDescanso) {
    this->distanciaDescanso = distanciaDescanso;
}

void Transporte::setTempoDescanso(int tempoDescanso) {
    this->tempoDescanso = tempoDescanso;
}

void Transporte::setCidade(Cidade* cidade) {
    this->localAtual = cidade;
    this->cidadeAtual = cidade; 
}

void Transporte::setDestino(Cidade* cidade) {
    this->destino = cidade;
}

void Transporte::setEmTransito(bool emTransito) {
    this->emTransito = emTransito;

}
