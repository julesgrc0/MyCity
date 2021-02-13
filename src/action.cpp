#include <iostream>
#include <vector>
#include "action.h"
#include "box.h"

Action::Action(std::vector<Box> cases)
{
    for (Box b : cases)
    {
        this->cases.push_back(b);
    }
}

std::vector<Box> Action::getAround(int dist, int x, int y)
{
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

void Action::matrixAround(std::string execpt, int (*arr)[9])
{
    std::vector<Box> around = this->getAround(1);
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int res = 0;
            if (index < (int)around.size() && around[index].getType() != execpt)
            {
                res = 1;
            }
            (*arr)[index] = res;
            index++;
        }
    }
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

Box Action::getItem(int x, int y)
{
    Box box = Box("null", x, y);
    for (Box b : this->cases)
    {
        if (b.getCoord().x == x && b.getCoord().y == y)
        {
            box = b;
        }
    }
    return box;
}

int Action::getItemIndex(Box it)
{
    int i = 0;
    for (Box b : this->cases)
    {
        if (b == it)
        {
            return i;
        }
        i++;
    }
    return this->cases.size() + 1;
}
int Action::getItemIndex(int x, int y)
{
    Box it = this->getItem(x, y);
    int i = 0;
    for (Box b : this->cases)
    {
        if (b == it)
        {
            return i;
        }
        i++;
    }
    return this->cases.size() + 1;
}

void Action::removeItem(Box b)
{
    int i = 0;
    for (Box box : this->cases)
    {
        if (b == box)
        {
            int remove[100][4];
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    remove[i][j] = 0;
                }
            }

            box.setType("");
            box.deselectBox();
            box.setBox(remove);
        }
        i++;
    }
}

void Action::setItem(Box item, int x, int y)
{
    int i = 0;
    for (Box box : this->cases)
    {
        if (item.getCoord().x == x && item.getCoord().y == y)
        {
            this->cases[i] = item;
        }
        i++;
    }
}

Action::~Action()
{
    this->cases.clear();
}