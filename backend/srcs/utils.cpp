#include "./include/utils.h"

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
        //listStartUps = executeRoundBattles(Battles);
    }

    return listStartUps[0];
}

std::vector<Battle*>* randomBattles(std::vector<StartUp*> listStartUps){
    int i;
    int ID = 0;
    std::vector<Battle*>* Battles = new std::vector<Battle*>();
    std::vector<StartUp*> listStartUpsAux = listStartUps;

    while(listStartUpsAux.size() > 1){
        Battle* battle = new Battle();
        battle->setID(ID);

        i = rand()%(listStartUpsAux.size()) + 0;
        battle->setStartUpA(listStartUpsAux[i]);
        listStartUpsAux.erase(listStartUpsAux.begin() + i);

        i = rand()%(listStartUpsAux.size()) + 0;
        battle->setStartUpB(listStartUpsAux[i]);


        Battles->push_back(battle);
        listStartUpsAux.erase(listStartUpsAux.begin() + i);

        ID++;
    }

    return Battles;
}

std::vector<StartUp*> randomizeBattles(std::vector<Battle*>* listBattles, std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events){
    
    int randomNumber;
    int n = 0;
    std::vector<StartUp*> classifiedStartUps;

    while(n < (*listBattles).size()){

        Battle* battle = (*listBattles)[n];
        PossibleEvents* eventsA = (battle->getStartUpA()->Events);
        PossibleEvents* eventsB = (battle->getStartUpB()->Events);

        for(int idEvent = 1; idEvent <= 5; idEvent++){
            for(int j = 0; j < 2; j++){
                randomNumber = rand() % 2;
                if((j == 0) && (randomNumber == 1)){
                    events[idEvent].first(*eventsA);
                }
                if((j == 1) && (randomNumber == 1)){
                    events[idEvent].first(*eventsB);
                }
            }
        }

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
        n++;
    }

    for (auto battle : *listBattles) {
        delete battle;
    }
    delete listBattles;

    return classifiedStartUps;
}