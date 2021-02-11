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
    void setMap(std::vector<Box>);
    std::vector<Box> getMap();

private:
    std::vector<Box> cases;
    void CreateFile(std::string,std::string);
    bool CreateFolder(std::string);
};

#endif // !_MAP_