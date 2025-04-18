#ifndef BATTLES_H
#define BATTLES_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <functional>

#include "StartUp.h"

void printListStartUps(std::vector<StartUp*> listStartUps);
void printListBattles(std::vector<std::pair<StartUp*, StartUp*>> Battles);
void printPointsRanking(std::vector<StartUp*> listStartUps);

StartUp* executeStartUpRush(std::vector<StartUp*> listStartUps);
std::vector<std::pair<StartUp*, StartUp*>> randomBattles(std::vector<StartUp*> listStartUps);
std::vector<StartUp*> executeRoundBattles(std::vector<std::pair<StartUp*, StartUp*>> Battles);
StartUp* executeSingleBattle(std::pair<StartUp*, StartUp*> Battle);

std::pair<bool, bool> checkEvents(std::pair<StartUp*, StartUp*> Battle, int selectEvent);

#endif