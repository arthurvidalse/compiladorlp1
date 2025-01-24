#ifndef TRAJETO_H
#define TRAJETO_H

#include <string>
#include "../headers/cidade.h"

class Trajeto {
public:
    Cidade* origem;
    Cidade* destino;
    std::string tipo;
    int distancia;

    Trajeto(Cidade* o, Cidade* d, std::string t, int dist)
        : origem(o), destino(d), tipo(t), distancia(dist) {}
};

#endif
