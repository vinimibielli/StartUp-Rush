#include "./include/main.h"

using json = nlohmann::json;



int main(){

    srand(time(0));

    crow::SimpleApp app;

    std::unordered_set<std::string> nameStartUps;
    std::vector<StartUp*> listStartUps;
    std::vector<StartUp*>* classifiedStartUps;
    
    std::vector<Battle*>* listBattles;

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

CROW_ROUTE(app, "/start_battle").methods("POST"_method)([&listStartUps, &listBattles](const crow::request& req) {
    
    if((listStartUps.size() != 4) && (listStartUps.size() != 8)){
        return crow::response(400, "Erro ao iniciar o StartUpRush, por favor inclua a quantidade correta de participantes.");
    } 
    
    listBattles = randomBattles(listStartUps);

    json battlesJson = json::array();
    for(const auto aux : *listBattles){
        battlesJson.push_back({
            {"startup 1", {"name", aux->getStartUpA()->getName()}},
            {"startup 2", {"name", aux->getStartUpB()->getName()}}
    });
    }

    return crow::response(battlesJson.dump(4));

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------CONFRONTOS-----------------------------------------------------------

CROW_ROUTE(app, "/battles").methods("GET"_method)([&listBattles](const crow::request& req) {
    
    json battlesAvaliables = json::array();
    
    for(const auto aux : *listBattles){
        battlesAvaliables.push_back({{"battle", aux->getID()},{{"name", aux->getStartUpA()->getName()}, {"name", aux->getStartUpB()->getName()}}});
    }

    return crow::response(battlesAvaliables.dump(4)); 

});

CROW_ROUTE(app, "/battle/<int>/finalize").methods("POST"_method)([&listBattles](const crow::request& req, int idBattle) {
    
//SÓ FALTA FAZER A PARTE DE FINALIZAR A RODADA E DEPOIS IR PARA O JAVA SCRIPT

    Battle* battle = (*listBattles)[idEvent];
    battle->setFinalized();
    
    PossibleEvents* eventsA = *(battle->getStartUpA()->Events);
    PossibleEvents* eventsB = *(battle->(&getStartUpB()->Events)); // ver se isso está certo e mudar no outro também

    Battle.first->editPoints(eventsA.valueEvents());
    Battle.second->editPoints(eventsB.valueEvents());

    eventsA.cleanBools();
    eventsB.cleanBools();

    *(Battle.first->Events) = eventsA;
    *(Battle.second->Events) = eventsB;

    event
    
    

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------EVENTOS-----------------------------------------------------------

CROW_ROUTE(app, "/battle/<int>/events").methods("GET"_method)([](const crow::request& req, int idBattle) {
    
    json eventsAvaliables = {
        {{"id", 1},{"Convincent Pitch"}},
        {{"id", 2},{"Product Bugs"}},
        {{"id", 3},{"User Track"}},
        {{"id", 4},{"Angry Investor"}},
        {{"id", 5},{"Fake News Pitch"}}
    };
    
    return crow::response(eventsAvaliables.dump(4));
});

CROW_ROUTE(app, "/battle/<int>/event/<int>/target").methods("GET"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    Battle* battle = (*listBattles)[idEvent];
    PossibleEvents eventsA = *(battle->getStartUpA()->Events);
    PossibleEvents eventsB = *(battle->getStartUpB()->Events);

    json messageOption;

    if(events.find(idEvent) != events.end()){

        if(!(events[idEvent].second(eventsA).first) && (!(events[idEvent].second(eventsB).first))){
            messageOption = {
                {{"avaliable"}, {"name", battle->getStartUpA()->getName()}},
                {{"avaliable"}, {"name", battle->getStartUpB()->getName()}},
                {{"avaliable"}, {"name", "Ambas"}}
            };
        
        } else {
            if(!(events[idEvent].second(eventsA).first)){
                messageOption = {
                    {{"avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"not avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"not avaliable"}, {"name", "Ambas"}}
                };
            }
            else if(!(events[idEvent].second(eventsB).first)){
                messageOption = {     
                    {{"not avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"not avaliable"}, {"name", "Ambas"}}
                };
            }
            else {
                return crow::response("Nenhuma opção disponível");
            }
        }
    }
    return crow::response(messageOption.dump(4));
});

CROW_ROUTE(app, "/battle/<int>/event/<int>/target").methods("POST"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    Battle* battle = (*listBattles)[idEvent];
    PossibleEvents* eventsA = *(battle->getStartUpA()->Events);
    PossibleEvents* eventsB = *(battle->getStartUpB()->Events);

    auto option = json::parse(req.body);

    std::string stringOption = option["name"];

    if("name" == "usuarioA"){
        events[idEvent].first(eventsA);
    } else if("name" == "usuarioB"){
        events[idEvent].first(eventsB);
    } else{
        events[idEvent].first(eventsA);
        events[idEvent].first(eventsB);
    }

    std::string location = "/battle/" + std::to_string(idBattle) + "/events";

    json resposta = {
        {"next", location}
    };

    return crow::response(200, resposta);

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------FINAL--------------------------------------------------------------

CROW_ROUTE(app, "/final_results").methods("GET"_method)([&listStartUps, &classifiedStartUps](const crow::request& req, int idBattle) {

    StartUp* Vencedor = (*classifiedStartUps)[0];
    
    json vencedorJSON = {
        {"name", Vencedor->getName()},
        {"slogan", Vencedor->getSlogan()}
    };

    std::vector<StartUp*> ordeningList = ordeningPointsRanking(listStartUps);

    json startupsJSON = json::array();

    for(int i = 0; i < ordeningList.size(); i++){
        startupsJSON.push_back({
            {"name", ordeningList[i]->getName()},
            {"slogan", ordeningList[i]->getSlogan()},
            {"foundation", ordeningList[i]->getFoundation()},
            {"points", ordeningList[i]->getPoints()},
            {"convincent pitch", ordeningList[i]->Events->getConvincentPitch()},
            {"product bugs", ordeningList[i]->Events->getProductsBugs()},
            {"user track", ordeningList[i]->Events->getUserTrack()},
            {"angry investor", ordeningList[i]->Events->getAngryInvestor()},
            {"fake new pitch", ordeningList[i]->Events->getPitchFakeNews()}
        });
    }

    json resposta = {
        {"vencedor", vencedorJSON},
        {"points ranking", startupsJSON}
    };

    return crow::response(vencedorJSON.dump());
});

//--------------------------------------------------------------------------------------------------------



app.port(8080).multithreaded().run();

}
