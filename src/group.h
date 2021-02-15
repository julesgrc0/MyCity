#pragma once

#ifndef _GROUP_
#define _GROUP_

#include <iostream>
#include<vector>
#include "box.h"


struct GroupeItem{
    int box[100][4];
    int x, y;
};

class BoxGroup
{
public:
    BoxGroup(std::string);
    ~BoxGroup();

    void setBox(int,int,GroupeItem);
    GroupeItem getBox(int,int);

    void setGroup(GroupeItem);
    GroupeItem getGroup();

    bool isSelected();
    void selectGroup();
    void deselectGroup();

    void operator=(BoxGroup);
    bool operator==(BoxGroup);
    bool operator!=(BoxGroup);

private:
    std::string type;
    std::vector<GroupeItem> group;
};

#endif // !_GROUP_