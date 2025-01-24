#include "../headers/cidade.h"

Cidade::Cidade(string nome) : nome(nome) {
    indice++;
}

string Cidade::getNome() {
    return nome;
}

list<Cidade*> Cidade::getFronteiras(){
    return fronteiras;
}

void Cidade::setFronteiras(Cidade *cidade){
    fronteiras.push_back(cidade);
}

int Cidade::getFronteirasSize(){
    return fronteiras.size();
}