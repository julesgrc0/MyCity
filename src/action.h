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
    std::vector<Box> getAround(int,int,int);
    Box getItem(int,int);
    void removeItem(Box);
    void setItem(Box,int,int);
    void matrixAround(std::string,int(*)[9]);
    int getItemIndex(Box);
    int getItemIndex(int,int);

private:
    bool isInDist(int, int, int);
    std::vector<Box> cases;
};

#endif // !_ACTION_