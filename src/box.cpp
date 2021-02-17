#include <iostream>
#include <SDL2/SDL.h>
#include "box.h"

Box::Box(std::string typeName, int x, int y)
{
    this->type = typeName;
    this->x = x;
    this->y = y;
    for (int i = 0; i < this->width * this->height; i++)
    {
        /*
        this->backUp[i][3] = 59;
        this->colors[i][3] = 59;

        this->backUp[i][2] = 83;
        this->colors[i][2] = 83;

        this->backUp[i][1] = 237;
        this->colors[i][1] = 237;

        this->backUp[i][0] = 255;
        this->colors[i][0] = 255;
        */

        for (int j = 0; j < 4; j++)
        {
            this->backUp[i][j] = 0;
            this->colors[i][j] = 0;
        }
    }
}

void Box::setType(std::string typeName)
{
    this->type = typeName;
}

std::string Box::getType()
{
    return this->type;
}

bool Box::isSelected()
{
    return this->selected;
}

void Box::getBox(int (*box)[100][4])
{
    for (int i = 0; i < this->width * this->height; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            (*box)[i][j] = this->colors[i][j];
        }
    }
}

void Box::getNoSelected(int (*box)[100][4])
{
    for (int i = 0; i < this->width * this->height; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            (*box)[i][j] = this->backUp[i][j];
        }
    }
}

void Box::setBox(int box[100][4])
{
    for (int i = 0; i < this->width * this->height; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->backUp[i][j] = box[i][j];
            this->colors[i][j] = box[i][j];
        }
    }
}

void Box::setCoord(Coord c)
{
    this->x = c.x;
    this->y = c.y;
}

struct Coord Box::getCoord()
{
    return {this->x, this->y};
}

void Box::selectBox()
{
    this->selected = true;
    for (int i = 0; i < this->width * this->height; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->backUp[i][j] = this->colors[i][j];
        }
    }

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int c = 255;
            switch (j)
            {
            case 1:
                c = 247;
                break;
            case 2:
                c = 20;
                break;
            case 3:
                c = 236;
                break;
            }
            this->colors[i][j] = c;

            int bottom = ((this->width * this->height) - this->width) + i;
            this->colors[bottom][j] = c;

            int left = i * this->width;
            this->colors[left][j] = c;

            int right = i * this->width + (this->height - 1);
            this->colors[right][j] = c;
        }
    }
}

void Box::deselectBox()
{
    this->selected = false;
    for (int i = 0; i < this->width * this->height; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->colors[i][j] = this->backUp[i][j];
        }
    }
}

void Box::setPixel(int index, Rgba color)
{
    if (index >= 0 && index < this->height * this->width)
    {
        this->colors[index][3] = color.r;
        this->colors[index][2] = color.g;
        this->colors[index][1] = color.b;
        this->colors[index][0] = color.a;
    }
}

Rgba Box::getPixel(int index)
{
    Rgba color = {256, 256, 256, 256};
    if (index >= 0 && index < this->height * this->width)
    {
        color = {this->colors[index][3], this->colors[index][2], this->colors[index][1], this->colors[index][0]};
    }
    return color;
}

void Box::operator=(Box other)
{
    this->setType(other.getType());
    this->setCoord(other.getCoord());
    int box[100][4];
    other.getNoSelected(&box);
    this->setBox(box);
    if (other.isSelected())
    {
        this->selectBox();
    }
}

bool Box::operator==(Box other)
{
    if (this->isSelected() != other.isSelected())
    {
        return false;
    }

    if (this->getType() != other.getType())
    {
        return false;
    }
    if (this->getCoord().x != other.getCoord().x || this->getCoord().y != other.getCoord().y)
    {
        return false;
    }

    for (int i = 0; i < this->getBoxBounds().w * this->getBoxBounds().h; i++)
    {
        Rgba t = this->getPixel(i);
        Rgba o = other.getPixel(i);
        if (t.a != o.a || t.b != o.b || t.g != o.g || t.r != o.r)
        {
            return false;
        }
    }
    return true;
}

bool Box::operator!=(Box other)
{
    if ((*this) == other)
    {
        return false;
    }
    return true;
}
struct Size Box::getBoxBounds()
{
    return {this->width, this->height};
}