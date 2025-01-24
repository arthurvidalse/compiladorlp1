#ifndef VIAGEM_H
#define VIAGEM_H

#include "../headers/sistema.h"
#include <list>

class Passageiro;
class Trajeto;
class Transporte;
class Cidade;

class Viagem{
  private:
    bool resultado; // true = finalizada, false = acontecendo ou esperando
    bool status; // true = em transito, false = esperando iniciar
    int viagemId;
  

  public:
    Viagem(int id, Cidade* destino, Transporte* transporte, list<Passageiro*> passageirosV,list<Cidade*> cidades);

    list<Passageiro*> passageiros;
    Transporte* transporte;
    list<Trajeto*> trajetos;
    list<Cidade*> cidades;
    int distanciaTotal;
    int kmRodados;
    Cidade* origem;
    Cidade* destino;
    int tempoCorrido;
    int tempoRestante;

    void avancarTempo(int tempo);
    int getViagemId();
    void setResultado(bool result);
    void setStatus(bool result);
    bool getResultado();
    bool getStatus();
};


#endif