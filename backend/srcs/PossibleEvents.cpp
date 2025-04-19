#include "./include/PossibleEvents.h"

PossibleEvents::PossibleEvents(){

    this->convincentPitch.first = false;
    this->convincentPitch.second = 0;

    this->productsBugs.first = false;
    this->productsBugs.second = 0;

    this->userTrack.first = false;
    this->userTrack.second = 0;

    this->angryInvestor.first = false;
    this->angryInvestor.second = 0;

    this->pitchFakeNews.first = false;
    this->pitchFakeNews.second = 0;

}

PossibleEvents::~PossibleEvents(){

}

void PossibleEvents::setConvincentPitch(){
    if(!this->convincentPitch.first){
        this->convincentPitch.second += 1;
}
    this->convincentPitch.first = true;
}

void PossibleEvents::setProductsBugs(){
    if(!this->productsBugs.first){
        this->productsBugs.second += 1;
    }
    this->productsBugs.first = true;
}

void PossibleEvents::setUserTrack(){
    if(!this->userTrack.first){
        this->userTrack.second += 1;
    }
    this->userTrack.first = true;
}

void PossibleEvents::setAngryInvestor(){
    if(!this->angryInvestor.first){
        this->angryInvestor.second += 1;
    }
    this->angryInvestor.first = true;
}

void PossibleEvents::setPitchFakeNews(){
    if(!this->pitchFakeNews.first){
        this->pitchFakeNews.second += 1;
    }
    this->pitchFakeNews.first = true;
}

void PossibleEvents::cleanBools(){
    this->convincentPitch.first = false;
    this->productsBugs.first = false;
    this->userTrack.first = false;
    this->angryInvestor.first = false;
    this->pitchFakeNews.first = false;
}

std::pair<bool, int> PossibleEvents::getConvincentPitch(){
    return this->convincentPitch;
} 
std::pair<bool, int> PossibleEvents::getProductsBugs(){
    return this->productsBugs;
} 
std::pair<bool, int> PossibleEvents::getUserTrack(){
    return this->userTrack;
}
std::pair<bool, int> PossibleEvents::getAngryInvestor(){
    return this->angryInvestor;
}
std::pair<bool, int> PossibleEvents::getPitchFakeNews(){
    return this->pitchFakeNews;
}

int PossibleEvents::valueEvents(){
    int value = 0;
    if(this->convincentPitch.first){
        value = value + CONVINCENT_PITCH;
    }
    if(this->productsBugs.first){
        value = value + PRODUCTS_BUGS;
    }
    if(this->userTrack.first){
        value = value + USER_TRACK;
    }
    if(this->angryInvestor.first){
        value = value + ANGRY_INVESTOR;
    }
    if(this->pitchFakeNews.first){
        value = value + PITCH_FAKE_NEWS;
    }

    std::cout << value << std::endl;

    return value;
}