#include "../headers/sistema.h"

Database *database;


// gerenciando sistema

Sistema::Sistema() {
    this->tempoCorrido = database->getTempo("database/tempo.txt");
    this->cidades = database->carregarCidades("database/cidades.csv");
    this->transportes = database->carregarTransportes("database/transportes.csv");
    this->trajetos = database->carregarTrajetos("database/trajetos.csv");
    this->viagens = database->carregarViagens("database/viagens.csv");
    this->passageiros = database->carregarPassageiros("database/passageiros.csv");
    this->viagens = database->carregarViagens("database/viagens.csv");
}

void Sistema::iniciar() {
    int opcao;

    while (true) {
        limpar();
        cout << "1. Gestão de Cidades\n";
        cout << "2. Gestão de Transportes\n";
        cout << "3. Gestão de Passageiros\n";
        cout << "4. Gestão de Viagens\n";
        cout << "5. Avanço de Tempo\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                limpar();
                menuGestaoCidades();
                break;
            case 2:
                limpar();
                menuGestaoTransportes();
                break;
            case 3:
                limpar();
                menuGestaoPassageiros();
                break;
            case 4:
                limpar();
                menuGestaoViagens();
                break;
            case 5: // para teste
                limpar();
                atualizarHora();
                break;
            case 0:
                salvarDados();
                telaSair();
                return;
            default:
                cout << "Opção inválida." << endl;
        }
    }
}

void Sistema::salvarDados() {
    database->setTempo("database/tempo.txt", this->tempoCorrido);
    database->salvarCidades("database/cidades.csv", cidades);
    database->salvarTransportes("database/transportes.csv", transportes);
    database->salvarTrajetos("database/trajetos.csv", trajetos);
    database->salvarViagens("database/viagens.csv", viagens);
    database->salvarPassageiros("database/passageiros.csv", passageiros);
}

void Sistema::limpar() {
    cout << "\033[2J\033[1;1H";
    cout << "### CONTROLADOR DE VIAGENS ###" << endl << endl;
    calcularDia();
    cout << endl;
}

void Sistema::pressEnter() {
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::telaSair() {
    cout << "\033[2J\033[1;1H";
    cout << endl << endl << "### SAINDO DO PROGRAMA... ###" << endl << endl;
}

void Sistema::calcularDia(){
    int tempo = this->tempoCorrido;
    int mes = ((tempo/24)/30);
    int dia = (tempo/24) - (mes*30);

    int hora = tempo - ((tempo/24)* 24);

    cout << "Mês: " << mes << " - Dia: " << dia << " - hora: " << hora << endl;
}

void Sistema::setTempoCorrido(int tempo){
    this->tempoCorrido += tempo;
}

void Sistema::avancarTempo(int tempo){

    setTempoCorrido(tempo);
    list<Viagem*> viagensFinalizadas;
    for(auto &v : viagens){
        if(v->getStatus() == true){
            v->avancarTempo(tempo);

            v->kmRodados = (v->tempoCorrido * v->transporte->getVelocidade() - ((v->tempoCorrido/v->transporte->getDistanciaDescanso()) * v->transporte->getTempoDescanso()));
            if(v->tempoRestante == 0){
                finalizarViagem(v);
                viagensFinalizadas.push_back(v);
            }
        }
    }
}

void Sistema::atualizarHora(){
    int tempo;
    cout << "Quanto tempo deseja avançar?" << endl;
    cin >> tempo;
    avancarTempo(tempo);
}



// menu de cidades

void Sistema::menuGestaoCidades() {

    int opcao;

    while (true) {
        limpar();
        cout << "1.1 Adicionar Cidade\n";
        cout << "1.2 Adicionar Fronteiras a Cidades\n";
        cout << "1.3 Listar Cidades\n";
        cout << "1.4 Cidades mais visitadas\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                limpar();
                adicionarCidade();
                break;
            case 2:
                limpar();
                menuAdicionarFronteiras();
                break;
            case 3:
                limpar();
                listarCidades();
                pressEnter();
                break;
            case 4:
                limpar();
                cidadesMaisVisitadas();
                pressEnter();
            case 0:
                salvarDados();
                return;
            default:
                cout << "Opção inválida." << endl;
        }
    }
}

void Sistema::adicionarCidade() {
    string nomeCidade;
    cout << "Digite o nome da cidade: ";

    cin.ignore();
    getline(cin, nomeCidade);
    Cidade* cidade = new Cidade(nomeCidade);
    cidade->indice = (cidades.size() + 1);
    database->addCidade("cidades.csv", cidade);
    cidades.push_back(cidade);
}

void Sistema::menuAdicionarFronteiras() {
    listarCidades();
    cout << endl << "Selecione a cidade que deseja adicionar fronteiras: ";
    int indice;
    cin >> indice;

    // cancelar cadastramento
    if (indice == 0){
        limpar();
        cout << "Cancelando cadastramento de cidade..." << endl;
        pressEnter();
        return;
    }

    Cidade* cidade = nullptr;
    for (auto &c : cidades) {
        if (c->indice == indice) {
            cidade = c;
            break;
        }
    }

    if (cidade) {
        limpar();
        adicionarFronteiras(cidade);
    } else {
        cout << "Cidade não encontrada." << endl;
    }
}

void Sistema::adicionarFronteiras(Cidade* cidade) {

    listarCidadesByFronteira(*cidade);
    
    cout << endl << "Selecione a cidade fronteiriça à cidade: " << cidade->getNome() << endl;
    int indice;
    cin >> indice;


     // cancelar cadastramento
    if (indice == 0){
        limpar();
        cout << "Cancelando cadastramento de cidade..." << endl;
        pressEnter();
        return;
    }
    
    Cidade* front = nullptr;
    for (auto &x : cidades) {
        if (x->indice == indice) front = x;
        }
    int i = 0;
    for (auto &t : trajetos){
        if(t->origem == cidade && t->destino == front || t->origem == front && t->destino == cidade){
            if (t->tipo == "T") i += 1;
            if (t->tipo == "A") i += 2;
        }
    }
    if (i == 3){
        limpar();
        cout << "Cidades ja são fronteiriças pela via aquática e terrestre" << endl;
        pressEnter();
        return;
    }
    if (i == 0){
        int opc;
        do{
            limpar();
            cout << "Qual tipo de trajeto deseja adicionar?" << endl;
            cout << "Digite 1 para aquático e 2 para terrestre:  ";
            cin >> opc;
        } while(opc > 2 || opc < 1);
    
        if (opc == 1){
            cidade->setFronteiras(front);
            front->setFronteiras(cidade);
            cadastrarTrajeto(*cidade, *front, "A"); 
        }
        if (opc == 2){
            cidade->setFronteiras(front);
            front->setFronteiras(cidade);
            cadastrarTrajeto(*cidade, *front, "T"); 
        }
        
    }
    if (i == 1){
        cadastrarTrajeto(*cidade, *front, "A"); 
    }
    if (i == 2){
        cadastrarTrajeto(*cidade, *front, "T"); 
    }
};

void Sistema::listarCidades() {
    cout << "CIDADES:" << endl << endl;

    for (auto &c : cidades) {
        cout << c->indice << "ª " << c->getNome() << ":" << endl;

        if (c->getFronteirasSize() > 0) {
            cout << " Fronteiras: ";
            for (auto &f : c->getFronteiras()) {
                cout << f->getNome() << " - ";
            }
            cout << endl;
        } else {
            cout << " Cidade sem fronteiras" << endl;
        }
    }
}

void Sistema::cidadesMaisVisitadas() {
    std::map<Cidade*, int> cidadeVisitas;

    for (auto &viagem : viagens) {
        if (viagem->getResultado()) { 
            cidadeVisitas[viagem->destino]++;
        }
    }

    std::list<std::pair<Cidade*, int>> visitasOrdenadas(cidadeVisitas.begin(), cidadeVisitas.end());

    visitasOrdenadas.sort([](const std::pair<Cidade*, int>& a, const std::pair<Cidade*, int>& b) {
        return a.second > b.second; 
    });

    cout << "Cidades mais visitadas:" << endl;
    for (const auto& par : visitasOrdenadas) {
        cout << par.first->getNome() << " - " << par.second << " visitas" << endl;
    }
}

void Sistema::listarCidadesByNome() {
    for (auto &c : cidades) {
        cout << c->indice << "ª " << c->getNome() << ":" << endl;

    }
}

void Sistema::listarCidadesByFronteira(Cidade &cidade) {
    for (auto &c : cidades) {
        if(cidade.indice != c->indice && !checarFronteira(cidade, *c)){
            cout << c->indice << "ª " << c->getNome() << ":" << endl;
            if (c->getFronteirasSize() > 0) {
                cout << "Fronteiras: ";
                for (auto &f : c->getFronteiras()) {
                    cout << f->getNome();
                    // int i = 0;
                    // for (auto &t : trajetos){
                    //     if(t->origem == &cidade && t->destino == f || t->origem == f && t->destino == &cidade){
                    //         if (t->tipo == "T") i += 1;
                    //         if (t->tipo == "A") i += 2;
                    //     }
                    // }
                    // if (i == 1) cout << " (T) ";
                    // if (i == 2) cout << " (A) ";
                    // if (i == 3) cout << " (A|T) ";
                    cout << " - ";
                }
                cout << endl;
            } else {
                cout << "Cidade sem fronteiras" << endl;
            }
        }



    }

}

void Sistema::cadastrarTrajeto(Cidade &origem, Cidade &destino, string tipo) {
    limpar();
    string origemNome, destinoNome;
    int distancia;

    if (tipo == "A"){
        cout << "Cadastrando trajeto aquático entre " << origem.getNome() << " e " << destino.getNome() << endl << endl;
        cout << "Digite a distância em Km: ";
        cin >> distancia;
        Trajeto* trajeto = new Trajeto(&origem, &destino, tipo, distancia);
        trajetos.push_back(trajeto);
        cout << "Trajeto cadastrado com sucesso!" << endl;
        database->addTrajeto("database/trajetos.csv", trajeto);
    }
    if (tipo == "T"){
        cout << "Cadastrando trajeto terrestre entre " << origem.getNome() << " e " << destino.getNome() << endl << endl;
        cout << "Digite a distância em Km: ";
        cin >> distancia;
        Trajeto* trajeto = new Trajeto(&origem, &destino, tipo, distancia);
        trajetos.push_back(trajeto);
        cout << "Trajeto cadastrado com sucesso!" << endl;
        database->addTrajeto("database/trajetos.csv", trajeto);
    }
    

    pressEnter();
}



// menu de passageiros

void Sistema::menuGestaoPassageiros() {
    int opcao;

    while (true) {
        cout << "3.1 Adicionar Passageiro\n";
        cout << "3.2 Listar Passageiros\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                limpar();
                cadastrarPassageiro();
                break;
            case 2:
                listarPassageiros();
                break;
            case 0:
                return;
            default:
                cout << "Opção inválida." << endl;
        }
    }
}

list<Passageiro*> Sistema::listarPassageirosInLoco(Cidade &cidade){
    limpar();
    list<Passageiro*> passageirosList;
    for (auto &p : passageiros){
        if(p->getCidadeAtual() == &cidade){
            cout << p->getCpf() << " - " << p->getNome() << endl;

            passageirosList.push_back(p);
        }

    }
    return passageirosList;
}

void Sistema::cadastrarPassageiro() {
    string nome, nomeCidadeAtual;
    int cpf;
    cout << "Digite o nome do passageiro: ";
    cin.ignore();
    getline(cin, nome);

    Cidade* cidadeAtual = selecionarCidade();
    if (!cidadeAtual) {
        return;
    }

    cout << "Digite o CPF do passageiro: ";
    cin >> cpf;

    if (cpfExiste(cpf)) {
        std::cout << "Erro: CPF já cadastrado." << std::endl;
        return;
    }

    Passageiro* novoPassageiro =  new Passageiro(nome, cidadeAtual);
    novoPassageiro->setCpf(cpf);
    passageiros.push_back(novoPassageiro);

    cout << "Passageiro cadastrado com sucesso" << endl;
}

void Sistema::listarPassageiros(){
    limpar();

    for (auto &p : passageiros){
        cout << p->getCpf() << " - " << p->getNome() << endl;
        if(p->getEmTransito() == true){
            cout << "Passageiro em trânsito, com destino a " << p->viagemAtual->destino->getNome() << endl;
        }
        if(p->getEmTransito() == false) cout << " Loc: " << p->getCidadeAtual()->getNome() << endl;

    }

    int cpf;
    cout << "Digite um cpf para ver as viagens do passageiro (ou 0 para voltar): ";
    cin >> cpf;

    for (auto &p : passageiros){
        if(p->getCpf() == cpf){
            limpar();
            cout << "Viagens de: " << p->getNome() << endl << endl;
            int i = 1;
            for (auto &v : p->getViagens()){
                cout << i << "º viagem: " << endl;
                cout << v->getViagemId() << " | origem: " << v->origem->getNome() << " - destino: " << v->destino->getNome() << endl;
            }
        }
    }
    
    pressEnter();
}



// menu de transportes

void Sistema::menuGestaoTransportes() {
    int opcao;

    while (true) {
        limpar();
        cout << "2.1 Adicionar Transporte\n";
        cout << "2.2 Listar Transportes\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                limpar();
                adicionarTransporte();
                break;
            case 2:
                menuListarTransportes();
                break;
            case 0:
                return;
            default:
                cout << "Opção inválida." << endl;
        }
    }
}

void Sistema::menuListarTransportes(){
    cout << "Transportes: " << endl;
    for(auto &t : transportes){
        cout << t->indiceT << ". " << t->getNome() << endl;
    }
    cout << "Selecione o transporte que deseja listar: " << endl << endl;
    int transporteEscolhido;
    cin >> transporteEscolhido;
    if(transporteEscolhido == 0) return;

    listarTransportes(*std::next(transportes.begin(), transporteEscolhido - 1));

}

void Sistema::adicionarTransporte() {

    string nomeTransporte, tipo;
    int capacidade, indiceCIdade;
    int velocidade, distanciaDescanso, tempoDescanso;

    cout << "Digite o nome do transporte: ";
    cin.ignore();
    getline(cin, nomeTransporte);
    cout << "Digite o tipo do transporte (A | T): ";
    cin >> tipo;
    cout << "Digite a capacidade do transporte: ";
    cin >> capacidade;
    cout << "Digite a velocidade do transporte: ";
    cin >> velocidade;
    cout << "Digite a distância de descanso do transporte: ";
    cin >> distanciaDescanso;
    cout << "Digite o tempo de descanso do transporte: ";
    cin >> tempoDescanso;
    cout << "Selecione a cidade atual do transporte: \n";
    listarCidadesByNome();
    cin >> indiceCIdade;

    Cidade* cidadeAtual = nullptr;
    for (auto cidade : cidades) {
        if (cidade->indice == indiceCIdade) {
            cidadeAtual = cidade;
            break;
        }
    }

    if (cidadeAtual) {
        Transporte* transporte = new Transporte(transportes.size()+1, nomeTransporte, tipo, capacidade, velocidade, distanciaDescanso, tempoDescanso, cidadeAtual);
        transportes.push_back(transporte);
    } else {
        cout << "Cidade não encontrada. Transporte não adicionado." << endl;
    }
}

void Sistema::listarTransportes(Transporte* t) {
    // pedir vaiculo e listar individualmente
    limpar();
    cout << t->getNome() << endl;    
    cout << endl << "Tipo: ";
    if(t->getTipo() == "T") cout << "terrestre";
    if(t->getTipo() == "A") cout << "aquático";
    cout << "\nCapacidade: " << t->getCapacidade() << " - Velocidade: " << t->getVelocidade() 
         << "\nDistância máxima sem pausa: " << t->getDistanciaDescanso() << "\nTempo mínimo de descanso: " 
         << t->getTempoDescanso() << "\nLocalização: " << t->getCidadeAtual()->getNome() << endl;
    if(t->getEmTransito() == true){
        cout << "Em viagem com destino a " << t->getDestino();
    }
    pressEnter();
    return;
}

int Sistema::listarTransportesParaViagem(Cidade &cidade, string tipo){
    int qnt = 0;
{        
    for(auto &t : transportes){

        if(t->getCidade() == &cidade && t->getTipo() == upperStr(tipo) && t->getEmTransito() == false){
            cout << t->indiceT << " - " << t->getNome() << " - " << t->getVelocidade() << "km/h" << endl;
            qnt++;
        }
    }
}
    return qnt;
}



// funcoes auxiliares

bool Sistema::cpfExiste(int cpf) {
    for (Passageiro* passageiro : passageiros) {
        if (passageiro->getCpf() == cpf) {
            return true;
        }
    }
    return false;
}

bool Sistema::checarFronteira(Cidade &cidade, Cidade &front){

    int i = 0;
    for (auto &t : trajetos){
        if(t->origem == &cidade && t->destino == &front || t->origem == &front && t->destino == &cidade){
            if (t->tipo == "T") i += 1;
            if (t->tipo == "A") i += 2;
        }
    }
    if (i == 3) return true;
    return false;
}

string Sistema::upperStr(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int Sistema::gerarId(){
    int cod, i;
    do {
        i = 0;
        srand(time(NULL));
        cod = rand() % 100;
        if(viagens.size() > 0){
            for(auto &v : viagens){
                if(cod == v->getViagemId() || cod == 0) i++;
            }
        }

    } while(i > 0);
    return cod;
}

int Sistema::calcularRota(Viagem &viagem){


    int distTotal = 0;
    for(auto &t : trajetos){
        if(viagem.transporte->getTipo() == t->tipo){
            if((t->origem == viagem.origem && t->destino == viagem.destino) || (t->origem == viagem.destino && t->destino == viagem.origem)){
                distTotal += t->distancia;

            }
        }

    }

    return distTotal;
}



// menu de viagens

void Sistema::menuGestaoViagens() {
    int opcao;

    while (true) {
        cout << "4.1 Solicitar viagem\n";
        cout << "4.2 Listar viagens\n";
        cout << "4.3 Iniciar viagem\n"; 
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                limpar();
                gerarViagem();
                break;
            case 2:
                limpar();
                detalharViagem();
                break;
            case 3:
                limpar();
                iniciarViagem(viagens);
                pressEnter();
                break;
            case 4: 
                break;
            case 0:
                return;
            default:
                cout << "Opção inválida." << endl;
        }
    }
}

void Sistema::gerarViagem(){

    cout << "Gerando Viagem!!!!" << endl;

    string tipo;


    Cidade* origem = setCidadeViagemPartida();
    if (origem == nullptr) return;
    Cidade* destino = setCidadeViagemDestino();
    if (destino == nullptr) return;
    limpar();
    cout << "Como você deseja ir de " << origem->getNome() << " para " << destino->getNome() <<  endl << "Digite A para aquático e T para terrestre: ";
    cin >> tipo;
    tipo = upperStr(tipo);
    pair<list<Cidade*>, int> rotaViagem = calcularMelhorRota(*origem, *destino, tipo);
    list<Cidade*> cidadesViagem = rotaViagem.first;
    int distTotal = rotaViagem.second;

    
    if(cidadesViagem.empty()){
        limpar();
        cout << "Não há caminho entre " << origem->getNome() << " e " << destino->getNome() << ".\n";
        cout << endl << "Cancelando colicitação de viagem!" << endl;
        return;
    }
    Transporte* transporteV = setTransporte(*origem, tipo);
    if(transporteV == nullptr){
        cout << "Nenhum transporte na cidade. Solicitação de viagem cancelada!" << endl;
        return;
    }
    list<Passageiro*> escolhidos = passageirosViagem(*transporteV);
    if (escolhidos.empty()) {
        cout << "Nenhum passageiro na cidade de origem \nSolicitação de viagem cancelada!" << endl;
        return;
    }
    transporteV->setDestino(destino);

    Viagem* viagem = new Viagem(gerarId(), destino, transporteV, escolhidos, cidadesViagem);

    // // Calcular o tempo estimado da viagem
    int tempoTotal = distTotal / viagem->transporte->getVelocidade();
    if(distTotal % viagem->transporte->getVelocidade() != 0) tempoTotal +=1;

    int paradas = distTotal/viagem->transporte->getDistanciaDescanso();
    tempoTotal = tempoTotal+(paradas*viagem->transporte->getTempoDescanso());


    viagem->tempoRestante = tempoTotal;
    viagem->distanciaTotal = distTotal;


    viagens.push_back(viagem);

}

void Sistema::detalharViagem() {

std::list<Viagem*> viagens = this->getViagens();

if (viagens.empty())
{
    cout << "Nenhuma viagem cadastrada." << endl;
    return;
}

cout << "Lista de viagens disponíveis:" << endl;

cout << endl << "Viagens acontecendo:" << endl << endl;
for (auto& viagem : viagens) {
    if(viagem->getStatus() == true){
        cout << viagem->getViagemId() << ". Origem: " << viagem->origem->getNome() 
             << " -> Destino: " << viagem->destino->getNome() << endl;
    }
}

cout << endl << "Viagens em espera: " << endl << endl;

for (auto& viagem : viagens) {
    if(viagem->getStatus() == false && viagem->getResultado() == false){
        cout << viagem->getViagemId() << ". Origem: " << viagem->origem->getNome() 
             << " -> Destino: " << viagem->destino->getNome() << endl;
    }
}

cout << endl << "Viagens finalizadas: " << endl << endl;

for (auto& viagem : viagens) {
    if(viagem->getResultado() == true){
        cout << viagem->getViagemId() << ". Origem: " << viagem->origem->getNome() 
             << " -> Destino: " << viagem->destino->getNome() << endl;
    }
}


cout << "Deseja detalhar alguma viagem? (Digite o ID da viagem ou 0 para voltar): ";
int escolha;
cin >> escolha;
int aux = 0;

if(escolha == 0){
    return;
}

for(auto &v : viagens){
    if(v->getViagemId() == escolha){
        aux++;
        cout << "Detalhes da viagem: " << v->getViagemId() << endl << endl;
        cout << "Distância: " << v->distanciaTotal << endl;
        cout << "Origem: " << v->origem->getNome(); 
        cout << "\nDestino: " << v->destino->getNome();  
        cout << "\nPassageiros: ";
        for (auto &passageiro : v->passageiros) 
            {
                cout << passageiro->getNome() << " - ";
            }
        cout << "\nTransporte: " << v->transporte->getNome() << endl;
        if(v->getStatus() == true){
            cout << "Tempo Restante: " << v->tempoRestante << " horas" << endl;
            //cout << "Km percorridos: " << v->kmRodados << endl; //**arrumar calculo**
        }
        else if (v->getResultado() == true){
            cout << "Viagem já finalizada!" << endl;
        }
        else {
            cout << "Tempo de viagem: " << v->tempoRestante << " horas" << endl;
            cout << "Aguardando inicio!" << endl;
        }
    }
}
if (aux == 0){
    limpar();
     cout << "Viagem não encontrada" << endl;
}

pressEnter();
limpar();


}

void Sistema::iniciarViagem(list<Viagem*> viagens) {
    listarViagemByCod(viagens);
    cout << "Selecione a viagem que deseja iniciar: ";
    Viagem* viagem = nullptr;
    int indiceViagem;
    cin >> indiceViagem;
    for(auto &v : viagens){
        if(indiceViagem == v->getViagemId()){
            viagem = v;
        }
    }

    if (!viagem) {
        std::cout << "Viagem não encontrada." << std::endl;
        return;
    }

    // Verificar se o transporte está disponível
    Transporte* transporte = viagem->transporte;

    if (!transporte || transporte->getEmTransito()) {
        std::cout << "Transporte não encontrado ou em trânsito." << std::endl;
        return;
    }

    // Verificar se todos os passageiros estão na cidade de origem e não estão em trânsito
    for (Passageiro* p : viagem->passageiros) {

        if (!p || p->getEmTransito() || p->getCidadeAtual() != viagem->origem) {
            std::cout << "Passageiro não encontrado, em trânsito ou não está na cidade de origem." << std::endl;
            return;
        }
    }

// Registrar a partida
transporte->partir();
viagem->setStatus(true);
for(auto &p : viagem->passageiros){
    p->setEmTransito(true);
    p->viagemAtual = viagem;
}




cout << "Viagem iniciada." << std::endl;

// Calcular a distância total da viagem
//to-do

}

void Sistema::finalizarViagem(Viagem* viagem) {
    if (!viagem->getStatus()) {
        std::cout << "A viagem já foi finalizada." << std::endl;
        return;
    }

    for (auto &p : viagem->passageiros){
        p->addViagem(viagem);
    }

    viagem->transporte->chegar(viagem->destino);
    viagem->setResultado(true);  
    viagem->setStatus(false);    

    for (Passageiro* passageiro : viagem->passageiros) {
        passageiro->setCidadeAtual(viagem->destino);  
        passageiro->setEmTransito(false);             
        passageiro->viagemAtual = nullptr;          
    }

    viagem->transporte->setEmTransito(false);

    std::cout << "Viagem de " << viagem->origem->getNome() << " para " << viagem->destino->getNome() << " finalizada com sucesso." << std::endl;
    pressEnter();
}

void Sistema::listarViagemByCod(list<Viagem*> &viagens) {
    for (auto v : viagens) {
        if (!v->getResultado()) { 
            cout << v->getViagemId() << ". " << v->origem->getNome() << " -> " << v->destino->getNome() << endl;
        }
    }
}

Cidade* Sistema::selecionarCidade() {
    listarCidadesByNome();
     int cidadeEscolhida;
        cout << "Digite o número correspondente à cidade: ";
        cin >> cidadeEscolhida;

        if (cidadeEscolhida < 1 || cidadeEscolhida > cidades.size()) {
            cout << "Erro: Cidade inválida." << endl;
            return nullptr; 
        }

        return *std::next(cidades.begin(), cidadeEscolhida - 1);
    }

Cidade* Sistema::setCidadeViagemPartida(){
    int idCity;
    limpar();
    listarCidadesByNome();
    cout << "De qual cidade deseja partir? ";
    cin >> idCity;
    if(idCity <= 0 || idCity > cidades.back()->indice){
        limpar();
        cout << "Cidade não existe!" << endl << "Cancelando a Solicitação de viagem..." << endl;
        pressEnter();
        return nullptr;
    }
    Cidade* cidade = nullptr;
    for (auto &c : cidades){
        if(c->indice == idCity) cidade = c;
    }

    return cidade;

}

Cidade* Sistema::setCidadeViagemDestino(){
    int idCity;
    limpar();
    listarCidadesByNome();
    cout << "Para Qual cidade deseja ir? ";
    cin >> idCity;
    if(idCity <= 0 || idCity > cidades.back()->indice){
        limpar();
        cout << "Cidade não existe!" << endl << "Cancelando a Solicitação de viagem..." << endl;
        pressEnter();
        return nullptr;
    }
    Cidade* cidade = nullptr;
    for (auto &c : cidades){
        if(c->indice == idCity) cidade = c;
    }
    return cidade;
}

Transporte* Sistema::setTransporte(Cidade &cidade, string tipo){
    limpar();
    int escolha;
    Transporte* transp = nullptr;
    int qnt = listarTransportesParaViagem(cidade, tipo);
    if(qnt == 0) return transp;
    
    cout << "Selecione o transporte:";
    cin >> escolha;
    for (auto &t : transportes){
        if(escolha == t->indiceT){
            return t;
        }
    }
    cout << "Transporte selecionado não existe, selecione um transporte válido!";
    pressEnter();
    return setTransporte(cidade, tipo);
}

list<Passageiro*> Sistema::passageirosViagem(Transporte &transporte) {
    int qnt;
    int cpf;
    list<Passageiro*> passageirosEscolhidos;

    do {
        limpar();
        cout << "Quantos passageiros viajarão? (limite: " << transporte.getCapacidade() << "): ";
        cin >> qnt;
        if (qnt > transporte.getCapacidade()) {
            cout << "Capacidade excedida!" << endl;
        }
    } while (qnt > transporte.getCapacidade());

    list<Passageiro*> passageirosNaCidade = listarPassageirosInLoco(*transporte.getCidade());

    if(passageirosNaCidade.empty()){
        return passageirosEscolhidos;
    }

    cout << "#Digite 0 para cancelar#" << endl;

    for (int i = 0; i < qnt; i++) {
        cin >> cpf;
        if (cpf == 0){
            return passageirosEscolhidos;
        }
        Passageiro* passageiroEscolhido = nullptr;

        for (auto &p : passageirosNaCidade) {
            if (p->getCpf() == cpf) {
                passageiroEscolhido = p;
                break;
            }
        }

        if (passageiroEscolhido != nullptr && !passageiroEscolhido->getEmTransito()) {
            passageirosEscolhidos.push_back(passageiroEscolhido);

        } else {
            cout << "Passageiro não encontrado ou já em trânsito. Tente novamente." << endl;
              i--;
        }
    }
    return passageirosEscolhidos;
    limpar();
}



// funções dijkstra

pair<list<Cidade*>, int> Sistema::calcularMelhorRota(Cidade &origem, Cidade &destino, string tipo){
    limpar();
    pair<list<Cidade*>, int> vazio;
    vector<int> caminho;
    
    //cout << "calculando melhor rota...\n";
    vector<vector<Edge>> grafo(this->cidades.size()+1);
    //cout << cidades.size() << endl;


    //cout << trajetos.size() << endl;
    for(auto &t : trajetos){
        if(t->tipo == tipo){
            grafo[t->origem->indice].push_back({t->destino->indice, t->distancia});
            grafo[t->destino->indice].push_back({t->origem->indice, t->distancia});
        }
        
        // cout << "orig: " << t->origem->indice << " dest: " << t->destino->indice << " dist: " << t->distancia << endl;
         // cout << "dest: " << t->destino->indice << " orig: " << t->origem->indice << " dist: " << t->distancia << endl;
    }


    pair<vector<int>, vector<int>> resultado = dijkstra(origem.indice, grafo);
    vector<int> distancias = resultado.first;
    vector<int> antecessor = resultado.second;

    if(distancias[destino.indice] == INT_MAX) {
        return vazio;
        } else {
            cout << "A menor distância de " << origem.getNome() << " para " << destino.getNome() << " é de " << distancias[destino.indice] << "km.\n";

            caminho = reconstruirCaminho(origem.indice, destino.indice, antecessor);
            cout << "Na viagem você passará por: " << origem.getNome();
            for (int cidade : caminho) {
                for(auto &c : cidades){
                    if(cidade != origem.indice && cidade != destino.indice){
                        // cout << "teste: " << cidade << " : "<< origem.indice << endl;
                        if(c->indice == cidade){
                            cout << ", " << c->getNome();
                        }
                    }
                }
            }
            cout << " até chegar em " << destino.getNome() << "." << endl;
            cout << endl;
        pressEnter();
        }
    list<Cidade*> cidadesViagem = gerarCidadesViagem(caminho);
    return {cidadesViagem, distancias[destino.indice]};
}

list<Cidade*> Sistema::gerarCidadesViagem(vector<int> caminho){
    list<Cidade*> cidadesV;
    Cidade* aux = nullptr;
    for (int i : caminho){
        for (auto &c : cidades){
            if(c->indice == i){
                aux = c;
                cidadesV.push_back(aux);
                // delete aux;
            }
        }
    }
    return cidadesV;
}

pair<vector<int>, vector<int>> Sistema::dijkstra(int origem, const vector<vector<Edge>>& grafo) {
    
    int n = grafo.size();
    //cout << trajetos.size() << endl;
    vector<int> distancias(n, INT_MAX); // Vetor para armazenar as menores distâncias
    vector<int> antecessor(n, -1);      // Vetor para armazenar o caminho
    distancias[origem] = 0;

    // Min-heap para escolher o próximo nó com a menor distância
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origem});

    while (!pq.empty()) {
        int distanciaAtual = pq.top().first;
        int cidadeAtual = pq.top().second;
        pq.pop();

        if (distanciaAtual > distancias[cidadeAtual]) continue;

        for (const Edge& vizinho : grafo[cidadeAtual]) {
            int novaDistancia = distanciaAtual + vizinho.distancia;

            if (novaDistancia < distancias[vizinho.destino]) {
                distancias[vizinho.destino] = novaDistancia;
                antecessor[vizinho.destino] = cidadeAtual; // Armazena o caminho
                pq.push({novaDistancia, vizinho.destino});
            }
        }
    }

    return {distancias, antecessor};
}

vector<int> Sistema::reconstruirCaminho(int origem, int destino, const vector<int>& antecessor) {
    vector<int> caminho;
    for (int at = destino; at != -1; at = antecessor[at]) {
        caminho.push_back(at);
        if (at == origem) break;
    }
    reverse(caminho.begin(), caminho.end());
    return caminho;
}
