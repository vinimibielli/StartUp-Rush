#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <utility>

#include "StartUp.h"

class Battle{

    int ID;
    bool finalized;
    StartUp* StartUpA;
    StartUp* StartUpB;

    public:

        Battle();
        ~Battle();

        void setID(int n);
        void setFinalized();
        void cleanFinalized();
        void setStartUpA(StartUp* A);
        void setStartUpB(StartUp* B);

        int getID();
        bool getFinalized();
        StartUp* getStartUpA();
        StartUp* getStartUpB();

};

#endif