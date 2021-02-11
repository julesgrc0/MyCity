#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
#include "map.h"
#include "box.h"

Map::Map(std::vector<Box> cases)
{
    for (int i = 0; i < (int)cases.size(); i++)
    {
        this->cases.push_back(cases[i]);
    }
}

Map::~Map()
{
    this->cases.clear();
}

bool Map::exportMap(std::string name)
{
    if (CreateFolder(name))
    {
        // while (access(name.c_str(), F_OK) != 0){}    /* Wait for folder creation */

        for (Box it : this->cases)
        {
            int b[100][4];
            it.getBox(&b);
            std::string content = "";

            std::string x = std::to_string(it.getCoord().x);
            std::string y = std::to_string(it.getCoord().y);

            std::string Fame = "./" + name + "/" + x + "-" + y + ".box";

            for (int i = 0; i < 100; i++)
            {
                for (int c = 0; c < 4; c++)
                {
                    content += std::to_string(b[i][c]) + " ";
                }
                content += "\n";
            }
            CreateFile(Fame, content);
        }
    }
    return false;
}

std::vector<Box> Map::importMap(std::string name)
{
    return this->cases;
}

void Map::CreateFile(std::string name, std::string content)
{
    std::fstream file(name, std::fstream::out);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

bool Map::CreateFolder(std::string name)
{
    if (access(name.c_str(), F_OK) != 0)
    {
        mkdir(name.c_str());
        return true;
    }
    return false;
}


void Map::setMap(std::vector<Box> cases)
{
    this->cases.clear();
    for (int i = 0; i < (int)cases.size(); i++)
    {
        this->cases.push_back(cases[i]);
    }
}

std::vector<Box> getMap()()
{
    return this->cases;
}