#ifndef DATABASE_H
#define DATABASE_H


#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <stdlib.h>


#include "../headers/sistema.h"
#include "../headers/cidade.h"
#include "../headers/passageiro.h"
#include "../headers/viagem.h"


class Transporte;
class Cidade;
class Trajeto;
class Passageiro;
class Viagem;


using std::vector;
using std::stoi;
using std::stoi;
using std::fstream;
using std::ifstream;
using std::stringstream;


class Database{
  private:
    list<Cidade*> cidades;

  public:
    Database();
    int getTempo(string nomeArquivo);
    void setTempo(string nomeArquivo, int tempo);
    void setCidades(list<Cidade*> cidades);
    void salvarTransportes(string nomeArquivo, list<Transporte*> &transportes);
    void salvarCidades(string nomeArquivo, list<Cidade*> &cidades);
    void salvarTrajetos(string nomeArquivo, list<Trajeto*> &trajetos);
    void salvarViagens(string nomeArquivo, list<Viagem*> &viagens);
    void addTrajeto(string nomeArquivo, Trajeto* &trajeto);
    void addCidade(string nomeArquivo, Cidade* &cidade);
    void salvarPassageiros(string nomeArquivo, list<Passageiro*> passageiros);

    // carregar
    list<Cidade*> carregarCidades(string nomeArquivo);
    list<Transporte*> carregarTransportes(string nomeArquivo);
    list<Trajeto*> carregarTrajetos(string nomeArquivo);
    list<Viagem*> carregarViagens(string nomeArquivo);
    list<Passageiro*> carregarPassageiros(string nomeArquivo);

};

#endif