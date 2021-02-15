#include <iostream>
#include <vector>
#include "group.h"
#include "box.h"
#include "texture.h"

BoxGroup::BoxGroup(std::string type,int size)
{
    this->type = type;
    this->size = size;
}

bool BoxGroup::isSelected()
{
    return this->selected;
}

void BoxGroup::deselectGroups()
{
    if (this->selected)
    {
        this->selected = false;
    }
}

void BoxGroup::selectGroups()
{
    if (!this->selected)
    {
        this->selected = true;
    }
}

std::string BoxGroup::getType()
{
    return this->type;
}

void BoxGroup::setType(std::string type)
{
    this->type = type;
}

std::vector<GroupItem> BoxGroup::getGroup()
{
    return this->group;
}

void BoxGroup::setGroup(std::vector<GroupItem> group)
{
    this->group.clear();
    for (GroupItem it : group)
    {
        this->group.push_back(it);
    }
}

GroupItem BoxGroup::getItemGroup(int x, int y)
{
    int box[100][4];
    GroupItem item = {&box, 0, 0};

    for (GroupItem it : group)
    {
        if (it.x == x && it.y == y)
        {
            return item;
        }
    }

    return item;
}

void BoxGroup::setItemGroup(int x, int y, GroupItem item)
{
    int i = 0;
    for (GroupItem it : this->group)
    {
        if (it.x == x && it.y == y)
        {
            this->group[i] = item;
            break;
        }
        i++;
    }
}

void BoxGroup::createGroup(std::vector<std::string> list, int size)
{
    Texture texture = Texture();
    int i = 0;
    int j = 0;
    std::vector<GroupItem> items = {};

    for (std::string it : list)
    {
        if (i == size)
        {
            int box[100][4];
            if (texture.LoadTexture(it))
            {
                texture.getTexture(&box);
            }
            GroupItem Gitem = {&box, i, j};
            items.push_back(Gitem);
            j++;
            i = 0;
        }
        i++;
    }
    this->size = size;

    this->group.clear();
    for(GroupItem it : items)
    {
        this->group.push_back(it);
    }
}

int BoxGroup::getSize()
{
    return this->size;
}

bool BoxGroup::setSize(int size)
{
    int gsize = (int)this->group.size();
    if(!gsize)
    {
        return false;
    }
    int i = 0;
    int j = 0;
    std::vector<GroupItem> items = {};

    for(GroupItem it : this->group)
    {
        if (i == size)
        {
            items.push_back(it);
            j++;
            i = 0;
        }
        i++;
    }

    this->group.clear();
    for(GroupItem it : items)
    {
        this->group.push_back(it);
    }

    return true;
}

void BoxGroup::operator=(BoxGroup other)
{
    bool last = false;
    if (other.isSelected())
    {
        last = true;
        other.deselectGroups();
    }
    this->setType(other.getType());
    this->setGroup(other.getGroup());

    if (last)
    {
        other.selectGroups();
        this->selectGroups();
    }
}

bool BoxGroup::operator==(BoxGroup other)
{
    if (other.isSelected() != this->isSelected())
    {
        return false;
    }

    if (other.getType() != this->getType())
    {
        return false;
    }

    for (GroupItem it : this->group)
    {
        for (GroupItem ot : other.getGroup())
        {
            if (it.x != ot.x || it.y != ot.y || it.box != ot.box)
            {
                return false;
            }
        }
    }

    return true;
}

bool BoxGroup::operator!=(BoxGroup other)
{
    if (this == &other)
    {
        return false;
    }
    return true;
}

BoxGroup::~BoxGroup()
{
    this->group.clear();
}
