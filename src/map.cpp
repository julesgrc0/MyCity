#include <iostream>
#include <vector>
#include "box.h"
#include "map.h"

Map::Map(std::vector<Box> cases)
{
    this->cases = cases;
}

Map::~Map()
{
    this->cases.clear();
}

bool Map::exportMap(std::string name)
{
}

std::vector<Box> Map::importMap(std::string name)
{
}