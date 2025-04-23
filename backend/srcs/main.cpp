#include "./include/main.h"

using json = nlohmann::json;

int main(){

    srand(time(0)); // gerando uma nova seed para garantir um sorteio aleatório

    crow::SimpleApp app; // simpleApp da biblioteca crow

    std::unordered_set<std::string> nameStartUps; // unordered_set que será responsável por armazenar o nome das StartUps participantes
    std::vector<StartUp*> listStartUps; // vector onde estará armazenado as StartUps adicionadas
    std::vector<StartUp*> classifiedStartUps; // vector que armazenará as StartUps classificadas para não ter interferência com a lista original
    
    std::vector<Battle*>* listBattles; // vector das batalhas, este será atribuido sempre que um novo sorteio for feito

    // unordered_map referente aos eventos possíveis, desta forma é evitado uma repetição grande de if/else ou switch
    std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events = {
        {1, std::make_pair(&PossibleEvents::setConvincentPitch, &PossibleEvents::getConvincentPitch)},
        {2, std::make_pair(&PossibleEvents::setProductsBugs, &PossibleEvents::getProductsBugs)},
        {3, std::make_pair(&PossibleEvents::setUserTrack, &PossibleEvents::getUserTrack)},
        {4, std::make_pair(&PossibleEvents::setAngryInvestor, &PossibleEvents::getAngryInvestor)},
        {5, std::make_pair(&PossibleEvents::setPitchFakeNews, &PossibleEvents::getPitchFakeNews)},
    };

    //-------------------------------------INICIO-------------------------------------------------------

    CROW_ROUTE(app, "/static/<string>")([](const crow::request& req, std::string filename) { //rota responsável por mandar os statics(css e js) para o html
     
        std::string filePath = "./frontend/static/" + filename;
      
        std::ifstream file(filePath);
        if (!file) {
            return crow::response(404, "File not found");
        }
    
        std::stringstream buffer;
        buffer << file.rdbuf();
      
        std::string contentType = "text/plain"; 
        if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".css") {
            contentType = "text/css";
        } else if (filename.size() >= 3 && filename.substr(filename.size() - 3) == ".js") {
            contentType = "application/javascript";
        } else if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".png") {
            contentType = "image/png";
        } else if ((filename.size() >= 4 && filename.substr(filename.size() - 4) == ".jpg") ||
                   (filename.size() >= 5 && filename.substr(filename.size() - 5) == ".jpeg")) {
            contentType = "image/jpeg";
        }
    
        crow::response res(buffer.str());
        res.set_header("Content-Type", contentType);
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/")([](){ //rota responsável por mostrar o menu de opções (index.html)
        return returnHTML("./frontend/pages/index.html");
    });

    CROW_ROUTE(app, "/adicionar")([](){ //rota responsável por mostrar o cadastro de StartUps (adicionar.html)
        return returnHTML("./frontend/pages/adicionar.html");
    });

    CROW_ROUTE(app, "/remover")([](){ //rota responsável por mostrar a remoção de StartUps (adicionar.html)
        return returnHTML("./frontend/pages/remover.html");
    });

    CROW_ROUTE(app, "/lista")([](){ //rota responsável por mostrar a lista de StartUps (lista.html)
        return returnHTML("./frontend/pages/lista.html");
    });

    CROW_ROUTE(app, "/batalhas")([](){ //rota responsável por mostrar o menu de batalhas (batalhas.html)
        return returnHTML("./frontend/pages/batalhas.html");
    });

    CROW_ROUTE(app, "/eventos")([](){ //rota responsável por mostrar o menu de eventos (eventos.html)
        return returnHTML("./frontend/pages/eventos.html");
    });

    CROW_ROUTE(app, "/alvo")([](){ //rota responsável por mostrar o menu de alvos (alvos.html)
        return returnHTML("./frontend/pages/alvo.html");
    });

    CROW_ROUTE(app, "/vencedor")([](){ //rota responsável por mostrar o vencedor e a tabela final (vencedor.html)
        return returnHTML("./frontend/pages/vencedor.html");
    });

    //rota responsável por fazer a adição de uma nova StartUp
    CROW_ROUTE(app, "/add_startup").methods("POST"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
        try{

            auto dados = json::parse(req.body); //recebe os dados do frontend via POST em um json

            if(!dados.contains("name") || !dados.contains("slogan") || !dados.contains("foundation")){ //verifica se os dados estão corretos
                return createJSON(400, "Dados inválidos", "");
            }

            //atribui os dados para suas referentes variáveis
            std::string startupName = dados["name"];
            std::string startupSlogan = dados["slogan"];
            int startupFoundation = dados["foundation"];

            if(nameStartUps.find(startupName) == nameStartUps.end()){ //verifica no unordered_set se a StartUp já existe, caso não exista a inserção será feita
                nameStartUps.insert(startupName);
                listStartUps.push_back(new StartUp(startupName, startupSlogan, startupFoundation));
                return createJSON(201, "A startUp foi adicionada!", "/");
            } else{
                return createJSON(400, "StartUp já existente.", ""); //retorna que a StartUp já existe
            }

        } catch (const nlohmann::json::exception& e) {
            return createJSON(500, "Erro no JSON", "");
        } catch(...){
            return createJSON(500, "Erro ao adicionar a StartUp.", "");
        }
        
    });

    //rota onde será feita a remoção de uma StartUp
    CROW_ROUTE(app, "/remove_startup").methods("DELETE"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
       try{
            auto dados = json::parse(req.body); //recebe os dados em formato json
            std::string startupName = dados["name"];

            if(nameStartUps.find(startupName) != nameStartUps.end()){ //verifica se a StartUp existe para fazer a remoção
                for(int i = 0; i < listStartUps.size(); i++){
                    if(listStartUps[i]->getName() == startupName){
                        listStartUps.erase(listStartUps.begin() + i); //apaga a StartUp da lista
                        nameStartUps.erase(startupName); //apaga a StartUp da lista de nomes
                        break;
                    }
                }
                return createJSON(200, "A startUp foi removida!", "/");
            }
            else{
                return createJSON(404, "StartUp não foi encontrada.", "");
            }
        } catch (const nlohmann::json::exception& e) {
            return createJSON(500, "Erro no JSON", "");
        } catch(...){
            return createJSON(500, "Erro ao adicionar a StartUp.", "");
        }
    });

    //rota onde será feito o envio das StartUps existentes para o frontend
    CROW_ROUTE(app, "/show_startups").methods("GET"_method)([&listStartUps](const crow::request& req) {
       
        json startupsJSON = json::array(); //cria um array de json

        for(int i = 0; i < listStartUps.size(); i++){ //faz um for que irá adicionar o nome, slogan e data de fundação da StartUp no array
            startupsJSON.push_back({
                {"name", listStartUps[i]->getName()},
                {"slogan", listStartUps[i]->getSlogan()},
                {"foundation", listStartUps[i]->getFoundation()}
            });
        }

        crow::response res(startupsJSON.dump());
        res.set_header("Access-Control-Allow-Origin", "*");
        return res; //envia a resposta ao frontend
});

//rota responsável for coordenar o início das batalhas
CROW_ROUTE(app, "/start_battle").methods("POST"_method)([&listStartUps, &listBattles](const crow::request& req) {
    
    if((listStartUps.size() != 4) && (listStartUps.size() != 8)){ //verifica se a lista de StartUps possui 4 ou 8 usuários
        return createJSON(400, "Insira um número válido (4 ou 8) de StartUps.", "");
    } 
    
    listBattles = randomBattles(listStartUps); //realiza o sorteio das batalhas e insere no vetor listBattles
    
    return createJSON(200, "Batalhas foram iniciadas!", "/batalhas");
    
});

CROW_ROUTE(app, "/auto_battle").methods("POST"_method)([&listStartUps, &listBattles, &classifiedStartUps, &events](const crow::request& req) {
    
    if((listStartUps.size() != 4) && (listStartUps.size() != 8)){ //verifica se a lista de StartUps possui 4 ou 8 usuários
        return createJSON(400, "Insira um número válido (4 ou 8) de StartUps.", "");
    }

    classifiedStartUps = listStartUps;

    while(classifiedStartUps.size() != 1){
        listBattles = randomBattles(classifiedStartUps);
        classifiedStartUps = randomizeBattles(listBattles, events);
    }
    
    return createJSON(200, "Batalhas foram iniciadas!", "/vencedor");
    
});


//--------------------------------------------------------------------------------------------------------

//-------------------------------------CONFRONTOS-----------------------------------------------------------

//rota onde será enviado para o frontend os confrontos disponíveis
CROW_ROUTE(app, "/battles").methods("GET"_method)([&listBattles](const crow::request& req) {
    
    json battlesAvaliables = json::array();
    
    for(const auto aux : *listBattles){ //for onde será montado o arrays de cada batalha
        if(aux->getFinalized() == true){
            if(aux->getStartUpA()->getPoints() > aux->getStartUpB()->getPoints()){
                battlesAvaliables.push_back({{"battle", aux->getID()}, {"status", aux->getFinalized()}, {"nameA", aux->getStartUpA()->getName()}, {"pointsA", aux->getStartUpA()->getPoints()}, {"nameB", aux->getStartUpB()->getName()}, {"pointsB", aux->getStartUpB()->getPoints()}, {"winner", aux->getStartUpA()->getName()}, {"winner", aux->getStartUpA()->getName()}, {"winnerPoints", aux->getStartUpA()->getPoints()}});  
            }
            else{
                battlesAvaliables.push_back({{"battle", aux->getID()}, {"status", aux->getFinalized()}, {"nameA", aux->getStartUpA()->getName()}, {"pointsA", aux->getStartUpA()->getPoints()}, {"nameB", aux->getStartUpB()->getName()}, {"pointsB", aux->getStartUpB()->getPoints()}, {"winner", aux->getStartUpB()->getName()}, {"winnerPoints", aux->getStartUpB()->getPoints()}});  
            }
        }else{
        battlesAvaliables.push_back({{"battle", aux->getID()}, {"status", aux->getFinalized()}, {"nameA", aux->getStartUpA()->getName()}, {"pointsA", aux->getStartUpA()->getPoints()}, {"nameB", aux->getStartUpB()->getName()}, {"pointsB", aux->getStartUpB()->getPoints()}, {"winner", ""}, {"winnerPoints", 0}});
        }
    }

    crow::response res(battlesAvaliables.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res; //envia as batalhas para o frontend

});

//rota responsável por coordenar a finalização das batalhas
CROW_ROUTE(app, "/battle/<int>/finalize").methods("POST"_method)([&listBattles, &classifiedStartUps](const crow::request& req, int idBattle) {
    
    Battle* battle = (*listBattles)[idBattle]; //atribui o valor da batalha específica para a classe Battle
    battle->setFinalized(); //coloca battle como finalizada (por causa disso que battle em cima precisa ser ponteiro)
    
    //pega os eventos realizados pelas StartUps que estão na batalha
    PossibleEvents* eventsA = (battle->getStartUpA()->Events); 
    PossibleEvents* eventsB = (battle->getStartUpB()->Events); 

    StartUp* Vencedor;

    //realiza o cálculo dos eventos que foram realizados
    battle->getStartUpA()->editPoints(eventsA->valueEvents());
    battle->getStartUpB()->editPoints(eventsB->valueEvents());

    //coloca todos os eventos como disponíveis para a próxima batalha
    eventsA->cleanBools();
    eventsB->cleanBools();

    //verifica qual StartUp foi a vencedora e realiza o SharkFight caso necessário
    if(battle->getStartUpA()->getPoints() > battle->getStartUpB()->getPoints()){
        Vencedor = battle->getStartUpA();
    } else if(battle->getStartUpA()->getPoints() < battle->getStartUpB()->getPoints()){
        Vencedor = battle->getStartUpB(); 
    } else {
        int i = rand() % 2;
        if(i == 1){
            battle->getStartUpA()->editPoints(2);
            Vencedor = battle->getStartUpA();
        } else {
            battle->getStartUpB()->editPoints(2);
            Vencedor = battle->getStartUpB();
        }

    }

    Vencedor->winBattlePoints(); //atribui os 30 pontos para a StartUp vencedor
    classifiedStartUps.push_back(Vencedor); //insere a StartUp vencedor na lista de classificados

    if(battle->getFinalized() == true && (listBattles->size() == 1)){ //verifica se a batalha da rodada foi finalizada e se a lista de batalhas é igual a 1
        delete battle;
        return createJSON(200, "O vencedor foi determinado!", "/vencedor"); //caso seja, todas as batalhas foram realizadas e temos um vencedor
    }
    for(const auto aux : *listBattles){ //caso não seja verdade, vai verificar ainda tem alguma batalha que não foi finalizada
        if(aux->getFinalized() == false){
            return createJSON(200, "Ainda restam batalhas.", "/batalhas");
    }
    }

    for (Battle* aux : *listBattles) { //caso todas tenham sido finalizadas, vai fazer o delete da batalha em questão para controle de memória
        delete aux; // desaloca o objeto apontado
    }
    
    listBattles = randomBattles(classifiedStartUps); //irá realizar o sorteio das novas batalhas com as StartUps classificadas
    classifiedStartUps.clear(); //vai limpar a lista das StartUps para a realização da próxima rodada
        
    return createJSON(200, "Novas batalhas foram sorteadas.", "/batalhas");

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------EVENTOS-----------------------------------------------------------

//rota responsável por enviar os eventos disponíveis para o frontend
CROW_ROUTE(app, "/battle/<int>/events").methods("GET"_method)([](const crow::request& req, int idBattle) {
    
    json eventsAvaliables = json::array();
    eventsAvaliables = { //atribuindo ao array de json todos os eventos disponíveis
        {{"id", 1},{"name", "Pitch Convincente (+6)"}},
        {{"id", 2},{"name", "Produto com Bugs (-4)"}},
        {{"id", 3},{"name", "Boa Tração de Usuários (+3)"}},
        {{"id", 4},{"name", "Investidores irritados (-6)"}},
        {{"id", 5},{"name", "Fake News no Pitch (-8)"}}
    };
    
    crow::response res(eventsAvaliables.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
});

//rota responsável por enviar os alvos disponíveis para o frontend
CROW_ROUTE(app, "/battle/<int>/events/<int>/targetlist").methods("GET"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    //pega a batalha que está sendo realizada e logo em seguida seus eventos
    Battle* battle = (*listBattles)[idBattle];
    PossibleEvents eventsA = *(battle->getStartUpA()->Events);
    PossibleEvents eventsB = *(battle->getStartUpB()->Events);

    json messageOption;

    if(events.find(idEvent) != events.end()){ //verifica se o evento em questão existe

        if(!(events[idEvent].second(eventsA).first) && (!(events[idEvent].second(eventsB).first))){ //verifica se está disponível para ambos
            messageOption = {
                {{"id", "StartUpA"}, {"status", "avaliable"}, {"name", battle->getStartUpA()->getName()}},
                {{"id", "StartUpB"}, {"status", "avaliable"}, {"name", battle->getStartUpB()->getName()}},
                {{"id", ""}, {"status", "avaliable"}, {"name", "Ambas"}}
            };
        
        } else {
            if(!(events[idEvent].second(eventsA).first)){ //verifica se está disponível para a primeira StartUp
                messageOption = {
                    {{"id", "StartUpA"}, {"status", "avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "StartUpB"}, {"status", "not avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
            else if(!(events[idEvent].second(eventsB).first)){ //verifica se está disponível para a segunda StartUp
                messageOption = {     
                    {{"id", "StartUpA"}, {"status", "not avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "StartUpB"}, {"status", "avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
            else { //caso esteja indisponível para as duas
                messageOption = { 
                    {{"id", "StartUpA"}, {"status", "not avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "StartUpB"}, {"status", "not avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
        }

    }
    crow::response res(messageOption.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
});

//rota responsável por cadastrar os eventos realizados pelos usuários
CROW_ROUTE(app, "/battle/<int>/events/<int>/target").methods("POST"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    //pega a batalha em questão e suas respectivas listas de eventos
    Battle* battle = (*listBattles)[idBattle];
    PossibleEvents* eventsA = (battle->getStartUpA()->Events);
    PossibleEvents* eventsB = (battle->getStartUpB()->Events);
    std::string location = "/eventos";

    auto option = json::parse(req.body);

    std::string stringOption = option["name"];

    if(stringOption == "StartUpA"){ //verifica através do frontend se foi a StartUpA
        events[idEvent].first(*eventsA);
        return createJSON(200, "Evento realizado.", location);
    } else if(stringOption == "StartUpB"){ //verifica através do frontend se foi a StartUpB
        events[idEvent].first(*eventsB);
        return createJSON(200, "Evento realizado.", location);
    } else{ //caso seja escolhido ambas, as duas irão realizar o evento
        events[idEvent].first(*eventsA);
        events[idEvent].first(*eventsB);
        return createJSON(200, "Evento realizado.", location);
    }

    return createJSON(400, "Nenhum evento realizado.", location);
    

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------FINAL--------------------------------------------------------------

//rota responsável por enviar para o frontend o vencedor a lista final de resultados
CROW_ROUTE(app, "/final_results").methods("GET"_method)([&listStartUps, &classifiedStartUps](const crow::request& req) {

    StartUp* Vencedor = classifiedStartUps[0];
    json startupsJSON = json::array();

    startupsJSON.push_back({
        {"vencedor", "sim"},
        {"name", Vencedor->getName()},
        {"slogan", Vencedor->getSlogan()},
        {"foundation", Vencedor->getFoundation()},
        {"points", Vencedor->getPoints()},
        {"convincent_pitch", Vencedor->Events->getConvincentPitch().second},
        {"product_bugs", Vencedor->Events->getProductsBugs().second},
        {"user_track", Vencedor->Events->getUserTrack().second},
        {"angry_investor", Vencedor->Events->getAngryInvestor().second},
        {"fake_news_pitch", Vencedor->Events->getPitchFakeNews().second}
    });

    std::vector<StartUp*> ordeningList = ordeningPointsRanking(listStartUps);


    for(int i = 0; i < ordeningList.size(); i++){
        if(ordeningList[i] != Vencedor){
        startupsJSON.push_back({
            {"vencedor", "nao"},
            {"name", ordeningList[i]->getName()},
            {"slogan", ordeningList[i]->getSlogan()},
            {"foundation", ordeningList[i]->getFoundation()},
            {"points", ordeningList[i]->getPoints()},
            {"convincent_pitch", ordeningList[i]->Events->getConvincentPitch().second},
            {"product_bugs", ordeningList[i]->Events->getProductsBugs().second},
            {"user_track", ordeningList[i]->Events->getUserTrack().second},
            {"angry_investor", ordeningList[i]->Events->getAngryInvestor().second},
            {"fake_news_pitch", ordeningList[i]->Events->getPitchFakeNews().second}
        });
    }
    }

    crow::response res(startupsJSON.dump());
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
});

//rota responsável por fazer a limpeza dos dados para reiniciar a competição
CROW_ROUTE(app, "/restart_startup").methods("POST"_method)([&listStartUps, &listBattles, &classifiedStartUps, &events](const crow::request& req) {
    

    for (auto startup : listStartUps) {
        delete startup;
    }
    listStartUps.clear();
    classifiedStartUps.clear();

    return createJSON(200, "Reiniciando StartUp Rush!", "/");
    
});

//--------------------------------------------------------------------------------------------------------

app.port(8080).multithreaded().run(); //iniciando o servidor através da porta 8080

for (auto startup : listStartUps) { //realizando a desalocação de memória das startups
    delete startup;
}
listStartUps.clear(); //esvaziando o vector listStartUps
classifiedStartUps.clear(); //esvaziando o vector classifiedStartUps

return 0;

}

//função responsável por criar o json de resposta
crow::response createJSON(int status, std::string message, std::string next){
    json resposta;
    resposta["message"] = message;
    if(!next.empty()){
        resposta["next"] = next;
    }

    crow::response res(status, resposta.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
}

//função responsável por criar o HTML de resposta
crow::response returnHTML(const std::string& filepath){
std::ifstream file(filepath);
    
    if (!file) {
        std::cerr << "Erro: " << filepath << " não encontrado!" << std::endl;
        return crow::response(404, "HTML não encontrado");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    crow::response res(buffer.str());
    res.set_header("Content-Type", "text/html");
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
}