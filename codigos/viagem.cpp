#include "../headers/viagem.h"


Viagem::Viagem(int id, Cidade* destino, Transporte* transporte, list<Passageiro*> passageirosV, list<Cidade*> cidades) : viagemId(id), passageiros(passageirosV), transporte(transporte), cidades(cidades) , destino(destino) {
    origem = *cidades.begin();
    this->status = false;
    this->resultado = false;
    kmRodados = 0;
}

void Viagem::avancarTempo(int tempo){
  if(tempoRestante <= tempo){
    this->tempoRestante = 0;
    this->tempoCorrido = (this->distanciaTotal/transporte->getVelocidade() + (distanciaTotal/transporte->getDistanciaDescanso()) * transporte->getTempoDescanso());
    return;
  }
  this->tempoRestante -= tempo;
  this->tempoCorrido += tempo;
}

int Viagem::getViagemId(){
  return viagemId;
}

void Viagem::setResultado(bool result){
  this->resultado = result;
}

void Viagem::setStatus(bool result){
  this->status = result;
}

bool Viagem::getResultado(){
  return resultado;
}

bool Viagem::getStatus(){
  return status;
}

