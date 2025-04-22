#include "./include/main.h"

using json = nlohmann::json;



int main(){

    srand(time(0));

    crow::SimpleApp app;

    std::unordered_set<std::string> nameStartUps;
    std::vector<StartUp*> listStartUps;
    std::vector<StartUp*> classifiedStartUps;

    listStartUps.push_back(new StartUp("Dell", "The power to do more", 2016));
    listStartUps.push_back(new StartUp("HP", "Keep Reinventing", 1939));
    listStartUps.push_back(new StartUp("Lenovo", "Smarter technology for all", 1984));
    listStartUps.push_back(new StartUp("Asus", "In Search of Incredible", 1989));
    listStartUps.push_back(new StartUp("Acer", "Explore beyond limits", 1974));
    listStartUps.push_back(new StartUp("Apple", "Think different", 1976));
    listStartUps.push_back(new StartUp("Sony", "make.believe", 1946));
    listStartUps.push_back(new StartUp("Samsung", "Do What You Can't", 1969));
    
    std::vector<Battle*>* listBattles;

    std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events = {
        {1, std::make_pair(&PossibleEvents::setConvincentPitch, &PossibleEvents::getConvincentPitch)},
        {2, std::make_pair(&PossibleEvents::setProductsBugs, &PossibleEvents::getProductsBugs)},
        {3, std::make_pair(&PossibleEvents::setUserTrack, &PossibleEvents::getUserTrack)},
        {4, std::make_pair(&PossibleEvents::setAngryInvestor, &PossibleEvents::getAngryInvestor)},
        {5, std::make_pair(&PossibleEvents::setPitchFakeNews, &PossibleEvents::getPitchFakeNews)},
    };

    //-------------------------------------INICIO-------------------------------------------------------

    CROW_ROUTE(app, "/static/<string>")([](const crow::request& req, std::string filename) {
     
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

    CROW_ROUTE(app, "/")([](){

        std::ifstream file("./frontend/pages/index.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
        
    });

    CROW_ROUTE(app, "/adicionar")([](){

        std::ifstream file("./frontend/pages/adicionar.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/remover")([](){

        std::ifstream file("./frontend/pages/remover.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/lista")([](){

        std::ifstream file("./frontend/pages/lista.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/batalhas")([](){

        std::ifstream file("./frontend/pages/batalhas.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/eventos")([](){

        std::ifstream file("./frontend/pages/eventos.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/alvo")([](){

        std::ifstream file("./frontend/pages/alvo.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/vencedor")([](){

        std::ifstream file("./frontend/pages/vencedor.html");

        if (!file) {
            std::cerr << "Erro: index.html não encontrado!" << std::endl;
            return crow::response(404, "HTML não encontrado");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/add_startup").methods("POST"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
        try{

            auto dados = json::parse(req.body);

            if(!dados.contains("name") || !dados.contains("slogan") || !dados.contains("foundation")){
                return createJSON(400, "Dados inválidos", "");
            }

            std::string startupName = dados["name"];
            std::string startupSlogan = dados["slogan"];
            int startupFoundation = dados["foundation"];

            if(nameStartUps.find(startupName) == nameStartUps.end()){
                nameStartUps.insert(startupName);
                listStartUps.push_back(new StartUp(startupName, startupSlogan, startupFoundation));
                return createJSON(201, "A startUp foi adicionada!", "/");
            } else{
                return createJSON(400, "StartUp já existente.", "");
            }

        } catch (const nlohmann::json::exception& e) {
            return createJSON(500, "Erro no JSONTESTE", "");
        } catch(...){
            return createJSON(500, "Erro ao adicionar a StartUp.", "");
        }
        
    });

    CROW_ROUTE(app, "/remove_startup").methods("DELETE"_method)([&listStartUps, &nameStartUps](const crow::request& req) {
       try{
            auto dados = json::parse(req.body);
            std::string startupName = dados["name"];


            if(nameStartUps.find(startupName) != nameStartUps.end()){
                for(int i = 0; i < listStartUps.size(); i++){
                    if(listStartUps[i]->getName() == startupName){
                        listStartUps.erase(listStartUps.begin() + i);
                        nameStartUps.erase(startupName);
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

    CROW_ROUTE(app, "/show_startups").methods("GET"_method)([&listStartUps](const crow::request& req) {
       
        json startupsJSON = json::array();

        for(int i = 0; i < listStartUps.size(); i++){
            startupsJSON.push_back({
                {"name", listStartUps[i]->getName()},
                {"slogan", listStartUps[i]->getSlogan()},
                {"foundation", listStartUps[i]->getFoundation()}
            });
        }

        crow::response res(startupsJSON.dump());
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
});

CROW_ROUTE(app, "/start_battle").methods("POST"_method)([listStartUps, &listBattles](const crow::request& req) {
    
    if((listStartUps.size() != 4) && (listStartUps.size() != 8)){
        return createJSON(400, "Insira um número válido de StartUps", "");
    } 
    
    listBattles = randomBattles(listStartUps);
    
    return createJSON(200, "Batalhas foram iniciadas!", "/batalhas");
    
});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------CONFRONTOS-----------------------------------------------------------

CROW_ROUTE(app, "/battles").methods("GET"_method)([&listBattles](const crow::request& req) {
    
    json battlesAvaliables = json::array();
    
    for(const auto aux : *listBattles){
        battlesAvaliables.push_back({{"battle", aux->getID()}, {"status", aux->getFinalized()}, {"nameA", aux->getStartUpA()->getName()}, {"nameB", aux->getStartUpB()->getName()}});
    }

    crow::response res(battlesAvaliables.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res; 

});

CROW_ROUTE(app, "/battle/<int>/finalize").methods("POST"_method)([&listBattles, &classifiedStartUps](const crow::request& req, int idBattle) {
    
    Battle* battle = (*listBattles)[idBattle];
    battle->setFinalized();
    
    PossibleEvents* eventsA = (battle->getStartUpA()->Events);
    PossibleEvents* eventsB = (battle->getStartUpB()->Events);

    StartUp* Vencedor;

    battle->getStartUpA()->editPoints(eventsA->valueEvents());
    battle->getStartUpB()->editPoints(eventsB->valueEvents());

    eventsA->cleanBools();
    eventsB->cleanBools();

    if(battle->getStartUpA()->getPoints() > battle->getStartUpB()->getPoints()){
        Vencedor = battle->getStartUpA();
    } else if(battle->getStartUpA()->getPoints() < battle->getStartUpB()->getPoints()){
        Vencedor = battle->getStartUpB(); 
    } else {
        int i = rand() % 2;
        if(i == 1){
            Vencedor = battle->getStartUpA();
        } else {
            Vencedor = battle->getStartUpB();
        }

    }

    
    Vencedor->winBattlePoints();
    classifiedStartUps.push_back(Vencedor);

    if(battle->getFinalized() == true && (listBattles->size() == 1)){
        return createJSON(200, "O vencedor foi determinado!", "/vencedor");
    }
    for(const auto aux : *listBattles){
        if(aux->getFinalized() == false){
            return createJSON(200, "Ainda restam batalhas.", "/batalhas");
    }
    }

    for (Battle* aux : *listBattles) {
        delete aux; // desaloca o objeto apontado
    }
    
    listBattles = randomBattles(classifiedStartUps);
    classifiedStartUps.clear();
        
    return createJSON(200, "Novas batalhas foram sorteadas.", "/batalhas");

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------EVENTOS-----------------------------------------------------------

CROW_ROUTE(app, "/battle/<int>/events").methods("GET"_method)([](const crow::request& req, int idBattle) {
    
    json eventsAvaliables = json::array();
    eventsAvaliables = {
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

CROW_ROUTE(app, "/battle/<int>/events/<int>/targetlist").methods("GET"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    Battle* battle = (*listBattles)[idBattle];
    PossibleEvents eventsA = *(battle->getStartUpA()->Events);
    PossibleEvents eventsB = *(battle->getStartUpB()->Events);

    json messageOption;

    if(events.find(idEvent) != events.end()){

        if(!(events[idEvent].second(eventsA).first) && (!(events[idEvent].second(eventsB).first))){
            messageOption = {
                {{"id", "usuarioA"}, {"status", "avaliable"}, {"name", battle->getStartUpA()->getName()}},
                {{"id", "usuarioB"}, {"status", "avaliable"}, {"name", battle->getStartUpB()->getName()}},
                {{"id", ""}, {"status", "avaliable"}, {"name", "Ambas"}}
            };
        
        } else {
            if(!(events[idEvent].second(eventsA).first)){
                messageOption = {
                    {{"id", "usuarioA"}, {"status", "avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "usuarioB"}, {"status", "not avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
            else if(!(events[idEvent].second(eventsB).first)){
                messageOption = {     
                    {{"id", "usuarioA"}, {"status", "not avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "usuarioB"}, {"status", "avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
            else {
                messageOption = {     
                    {{"id", "usuarioA"}, {"status", "not avaliable"}, {"name", battle->getStartUpA()->getName()}},
                    {{"id", "usuarioB"}, {"status", "not avaliable"}, {"name", battle->getStartUpB()->getName()}},
                    {{"id", ""}, {"status", "not avaliable"}, {"name", "Ambas"}}
                };
            }
        }

    }
    crow::response res(messageOption.dump(0));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
});

CROW_ROUTE(app, "/battle/<int>/events/<int>/target").methods("POST"_method)([&listBattles, &events](const crow::request& req, int idBattle, int idEvent) {

    Battle* battle = (*listBattles)[idBattle];
    PossibleEvents* eventsA = (battle->getStartUpA()->Events);
    PossibleEvents* eventsB = (battle->getStartUpB()->Events);
    std::string location = "/eventos";

    auto option = json::parse(req.body);

    std::string stringOption = option["name"];

    if(stringOption == "usuarioA"){
        events[idEvent].first(*eventsA);
        return createJSON(201, "Evento realizado.", location);
    } else if(stringOption == "usuarioB"){
        events[idEvent].first(*eventsB);
        return createJSON(202, "Evento realizado.", location);
    } else{
        events[idEvent].first(*eventsA);
        events[idEvent].first(*eventsB);
        return createJSON(203, "Evento realizado.", location);
    }

    return createJSON(200, "Evento realizado.", location);
    

});

//--------------------------------------------------------------------------------------------------------

//-------------------------------------FINAL--------------------------------------------------------------

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

//--------------------------------------------------------------------------------------------------------



app.port(8080).multithreaded().run();

}

crow::response createJSON(int status, std::string message, std::string next){
    json resposta;
    resposta["message"] = message;
    if(!next.empty()){
        resposta["next"] = next;
    }

    crow::response res(status, resposta.dump(4));
    res.set_header("Access-Control-Allow-Origin", "*");
    return res;
}
