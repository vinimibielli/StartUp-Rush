#include "./include/main.h"

using json = nlohmann::json;



int main(){

    srand(time(0));

    crow::SimpleApp app;

    std::unordered_set<std::string> nameStartUps;
    std::vector<StartUp*> listStartUps;

    std::unordered_map<int, std::pair<StartUp*, StartUp*>>* listBattles;
    std::pair<StartUp*, StartUp*>* battle;

    std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events = {
        {1, std::make_pair(&PossibleEvents::setConvincentPitch, &PossibleEvents::getConvincentPitch)},
        {2, std::make_pair(&PossibleEvents::setProductsBugs, &PossibleEvents::getProductsBugs)},
        {3, std::make_pair(&PossibleEvents::setUserTrack, &PossibleEvents::getUserTrack)},
        {4, std::make_pair(&PossibleEvents::setAngryInvestor, &PossibleEvents::getAngryInvestor)},
        {5, std::make_pair(&PossibleEvents::setPitchFakeNews, &PossibleEvents::getPitchFakeNews)},
    };

    //-------------------------------------INICIO-------------------------------------------------------

    CROW_ROUTE(app, "/")([](){

        std::string html = R"(
            <!DOCTYPE html>
            <html lang="pt-BR">
                <head>
                    <meta charset="UTF-8">
                    <meta http-equiv="X-UA-Compatible"  content="IE=edge">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>StartUp Rush</title>
                </head>
                <body>
                    <h1>Bem vindo a StartUp Rush!</h1>
                    <h2>Selecione a opcao desejada:</h2>
                    <ul>
                        <li><a href="/add_startup">Cadastro de StartUp</a></li>
                        <li><a href="/remove_startup">Remova uma StartUp</a></li>
                        <li><a href="/show_startups">Lista de StartUps participantes</a></li>
                        <li><a href="/start_battle">Iniciar StartUp Rush</a></li>
                    </ul>
                </body>
            </html>
        )";

        return crow::response(html);
    });


    CROW_ROUTE(app, "/add_startup").methods("POST"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
        try{

            auto dados = json::parse(req.body);

            if(!dados.contains("name") || !dados.contains("slogan") || !dados.contains("foundation")){
                return crow::response(400, "Dados inválidos");
            }

            std::string startupName = dados["name"];
            std::string startupSlogan = dados["slogan"];
            int startupFoundation = dados["foundation"];

            if(nameStartUps.find(startupName) == nameStartUps.end()){
                nameStartUps.insert(startupName);
                listStartUps.push_back(new StartUp(startupName, startupSlogan, startupFoundation));
                return crow::response(200, "A startUp foi adicionada!"); 
            } else{
                return crow::response(500, "StartUp já existente."); 
            }

        } catch (const nlohmann::json::exception& e) {
            return crow::response(400, "Erro no JSON.");
        } catch(...){
            return crow::response(500, "Erro ao adicionar a StartUp.");
        }
        
    });

    CROW_ROUTE(app, "/remove_startup").methods("DELETE"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
       
            auto dados = json::parse(req.body);
            std::string startupName = dados["name"];


            if(nameStartUps.find(startupName) != nameStartUps.end()){
                for(int i = 0; i < listStartUps.size(); i++){
                    if(listStartUps[i]->getName() == startupName){
                        listStartUps.erase(listStartUps.begin() + i);
                        break;
                    }
                }
                return crow::response(200, "A startUp foi removida!");
            }
            else{
                return crow::response(500, "StartUp não foi encontrada.");
            }
    });

    CROW_ROUTE(app, "/show_startups").methods("GET"_method)([&listStartUps](const crow::request& req) {
       
        json startupsJSON = json::array();

        for(int i = 0; i < listStartUps.size(); i++){
            startupsJSON.push_back({
                {"name", listStartUps[i]->getName()},
                {"slogan", listStartUps[i]->getSlogan()},
                {"foundation", listStartUps[i]->getFoundation()}
            });
        }

        return crow::response(startupsJSON.dump(4));
});

CROW_ROUTE(app, "/start_battle").methods("POST"_method)([&listStartUps](const crow::request& req) {
    
    if((listStartUps.size() != 4) && (listStartUps.size() != 8)){
        return crow::response(400, "Erro ao iniciar o StartUpRush, por favor inclua a quantidade correta de participantes.");
    }
    
    return crow::response(); //FINALIZAR ISSO

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------SORTEIO-----------------------------------------------------------

CROW_ROUTE(app, "/random_battles").methods("POST"_method)([&listStartUps, &listBattles](const crow::request& req) {
    
    listBattles->clear();
    listBattles = randomBattles(listStartUps);

    json battlesJson = json::array();
    for(const auto aux : *listBattles){
        battlesJson.push_back({
            {"startup 1", {"name", aux.second.first->getName()}},
            {"startup 2", {"name", aux.second.second->getName()}}
    });
    }

    return crow::response(battlesJson.dump(4));

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------CONFRONTOS-----------------------------------------------------------

CROW_ROUTE(app, "avaliables_battles").methods("GET"_method)([&listBattles](const crow::request& req) {
    
    json battlesAvaliables = json::array();
    
    for(const auto aux : *listBattles){
        battlesAvaliables.push_back({{"battle", aux.first},{{"name", aux.second.first->getName()}, {"name", aux.second.second->getName()}}});
    }

    return crow::response(battlesAvaliables.dump(4));

});

CROW_ROUTE(app, "single_battle/<int>").methods("POST"_method)([&listBattles, &battle](const crow::request& req, int id) {
    
    *battle = (*listBattles)[id];    
    

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------EVENTOS-----------------------------------------------------------

CROW_ROUTE(app, "avaliables_events").methods("GET"_method)([](const crow::request& req) {
    
    json eventsAvaliables = {
        {{"id", 1},{"Convincent Pitch"}},
        {{"id", 2},{"Product Bugs"}},
        {{"id", 3},{"User Track"}},
        {{"id", 4},{"Angry Investor"}},
        {{"id", 5},{"Fake News Pitch"}}
    };
    
    return crow::response(eventsAvaliables.dump(4));
});

CROW_ROUTE(app, "avaliables_startups/").methods("GET"_method)([&battle, &events](const crow::request& req, int id) {

    PossibleEvents eventsA = *(battle->first->Events);
    PossibleEvents eventsB = *(battle->second->Events);

    json messageOption;

    if(events.find(id) != events.end()){

        if(!(events[id].second(eventsA).first) && (!(events[id].second(eventsB).first))){
            messageOption = {
                {"name", battle->first->getName()},
                {"name", battle->second->getName()},
                {"name", "Ambas"}
            };
        
        } else {
            if(!(events[id].second(eventsA).first)){
                messageOption = {
                    {"name", battle->first->getName()},
                };
            }
            else if(!(events[id].second(eventsB).first)){
                messageOption = {
                    {"name", battle->second->getName()},
                };
            }
            else {
                return crow::response("Nenhuma opção disponível");
            }
        }
    }
    return crow::response(messageOption.dump(4));
});

CROW_ROUTE(app, "avaliables_startups/").methods("POST"_method)([&battle, &events](const crow::request& req, int id) {

    PossibleEvents eventsA = *(battle->first->Events);
    PossibleEvents eventsB = *(battle->second->Events);

    auto dados = json::parse(req.body);

    json messageOption;

    if(dados == 1){
        if(!(events[id].second(eventsA).first)){
            events[id].first(eventsA);
        } else{
            events[id].first(eventsB);
        } 

    }
    if(dados == 2){
        events[id].first(eventsB); 
    }
    if(dados == 3){
        events[id].first(eventsA);
        events[id].first(eventsB); 
    }
    if(dados < 1 || dados > 3){
        return crow::response("Valor inválido, por favor insira apenas os valores possíveis.");
    }

    return crow::response();
});

app.port(8080).multithreaded().run();

}
/*
StartUp* Vencedor = executeStartUpRush(listStartUps);

        json vencedorJSON = {
            {"name", Vencedor->getName()},
            {"slogan", Vencedor->getSlogan()}
        };

        std::vector<StartUp*> ordeningList = ordeningPointsRanking(listStartUps);

        json startupsJSON = json::array();

        for(int i = 0; i < listStartUps.size(); i++){
            startupsJSON.push_back({
                {"name", listStartUps[i]->getName()},
                {"slogan", listStartUps[i]->getSlogan()},
                {"foundation", listStartUps[i]->getFoundation()},
                {"points", listStartUps[i]->getPoints()},
                {"convincent pitch", listStartUps[i]->Events->getConvincentPitch()},
                {"product bugs", listStartUps[i]->Events->getProductsBugs()},
                {"user track", listStartUps[i]->Events->getUserTrack()},
                {"angry investor", listStartUps[i]->Events->getAngryInvestor()},
                {"fake new pitch", listStartUps[i]->Events->getPitchFakeNews()}
            });
        }

        json resposta = {
            {"vencedor", vencedorJSON},
            {"points ranking", startupsJSON}
        };

        return crow::response(vencedorJSON.dump());

    }*/
