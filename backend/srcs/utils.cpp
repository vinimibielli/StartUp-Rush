#include "./include/utils.h"

void printListStartUps(std::vector<StartUp*> listStartUps){
    if(listStartUps.size() == 0){
        std::cout << "Nenhuma StartUp cadastrada." << std::endl;
    } else{
        for (int i = 0; i < listStartUps.size(); i++) {
            std::cout << "StartUp " << i+1;
            std::cout << ": Nome: " << listStartUps[i]->getName();
            std::cout << " - Slogan: " << listStartUps[i]->getSlogan();
            std::cout << " - Fundação: " << listStartUps[i]->getFoundation();
            std::cout << " - Pontos " << listStartUps[i]->getPoints() << std::endl;
        }
    }
    return;
}

void printListBattles(std::vector<std::pair<StartUp*, StartUp*>> Battles){
        for (int i = 0; i < Battles.size(); i++) {
            std::cout << "Batalha " << i+1 << ": " << Battles[i].first->getName() << " x " << Battles[i].second->getName() << std::endl;
        }
}

std::vector<StartUp*> ordeningPointsRanking(std::vector<StartUp*> listStartUps){
    StartUp* aux;
    for(int i = 0; i < listStartUps.size(); i++){
        for(int j = i; j < listStartUps.size(); j++){
            if(listStartUps[i]->getPoints() < listStartUps[j]->getPoints()){
                aux = listStartUps[i];
                listStartUps[i] = listStartUps[j];
                listStartUps[j] = aux;
            }
        }
    }

    return listStartUps;
}

StartUp* executeStartUpRush(std::vector<StartUp*> listStartUps){
    std::vector<std::pair<StartUp*, StartUp*>> Battles;
    
    while(listStartUps.size() != 1){
        //Battles = randomBattles(listStartUps);
        listStartUps = executeRoundBattles(Battles);
    }

    return listStartUps[0];
}

std::vector<Battle*>* randomBattles(std::vector<StartUp*> listStartUps){
    int i;
    int ID = 0;
    StartUp *auxFirst, *auxSecond;
    Battle* battle = new Battle();
    std::vector<Battle*>* Battles;
    while(listStartUps.size() > 1){
        battle->setID(ID);

        i = rand()%(listStartUps.size()) + 0;
        battle->setStartUpA(listStartUps[i]);
        listStartUps.erase(listStartUps.begin() + i);

        i = rand()%(listStartUps.size()) + 0;
        battle->setStartUpA(listStartUps[i]);


        Battles->push_back(battle);
        listStartUps.erase(listStartUps.begin() + i);

    }

    return Battles;
}

std::vector<StartUp*> executeRoundBattles(std::vector<std::pair<StartUp*, StartUp*>> Battles){
    std::vector<StartUp*> classifiedStartUps;
    int selectOption;
    std::pair<StartUp*, StartUp*> Battle;
    while(Battles.size() != 0){
        printListBattles(Battles);
        std::cout << "Selecione a batalha que irá ser o jurado: ";
        std::cin >> selectOption;
        Battle = Battles[(selectOption - 1)];
        classifiedStartUps.push_back(executeSingleBattle(Battle));
        Battles.erase(Battles.begin() + (selectOption - 1));
    }
    return classifiedStartUps;
    
}

StartUp* executeSingleBattle(std::pair<StartUp*, StartUp*> Battle){

    PossibleEvents eventsA = *(Battle.first->Events);
    PossibleEvents eventsB = *(Battle.second->Events);

    std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events = {
        {1, std::make_pair(&PossibleEvents::setConvincentPitch, &PossibleEvents::getConvincentPitch)},
        {2, std::make_pair(&PossibleEvents::setProductsBugs, &PossibleEvents::getProductsBugs)},
        {3, std::make_pair(&PossibleEvents::setUserTrack, &PossibleEvents::getUserTrack)},
        {4, std::make_pair(&PossibleEvents::setAngryInvestor, &PossibleEvents::getAngryInvestor)},
        {5, std::make_pair(&PossibleEvents::setPitchFakeNews, &PossibleEvents::getPitchFakeNews)},
    };

    int i, selectEvent, selectStartUps;
    StartUp* Vencedor;
    std::cout << std::endl << "-------------------------------VAMOS PARA A BATALHA!!!!!!!!!!-------------------------------------" << std::endl;
    std::cout << "                           " << Battle.first->getName() << " - " << Battle.first->getPoints() << " PONTOS x " << Battle.second->getName() << " - " << Battle.second->getPoints() << " PONTOS" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl << std::endl;

    while(true){

        std::cout << "Valor do evento: ";
        std::cin >> selectEvent;

        if(selectEvent == 6){
            break;
        }

        if(events.find(selectEvent) != events.end()){
            
            std::cout << "Marque a opção desejada: " << std::endl;

            if(!(events[selectEvent].second(eventsA).first) && (!(events[selectEvent].second(eventsB).first))){
                std::cout << "1- " << Battle.first->getName() << std::endl
                          << "2- " << Battle.second->getName() << std::endl
                          << "3- Ambas as startups" << std::endl;
            } else {
                if(!(events[selectEvent].second(eventsA).first)){
                    std::cout << "1- Apenas a startup " << Battle.first->getName() << " esta disponivel" << std::endl;
                }
                else if(!(events[selectEvent].second(eventsB).first)){
                    std::cout << "1- Apenas a startup " << Battle.second->getName() << " esta disponivel" << std::endl;
                }
                else {
                    std::cout << "Nenhuma startup esta disponivel para este evento" << std::endl;
                    continue;
                }
            }

            std::cin >> selectStartUps;

            if(selectStartUps == 1){
                if(!(events[selectEvent].second(eventsA).first)){
                    events[selectEvent].first(eventsA);
                } else{
                    events[selectEvent].first(eventsB);
                } 

            }
            if(selectStartUps == 2){
                events[selectEvent].first(eventsB); 
            }
            if(selectStartUps == 3){
                events[selectEvent].first(eventsA);
                events[selectEvent].first(eventsB); 
            }
            if(selectStartUps < 1 || selectStartUps > 3){
                std::cout << "Valor inválido, por favor insira apenas os valores possíveis." << std::endl;
            }
        } else{
            std::cout << "Nenhuma atividade esta disponivel para este evento" << std::endl;
            continue;
        }

        //std::cout << "Nome: " << Battle.first->getName() << " Convincent Pitch: " << eventsA.getConvincentPitch().first << " Product Bugs: " << eventsA.getProductsBugs().first << " User Track: " << eventsA.getUserTrack().first << " Angry Investor: " << eventsA.getAngryInvestor().first << " Fake News Pitch: " << eventsA.getPitchFakeNews().first << std::endl;
        //std::cout << "Nome: " << Battle.second->getName() << " Convincent Pitch: " << eventsB.getConvincentPitch().first << " Product Bugs: " << eventsB.getProductsBugs().first << " User Track: " << eventsB.getUserTrack().first << " Angry Investor: " << eventsB.getAngryInvestor().first << " Fake News Pitch: " << eventsB.getPitchFakeNews().first << std::endl;
        

    }

    Battle.first->editPoints(eventsA.valueEvents());
    Battle.second->editPoints(eventsB.valueEvents());

    eventsA.cleanBools();
    eventsB.cleanBools();

    *(Battle.first->Events) = eventsA;
    *(Battle.second->Events) = eventsB;

    std::cout << "Nome: " << Battle.first->getName() << " Pontos: " << Battle.first->getPoints() << std::endl;
    std::cout << "Nome: " << Battle.second->getName() << " Pontos: " << Battle.second->getPoints() << std::endl;

    if(Battle.first->getPoints() > Battle.second->getPoints()){
        Vencedor = Battle.first;
    } else if(Battle.first->getPoints() < Battle.second->getPoints()){
        Vencedor = Battle.second; 
    } else {
        i = rand() % 2;
        if(i == 1){
            Vencedor = Battle.first;
        } else {
            Vencedor = Battle.second;
        }

    }


    Vencedor->winBattlePoints();

    return Vencedor;
}