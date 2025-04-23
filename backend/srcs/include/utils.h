#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <functional>

#include "StartUp.h"
#include "Battle.h"

std::vector<StartUp*> ordeningPointsRanking(std::vector<StartUp*> listStartUps);
std::vector<Battle*>* randomBattles(std::vector<StartUp*> listStartUps);
std::vector<StartUp*> randomizeBattles(std::vector<Battle*>* listBattles, std::unordered_map<int, std::pair<std::function<void(PossibleEvents&)>, std::function<std::pair<bool, int>(PossibleEvents&)>>> events);


#endif