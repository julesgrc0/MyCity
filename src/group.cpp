#include <iostream>
#include <vector>
#include "group.h"
#include "box.h"

BoxGroup::BoxGroup(std::string type)
{
}

BoxGroup::~BoxGroup()
{
    this->group.clear();
}
