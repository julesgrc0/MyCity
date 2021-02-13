#pragma once

#ifndef _ACTION_
#define _ACTION_

#include <iostream>
#include <vector>
#include "box.h"

class Action
{
public:
    Action(std::vector<Box>);
    ~Action();
    std::vector<Box> getAround(int);

private:
    bool isInDist(int, int, int);
    std::vector<Box> cases;
};

#endif // !_ACTION_