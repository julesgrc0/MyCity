#pragma once

#ifndef _MAP_
#define _MAP_

#include <iostream>
#include <vector>
#include "box.h"

class Map
{

public:
    Map(std::vector<Box>);
    ~Map();
    bool exportMap(std::string);
    std::vector<Box> importMap(std::string);

private:
    std::vector<Box> cases;
};

#endif // !_MAP_