#include "./include/main.h"

int main(){

    std::vector<StartUp*> listStartUps;
    std::vector<std::pair<StartUp*, StartUp*>> Battles;

    listStartUps.push_back(new StartUp("Dell", "Venha ser Feliz", 1953));
    listStartUps.push_back(new StartUp("HP", "Venha ser Feliz", 1953));
    listStartUps.push_back(new StartUp("Lenovo", "Venha ser Feliz", 1931));
    listStartUps.push_back(new StartUp("Asus", "Venha ser Feliz", 1998));
    listStartUps.push_back(new StartUp("Acer", "Venha ser Feliz", 1998));
    listStartUps.push_back(new StartUp("Positivo", "Venha ser Feliz", 1998));
    listStartUps.push_back(new StartUp("Sony", "Venha ser Feliz", 1998));
    listStartUps.push_back(new StartUp("Avell", "Venha ser Feliz", 1998));

   Battles = randomBattles(listStartUps);

    for(int i = 0; i < Battles.size(); i++){
        std::cout << "Batalha " << i+1 << ": " << Battles[i].first->getName() << " x " << Battles[i].second->getName() << std::endl;
    }
}



std::vector<std::pair<StartUp*, StartUp*>> randomBattles(std::vector<StartUp*>& listStartUps){
    int i;
    StartUp *auxFirst, *auxSecond;
    std::vector<std::pair<StartUp*, StartUp*>> Battles;
    std::pair<StartUp*, StartUp*> pairAux;
    while(listStartUps.size() > 1){

        srand(time(0));
        i = rand()%(listStartUps.size()) + 0;
        auxFirst = listStartUps[i];
        listStartUps.erase(listStartUps.begin() + i);

        i = rand()%(listStartUps.size()) + 0;
        auxSecond = listStartUps[i];
        Battles.push_back(std::make_pair(auxFirst, auxSecond));
        listStartUps.erase(listStartUps.begin() + i);

    }

    return Battles;
}