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
