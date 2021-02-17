#include <iostream>
#include <vector>
#include "group.h"
#include "box.h"
#include "texture.h"

BoxGroup::BoxGroup(std::string type, int size)
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
        this->group.clear();
        for (Box it : this->backUp)
        {
            this->group.push_back(it);
        }
    }
}

void BoxGroup::selectGroups()
{
    if (!this->selected)
    {
        this->selected = true;
        this->backUp.clear();
        for (Box it : this->group)
        {
            this->backUp.push_back(it);
        }

        int width = this->size;
        int height = this->group.size() / width;

        for (int i = 0; i < width; i++)
        {
            int pos[4] = {i, i * width, ((width * height) - width) + i, i * width + (height - 1)};
            for (int j = 0; j < 4; j++)
            {
                int box[100][4];
                for (int bi = 0; bi < 100; bi++)
                {
                    for (int bj = 0; bj < 4; bj++)
                    {
                        int Gbox[100][4];
                        this->group[pos[j]].getBox(&Gbox);
                        box[bi][bj] = Gbox[bi][bj];
                    }
                }

                switch (j)
                {
                case 0:
                    this->setBoxBorder(&box, true, false, false, true);
                    break;
                case 1:
                    this->setBoxBorder(&box, false, true, false, true);
                    break;
                case 2:
                    this->setBoxBorder(&box, false, false, true, true);
                    break;
                case 3:
                    this->setBoxBorder(&box, false, false, false, true);
                    break;
                }

                Box item = Box(this->type, this->group[pos[j]].getCoord().x, this->group[pos[j]].getCoord().y);
                item.setBox(box);
                this->group[pos[j]] = item;
            }
        }
    }
}

void BoxGroup::setBoxBorder(int (*box)[100][4], bool top, bool right, bool bottom, bool left)
{
    for (int i = 0; i < 10; i++)
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
            if (top)
            {
                (*box)[i][j] = c;
            }

            if (bottom)
            {
                int bottomB = ((10 * 10) - 10) + i;
                (*box)[bottomB][j] = c;
            }

            if (left)
            {
                int leftB = i * 10;
                (*box)[leftB][j] = c;
            }
            if (right)
            {
                int rightB = i * 10 + (10 - 1);
                (*box)[rightB][j] = c;
            }
        }
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

std::vector<Box> BoxGroup::getGroup()
{
    return this->group;
}

void BoxGroup::setGroup(std::vector<int **> g)
{
    this->group.clear();
    int i = 0;
    int j = 0;

    for (int **it : g)
    {
        i++;
        int box[100][4];
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                box[i][j] = it[i][j];
            }
        }
        Box b = Box(this->type, i, j);
        b.setBox(box);
        this->group.push_back(b);
        if (i == this->size)
        {
            i = 0;
            j++;
        }
    }
}

void BoxGroup::setGroup(std::vector<Box> group)
{
    this->group.clear();
    for (Box it : group)
    {
        this->group.push_back(it);
    }
}

Box BoxGroup::getItemGroup(int x, int y)
{
    Box item = Box(this->type, 0, 0);

    for (Box it : group)
    {
        if (it.getCoord().x == x && it.getCoord().y == y)
        {
            return it;
        }
    }

    return item;
}

void BoxGroup::setItemGroup(int x, int y, Box item)
{
    int i = 0;
    for (Box it : this->group)
    {
        if (it.getCoord().x == x && it.getCoord().y == y)
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
    std::vector<Box> items = {};

    int x = 0;
    int y = 0;

    for (std::string it : list)
    {
        x++;
        int box[100][4];
        if (texture.LoadTexture(it))
        {
            texture.getTexture(&box);
            int **a = new int *[100];
            for (int i = 0; i < 100; ++i)
            {
                a[i] = new int[4];

                a[i][0] = box[i][3];
                a[i][1] = box[i][2];
                a[i][2] = box[i][1];
                a[i][3] = box[i][0];
            }

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    box[i][j] = a[i][j];
                }
            }
        }
        Box Gitem = Box(this->type, x, y);
        Gitem.setBox(box);
        items.push_back(Gitem);
        if (x == size)
        {
            x = 0;
            y++;
        }
    }
    this->size = size;

    this->group.clear();
    for (Box it : items)
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
    if (!gsize)
    {
        return false;
    }
    int i = 0;
    int j = 0;
    std::vector<Box> items = {};

    for (Box it : this->group)
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
    for (Box it : items)
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

    for (Box it : this->group)
    {
        for (Box ot : other.getGroup())
        {
            if (it != ot)
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
    this->backUp.clear();
}
