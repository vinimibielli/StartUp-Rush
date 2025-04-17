#ifndef STARTUP_H
#define STARTUP_H

#include <iostream>
#include <string>
#include <algorithm>
#include <iostream>

#include "PossibleEvents.h"

class StartUp{

    std::string startupName;
    std::string startupSlogan;
    int startupFoundation;
    int startupPoints;

    public:

        PossibleEvents* Events;

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

 

};

#endif