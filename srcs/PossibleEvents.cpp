#include "./include/PossibleEvents.h"

PossibleEvents::PossibleEvents(){

    this->convincentPitch = 0;
    this->productsBugs = 0;
    this->userTrack = 0;
    this->angryInvestor = 0;
    this->pitchFakeNews = 0;

}

PossibleEvents::~PossibleEvents(){

}

void PossibleEvents::setConvincentPitch(){
    this->convincentPitch += 1;
}
void PossibleEvents::setProductsBugs(){
    this->productsBugs += 1;
} 
void PossibleEvents::setUserTrack(){
    this->userTrack += 1;
}
void PossibleEvents::setAngryInvestor(){
    this->angryInvestor += 1;
}
void PossibleEvents::setPitchFakeNews(){
    this->pitchFakeNews += 1;
}

int PossibleEvents::getConvincentPitch(){
    return this->convincentPitch;
} 
int PossibleEvents::getProductsBugs(){
    return this->convincentPitch;
} 
int PossibleEvents::getUserTrack(){
    return this->userTrack;
}
int PossibleEvents::getAngryInvestor(){
    return this->angryInvestor;
}
int PossibleEvents::getPitchFakeNews(){
    return this->pitchFakeNews;
}