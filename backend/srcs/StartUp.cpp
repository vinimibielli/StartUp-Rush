#include "./include/StartUp.h"

StartUp::StartUp(){
    this->startupName = "Name";
    this->startupSlogan = "Slogan";
    this->startupFoundation = 0;
    this->startupPoints = 70;
    Events = new PossibleEvents();
}
StartUp::~StartUp(){
    delete Events;
}
StartUp::StartUp(std::string Name, std::string Slogan, int Foundation){
    this->startupName = Name;
    this->startupSlogan = Slogan;
    this->startupFoundation = Foundation;
    this->startupPoints = 70;
    Events = new PossibleEvents();
}

//Funções para o Nome
void StartUp::setName(std::string Name){
    this->startupName = Name;
}
std::string  StartUp::getName(){
    return this->startupName;
}

//Funções para o Slogan
void StartUp::setSlogan(std::string Slogan){
    this->startupSlogan = Slogan;
}
std::string  StartUp::getSlogan(){
    return this->startupSlogan;
}

//Funções para o Ano de Fundação
void StartUp::setFoundation(int Foundation){
    this->startupFoundation = Foundation;
}
int  StartUp::getFoundation(){
    return this->startupFoundation;
}

//Funções para os Pontos
void StartUp::setPoints(int Points){
    this->startupPoints = Points;
}
int  StartUp::getPoints(){
    return this->startupPoints;
}
void StartUp::editPoints(int changePoints){
    this->startupPoints = this->startupPoints + (changePoints);
}

void StartUp::winBattlePoints(){
    this->startupPoints = this->startupPoints + 30;
}
