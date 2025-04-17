#include "./include/main.h"

int main(){

    std::vector<StartUp*> listStartUps;
    std::string Name, Slogan;
    int selectOption, Foundation;
    bool continueToBattles = false;

    std::cout << "Cadastre as StartUps participantes!" << std::endl;
    std::cout << "Lembre-se para realizar as disputas será necessário 4 ou 8 equipes." << std::endl;

    /*
    while(!continueToBattles){
        std::cout << "1- Cadastro de nova StartUp." << std::endl;
        std::cout << "2- Exluir cadastro de uma StartUp." << std::endl;
        std::cout << "3- Veja as StartUps já participantes." << std::endl;
        std::cout << "4- Começar as disputas." << std::endl;
        std::cin >> selectOption;

        switch (selectOption)
        {
        case 1:
            std::cout << "Indique o nome, slogan e ano de fundacao nesta respectiva ordem." << std::endl;
            std::cin >> Name >> Slogan >> Foundation;
            listStartUps.push_back(new StartUp(Name, Slogan, Foundation));
        break;
        case 2:
            printListStartUps(listStartUps);
            if(listStartUps.size() != 0){
            std::cout << "Indique qual StartUp você quer deletar." << std::endl;
            std::cin >> selectOption;
            listStartUps.erase(listStartUps.begin() + (selectOption - 1));
            }
        break;
        case 3:
            printListStartUps(listStartUps);
        break;
        case 4:
            if((listStartUps.size() == 4) || (listStartUps.size() == 8)){
                continueToBattles = true;
            } else {
                std::cout << "Número de equipes cadastradas no momento: " << listStartUps.size() << std::endl;
                std::cout << "Por favor, cadastre 4 ou 8 StartUps" << std::endl;
            }
        break;
        default:
            break;
        }
    }
        */

    listStartUps.push_back(new StartUp("Dell", "The power to do more", 2016));
    listStartUps.push_back(new StartUp("HP", "Keep Reinventing", 1939));
    listStartUps.push_back(new StartUp("Lenovo", "Smarter technology for all", 1984));
    listStartUps.push_back(new StartUp("Asus", "In Search of Incredible", 1989));
    listStartUps.push_back(new StartUp("Acer", "Explore beyond limits", 1974));
    listStartUps.push_back(new StartUp("Apple", "Think different", 1976));
    listStartUps.push_back(new StartUp("Sony", "make.believe", 1946));
    listStartUps.push_back(new StartUp("Samsung", "Do What You Can't", 1969));

   StartUp* Vencedor = executeStartUpRush(listStartUps);

   std::cout << " StartUp Vencedora: "<< Vencedor->getName() << " - " << Vencedor->getSlogan() << std::endl;

   printPointsRanking(listStartUps);

}
