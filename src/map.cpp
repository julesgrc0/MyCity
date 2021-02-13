#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "util.h"
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
    this->cases.clear();
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    std::vector<std::string> fileList;

    while ((dp = readdir(dirp)) != NULL)
    {
        std::vector<std::string> el;

        split(std::string(dp->d_name), el, '.');
        if (el.size() >= 2 && el[1] == "box")
        {
            fileList.push_back(el[0]);
        }
    }

    for (std::string file : fileList)
    {

        std::ifstream it(name + "/" + file + ".box");

        if (it.is_open())
        {
            int box[100][4];
            for (int i = 0; i < 100; i++)
            {
                /*
                box[i][2] = 83;
                box[i][3] = 59;
                box[i][1] = 237;
                box[i][0] = 255;
                */
                for (int j = 0; j < 4; j++)
                {
                    box[i][j] = 0;
                }
            }

            std::string line = "";
            int index = 0;
            while (getline(it, line))
            {
                if (index < 100)
                {
                    std::vector<std::string> values;
                    split(line, values, ' ');
                    if ((int)values.size() > 4)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            box[index][i] = std::atoi(values[i].c_str());
                        }
                    }
                    else
                    {
                        for (int i = 0; i < (int)values.size(); i++)
                        {
                            box[index][i] = std::atoi(values[i].c_str());
                        }
                    }
                    index++;
                }
            }

            std::vector<std::string> coord;
            split(file, coord, '-');
            int x = 0;
            int y = 0;

            if (coord.size() >= 2)
            {
                x = std::atoi(coord[0].c_str());
                y = std::atoi(coord[1].c_str());
            }
            Box b = Box("", x, y);
            b.setBox(box);
            this->cases.push_back(b);
            it.close();
        }
    }

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

std::vector<Box> Map::getMap()
{
    return this->cases;
}