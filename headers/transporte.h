#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include "../headers/cidade.h"

using std::string;

class Cidade;

class Transporte {
private:
    string nome;
    string tipo;
    int capacidade;
    int velocidade;
    int distanciaDescanso;
    int tempoDescanso;
    Cidade* localAtual;
    Cidade* cidadeAtual; 
    bool emTransito;
    Cidade* destino;
public:
    Transporte(int indiceT, string nome, string tipo, int capacidade, int velocidade, int distanciaDescanso, int tempoDescanso, Cidade* localAtual);

    int indiceT;
    void partir();
    void chegar(Cidade* destino);

    string getNome();
    string getTipo();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaDescanso();
    int getTempoDescanso();
    Cidade* getCidade();
    Cidade* getCidadeAtual();
    Cidade* getDestino();
    bool getEmTransito();
    


    void setNome(string nome);
    void setTipo(string tipo);
    void setCapacidade(int capacidade);
    void setVelocidade(int velocidade);
    void setDistanciaDescanso(int distanciaDescanso);
    void setTempoDescanso(int tempoDescanso);
    void setCidade(Cidade* cidade);
    void setDestino(Cidade* cidade);
    void setEmTransito(bool emTransito);
};

#endif
