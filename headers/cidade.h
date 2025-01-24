#ifndef CIDADE_H
#define CIDADE_H

#include <string>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include "../headers/transporte.h"

using std::list;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::cerr;

class Cidade {
private:
    string nome;
    list<Cidade*> fronteiras;
public:
    Cidade();
    Cidade(string nome);
    int indice;
    int nFront;
    string getNome();
    list<Cidade*> getFronteiras();
    void setFronteiras(Cidade* cidade);
    int getFronteirasSize();
};

#endif 

