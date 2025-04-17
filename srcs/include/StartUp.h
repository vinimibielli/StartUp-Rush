#ifndef STARTUP_H
#define STARTUP_H

#include <iostream>
#include <string>
#include <algorithm>
#include <iostream>

//class PossibleEvents{
//    public:
//    int convincentPitch = 0;
//    int productsBugs = 0;
//    int userTrack = 0;
//    int angryInvestor = 0;
//    int pitchFakeNews = 0;
//};

class StartUp{

    std::string startupName;
    std::string startupSlogan;
    int startupFoundation;
    int startupPoints;
    //PossibleEvents Events;

    public:

        StartUp();
        ~StartUp();

        StartUp(std::string Name, std::string Slogan, int Foundation);

        void setName(std::string Name);
        std::string  getName();

        void setSlogan(std::string Slogan);
        std::string  getSlogan();

        void setFoundation(int Foundation);
        int  getFoundation();

        void setPoints(int Points);
        int  getPoints();
        void editPoints(int changePoints);
        void winBattlePoints();

        //void setConvincentPitch(int n);
        //void setProductsBugs(int n); 
        //void setUserTrack(int n);
        //void setAngryInvestor(int n);
        //void setPitchFakeNews(int n);
        //
        //int getConvincentPitch(); 
        //int getProductsBugs(); 
        //int getUserTrack();
        //int getAngryInvestor();
        //int getPitchFakeNews();
 

};

#endif