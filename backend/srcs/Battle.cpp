#include "./include/Battle.h"

Battle::Battle(){
    this->ID = 0;
    this->finalized = false;
    this->StartUpA = NULL;
    this->StartUpB = NULL;
}
Battle::~Battle(){

}

void Battle::setID(int n){
    this->ID = n;
}

void Battle::setFinalized(){
    this->finalized = true;
}

void Battle::cleanFinalized(){
    this->finalized = false;
}

void Battle::setStartUpA(StartUp* A){
    this->StartUpA = A;
}
void Battle::setStartUpB(StartUp* B){
    this->StartUpB = B;
}

int Battle::getID(){
    return this->ID;
}

bool Battle::getFinalized(){
    return this->finalized;
}
StartUp* Battle::getStartUpA(){
    return this->StartUpA;
}
StartUp* Battle::getStartUpB(){
    return this->StartUpB;
}