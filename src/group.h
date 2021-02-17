#pragma once

#ifndef _GROUP_
#define _GROUP_

#include <iostream>
#include <vector>
#include "box.h"

struct GroupItem
{
    int (*box)[4];
    int x, y;
    void operator=(GroupItem other)
    {
        this->x = other.x;
        this->y = other.y;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->box[i][j] = other.box[i][j];
            }
        }
    }
};

class BoxGroup
{
public:
    BoxGroup(std::string, int);
    ~BoxGroup();

    void createGroup(std::vector<std::string>, int);

    void setItemGroup(int, int, GroupItem);
    GroupItem getItemGroup(int, int);

    void setGroup(std::vector<GroupItem>);
    std::vector<GroupItem> getGroup();

    std::string getType();
    void setType(std::string);

    bool isSelected();
    void selectGroups();
    void deselectGroups();

    int getSize();
    bool setSize(int);

    void operator=(BoxGroup);
    bool operator==(BoxGroup);
    bool operator!=(BoxGroup);

private:
    std::string type;
    std::vector<GroupItem> group;
    std::vector<GroupItem> backUp;
    bool selected = false;
    int size;
    void setBoxBorder(int (*)[100][4], bool, bool, bool, bool);
};

#endif // !_GROUP_