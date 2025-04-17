#ifndef BATTLES_H
#define BATTLES_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>

#include "StartUp.h"

std::vector<std::pair<StartUp*, StartUp*>> randomBattles(std::vector<StartUp*> listStartUps);

void printListStartUps(std::vector<StartUp*> listStartUps);

std::vector<StartUp*> executeRoundBattles(std::vector<std::pair<StartUp*, StartUp*>> Battles);

StartUp* executeSingleBattle(std::pair<StartUp*, StartUp*> Battle);

StartUp* executeStartUpRush(std::vector<StartUp*> listStartUps);

#endif