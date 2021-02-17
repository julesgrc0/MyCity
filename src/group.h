#pragma once

#ifndef _GROUP_
#define _GROUP_

#include <iostream>
#include <vector>
#include "box.h"

class BoxGroup
{
public:
    BoxGroup(std::string, int);
    ~BoxGroup();

    void createGroup(std::vector<std::string>, int);

    void setItemGroup(int, int, Box);
    Box getItemGroup(int, int);

    void setGroup(std::vector<Box>);
    void setGroup(std::vector<int**>);
    std::vector<Box> getGroup();

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
    std::vector<Box> group;
    std::vector<Box> backUp;
    bool selected = false;
    int size;
    void setBoxBorder(int (*)[100][4], bool, bool, bool, bool);
};

#endif // !_GROUP_