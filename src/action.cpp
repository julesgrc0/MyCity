#include <iostream>
#include "action.h"
#include "box.h"

Action::Action(std::vector<Box> cases)
{
    for (Box b : cases)
    {
        this->cases.push_back(b);
    }
}

std::vector<Box> Action::getAround(int dist)
{
    int x = 0, y = 0;
    for (Box b : this->cases)
    {
        if (b.isSelected())
        {
            x = b.getCoord().x;
            y = b.getCoord().y;
        }
    }
    int BOX_SIZE = 10;

    std::vector<Box> around = {};
    for (Box b : this->cases)
    {
        int bx = b.getCoord().x;
        int by = b.getCoord().y;
        if (this->isInDist(dist * BOX_SIZE, bx, x) && this->isInDist(dist * BOX_SIZE, by, y))
        {
            around.push_back(b);
        }
    }
    return around;
}

bool Action::isInDist(int dist, int a, int b)
{
    if (a > b)
    {
        int count = 0;
        for (int i = a; i > b; i--)
        {
            count++;
        }
        if (count <= dist)
        {
            return true;
        }
    }
    else
    {
        int count = 0;
        for (int i = a; i < b; i++)
        {
            count++;
        }
        if (count <= dist)
        {
            return true;
        }
    }

    return false;
}

Action::~Action()
{
    this->cases.clear();
}