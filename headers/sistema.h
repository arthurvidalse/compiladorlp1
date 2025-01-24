#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include "cidade.h"
#include "../database/database.h"
#include "../headers/trajeto.h"
#include "../headers/passageiro.h"
#include <queue>
#include <limits.h>
#include "../headers/transporte.h"

using std::vector;
using std::pair;
using std::greater;
using std::priority_queue;

class Cidade;
class Transporte;
class Database;

// struct para dijkstra
struct Edge {
    int destino;
    int distancia;
};

class Sistema {
private:

    list<Cidade*> cidades;
    list<Transporte*> transportes;
    list<Trajeto*> trajetos;
    list<Passageiro*> passageiros;
    list<Viagem*> viagens;
    int tempoCorrido;
    

public:
    // gerenciando sistema
    Sistema();
    void iniciar();
    void salvarDados();
    void limpar();
    void pressEnter();
    void telaSair();
    void calcularDia();
    void setTempoCorrido(int tempo);
    void avancarTempo(int tempo);
    void atualizarHora();

    // menu de cidades
    void menuGestaoCidades();
    void adicionarCidade();
    void menuAdicionarFronteiras();
    void adicionarFronteiras(Cidade* cidade);
    void listarCidades();
    void cidadesMaisVisitadas();
    void listarCidadesByNome();
    void listarCidadesByFronteira(Cidade &cidade);
    void cadastrarTrajeto(Cidade &origem, Cidade &destino, string tipo);

    // menu passageiros
    void menuGestaoPassageiros();
    list<Passageiro*> listarPassageirosInLoco(Cidade &cidade);
    void cadastrarPassageiro();
    void listarPassageiros();

    // menu transportes
    void menuGestaoTransportes();
    void menuListarTransportes();
    void adicionarTransporte();
    void listarTransportes(Transporte* t);
    int listarTransportesParaViagem(Cidade &cidade, string tipo);
    
    // funções auxiliares
    bool cpfExiste(int Cpf);
    bool checarFronteira(Cidade &cidade, Cidade &front);
    string upperStr(string str);
    int gerarId();
    int calcularRota(Viagem &viagem);

    // menu de viagens
    void menuGestaoViagens();
    void gerarViagem();
    void detalharViagem();
    
    void iniciarViagem(list<Viagem*> viagens);
    void finalizarViagem(Viagem* viagem);
    void listarViagemByCod(list<Viagem*> &viagens);
    Cidade* selecionarCidade();
    Cidade* setCidadeViagemPartida();
    Cidade* setCidadeViagemDestino();
    Transporte* setTransporte(Cidade &cidade, string tipo);
    list<Passageiro*> passageirosViagem(Transporte &transporte);

    // getters
    list<Viagem*> getViagens() { return viagens; }
    list<Transporte*> getTransportes() { return transportes; }
    list<Passageiro*> getPassageiros() { return passageiros; }

    // dijkstra
    pair<list<Cidade*>, int> calcularMelhorRota(Cidade &origem, Cidade &destino, string tipo);
    list<Cidade*> gerarCidadesViagem(vector<int> caminho);
    pair<vector<int>, vector<int>> dijkstra(int origem, const vector<vector<Edge>>& grafo);
    vector<int> reconstruirCaminho(int origem, int destino, const vector<int>& antecessor);
};

#endif 


