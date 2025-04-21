#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "StartUp.h"
#include "utils.h"
#include "Battle.h"
#include "crow.h"
#include "json.hpp"

crow::response createJSON(int status, std::string message, std::string next);
