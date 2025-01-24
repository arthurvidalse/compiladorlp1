#include "database.h"

list<Cidade*> Cidades;
list<Transporte*> Transportes;
list<Passageiro*> Passageiros;
list<Viagem*> Viagens;


// funções auxliares

vector<string> retornaLinha(vector<string> v, int j){
  vector<string> aux;
    string token;
    stringstream ss(v[j]);
    while(getline(ss, token, ',')){
      aux.push_back(token);
}
  return aux;
}

list<Cidade*> adicionarFronteiras(list<Cidade*> cidades, vector<string> v){
  vector<string> aux;
  int j = 0;
  for(auto &c : cidades){
    aux = retornaLinha(v, j);
    j++;
    if(aux.size() > 2){
      for(auto &f : cidades){
        for (int i=3; i<aux.size(); i++){
          if(f->indice == stoi(aux[i])){
            c->setFronteiras(f);
          }
        }
      }
    }    
  }
  return cidades;
};

void printlist(vector<string> dados){
  for(int i=0; i<dados.size(); i++){
    cout << dados[i] << "-";
  }
}


Database::Database(){
  cout << "carregando dados...";
}

int Database::getTempo(string nomeArquivo){
  int tempo;
  ifstream arquivo(nomeArquivo, fstream::in);
    string linha;
    getline(arquivo, linha);
    tempo = stoi(linha);
  return tempo;
}

void Database::setTempo(string nomeArquivo, int tempo){
  ofstream arquivo(nomeArquivo, fstream::trunc);
  if(arquivo.is_open()){
    arquivo << tempo;
  }
}

void Database::setCidades(list<Cidade*> cidades){
  for(auto &c : cidades){
    this->cidades.push_back(c);
  }
}

void Database::salvarTransportes(string nomeArquivo, list<Transporte*> &transportes){
  ofstream arquivo(nomeArquivo, fstream::trunc);
  if(arquivo.is_open()){
    for(auto &t : transportes){


      arquivo << t->indiceT << ","<< t->getNome() << "," << t->getTipo() << "," << t->getCapacidade() << "," << t->getVelocidade() << "," << t->getDistanciaDescanso() << "," << t->getTempoDescanso() << "," << t->getCidade()->indice << "," << t->getCidadeAtual()->indice << endl;
  }
}
}

void Database::salvarCidades(string nomeArquivo, list<Cidade*> &cidades){
  ofstream arquivo(nomeArquivo, fstream::trunc);

  if(arquivo.is_open()){
    for (auto  &c : cidades){
      arquivo << c->getNome() << "," << c->indice;

      if(c->getFronteirasSize() > 0){
        arquivo << "," << c->getFronteirasSize();
        for (auto &f : c->getFronteiras()){
          arquivo << "," << f->indice;
        }
      }
      arquivo << endl;
    }
  }
}

void Database::salvarTrajetos(string nomeArquivo, list<Trajeto*> &trajetos){
  ofstream arquivo(nomeArquivo, fstream::trunc);
    if(arquivo.is_open()){
      for(auto &t : trajetos){
        arquivo << t->origem->indice << "," << t->destino->indice << "," << t->tipo << "," << t->distancia << endl;
    }
  }
}

void Database::salvarViagens(string nomeArquivo, list<Viagem *> &viagens){
  ofstream arquivo(nomeArquivo, fstream::trunc);
  if(arquivo.is_open()){
    for(auto &v : viagens){
      arquivo << v->getViagemId() << "," << v->transporte->indiceT << "," << v->kmRodados << ",";
      if(v->getResultado()) arquivo << "1";
      if(!v->getResultado()) arquivo << "0";
      arquivo << ",";
      if(v->getStatus()) arquivo << "1";
      if(!v->getStatus()) arquivo << "0";
    arquivo << "," << v->distanciaTotal << "," << v->tempoRestante << "," << v->tempoCorrido;
      arquivo << "," << v->passageiros.size();
      for(auto &p : v->passageiros){
        arquivo << "," << p->getCpf();
      }
      arquivo << "," << v->cidades.size();
      for (auto &c : v->cidades){
          arquivo << "," << c->indice;
        }
      arquivo << endl;
    }
  }
}

void Database::addTrajeto(string nomeArquivo, Trajeto* &trajeto){
  ofstream arquivo(nomeArquivo, fstream::in|fstream::out|fstream::app);
  if(arquivo.is_open()){
    arquivo << trajeto->origem->indice << "," << trajeto->destino->indice << "," << trajeto->tipo << "," << trajeto->distancia << endl;

}
};

void Database::addCidade(string nomeArquivo, Cidade *&cidade){
  ofstream arquivo(nomeArquivo, fstream::in|fstream::out|fstream::app);
  if(arquivo.is_open()){
    arquivo << cidade->getNome() << "," << cidade->indice;

    if(cidade->getFronteirasSize() > 0){
      for (auto &f : cidade->getFronteiras()){
        arquivo << "," << f->indice;
      }
    }
    arquivo << endl;
  }

};

void Database::salvarPassageiros(string nomeArquivo, list<Passageiro*> passageiros){
  ofstream arquivo(nomeArquivo, fstream::trunc);
  if(arquivo.is_open()){
    for(auto &p : passageiros){
      arquivo << p->getNome() << "," << p->getCidadeAtual()->indice << "," << p->getCpf();
      if(p->getEmTransito() == true){
        arquivo << ",1," << p->viagemAtual->getViagemId();
      } else {
        arquivo << ",0";
      }
      arquivo << "," << p->getViagens().size();
      for(auto &v : p->getViagens()){
        arquivo << "," << v->getViagemId();
      }
      arquivo << endl;
    }
  }
}



// carregar dados

list<Cidade*> Database::carregarCidades(string nomeArquivo){

  list<Cidade*> cidades;
  vector<string> aux;
  ifstream arquivo(nomeArquivo, fstream::in);
  if(arquivo.is_open()){
    arquivo.close();
    arquivo.open(nomeArquivo, fstream::in);
    string linha;
    while(getline(arquivo, linha)){
      stringstream ss(linha);
      string token;
      getline(ss, token, ',');
      Cidade *cidade = new Cidade(token);
      getline(ss, token, ',');
      cidade->indice = stoi(token);
      cidades.push_back(cidade);
      aux.push_back(linha);
    }
   }

  cidades = adicionarFronteiras(cidades, aux);

  Cidades = cidades;

  return cidades;
}

list<Transporte*> Database::carregarTransportes(string nomeArquivo){

  list<Transporte*> transportes;
  Cidade* cidade = nullptr;

  ifstream arquivo(nomeArquivo, fstream::in);
  if(arquivo.is_open()){
    arquivo.close();
    arquivo.open(nomeArquivo, fstream::in);
    string linha;
    while(getline(arquivo, linha)){
      vector<string> dados;
      stringstream ss(linha);
      string token;
      while(getline(ss, token, ',')){
        dados.push_back(token);
      }
      for (auto &c : Cidades){
        if(c->indice == stoi(dados[7])){
          cidade = c;
        }
      }
      Transporte *transporte = new Transporte(stoi(dados[0]), dados[1], dados[2], stoi(dados[3]), stoi(dados[4]), stoi(dados[5]), stoi(dados[6]), cidade);
      transportes.push_back(transporte);
    }
  }
  Transportes = transportes;
  return transportes;
}

list<Trajeto*> Database::carregarTrajetos(string nomeArquivo){
  list<Trajeto*> trajetos;
  Cidade* origem = nullptr;
  Cidade* destino = nullptr;

  ifstream arquivo(nomeArquivo, fstream::in);
  if(arquivo.is_open()){
    arquivo.close();
    arquivo.open(nomeArquivo, fstream::in);
    string linha;
    while(getline(arquivo, linha)){
      vector<string> dados;
      stringstream ss(linha);
      string token;
      while(getline(ss, token, ',')){
        dados.push_back(token);
      }
      for(auto &c : Cidades){
        if(c->indice == stoi(dados[0])){
          origem = c;
        }
        if(c->indice == stoi(dados[1])){
          destino = c;
        }
      }
      Trajeto *trajeto = new Trajeto(origem, destino, dados[2], stoi(dados[3]));
      trajetos.push_back(trajeto);
    }
  }
  return trajetos;
}

list<Viagem*> Database::carregarViagens(string nomeArquivo){
  list<Viagem*> viagens;
  Cidade* destino = nullptr;
  Transporte* veiculo = nullptr;
  list<Cidade*> cidadesViagem;
  list<Passageiro*> passageirosViagem;

  ifstream arquivo(nomeArquivo, fstream::in);
  int j;
  if(arquivo.is_open()){
    arquivo.close();
    arquivo.open(nomeArquivo, fstream::in);

    string linha;
    while(getline(arquivo, linha)){
      vector<string> dados;
      stringstream ss(linha);
      string token;
      while(getline(ss, token, ',')){
        dados.push_back(token);
      }
      for(auto &t : Transportes){
        if(t->indiceT == stoi(dados[1]))
          veiculo = t;
      }

      j = stoi(dados[8]);
      if(j > 0){
        for (int i=0; i<j; i++){
          for(auto &p : Passageiros){
            if(p->getCpf() == stoi(dados[9+i])) passageirosViagem.push_back(p);
          }
        }
      }
      if(stoi(dados[10+j]) > 0){
        for(int i=0; i<stoi(dados[9+j]); i++){
          for(auto &c : Cidades){
            if(c->indice == stoi(dados[i+10+j])) cidadesViagem.push_back(c);
            if(c->indice == stoi(dados[dados.size()-1])) destino = c;
          }
        }
      }

      Viagem* viagem = new Viagem(stoi(dados[0]), destino, veiculo, passageirosViagem, cidadesViagem);

      if(dados[3] == "0") viagem->setResultado(false);
      if(dados[3] == "1") viagem->setResultado(true);
      if(dados[4] == "0") viagem->setStatus(false);
      if(dados[4] == "1") viagem->setStatus(true);

      viagem->kmRodados = stoi(dados[2]);
      viagem->tempoCorrido = stoi(dados[7]);
      viagem->distanciaTotal = stoi(dados[5]);
      viagem->tempoRestante = stoi(dados[6]);

      viagens.push_back(viagem);

    }


  }


  Viagens = viagens;
  return viagens;
}

list<Passageiro*> Database::carregarPassageiros(string nomeArquivo){
  //list<Viagem*> viagens;
  Cidade* cidadeAtual = nullptr;
  //Transporte* veiculo = nullptr;
  //list<Cidade*> cidadesViagem;
  list<Passageiro*> passageiros;

  ifstream arquivo(nomeArquivo, fstream::in);
  int j;
  if(arquivo.is_open()){
    arquivo.close();
    arquivo.open(nomeArquivo, fstream::in);

    string linha;
    while(getline(arquivo, linha)){
      vector<string> dados;
      stringstream ss(linha);
      string token;
      while(getline(ss, token, ',')){
        dados.push_back(token);
      }

      for (auto &c : Cidades){
        if(stoi(dados[1]) == c->indice) cidadeAtual = c;
      }
      Passageiro* passageiro = new Passageiro(dados[0], cidadeAtual);
      passageiro->setCpf(stoi(dados[2]));

      j = stoi(dados[3]);
      for (int i=0; i<j; i++){
        for(auto &v : Viagens){
          if(v->getViagemId() == stoi(dados[i+4])) passageiro->addViagem(v);
        }
      }
      passageiros.push_back(passageiro);
    }
  }


  Passageiros = passageiros;
  return passageiros;
}


