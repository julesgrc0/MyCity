#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "texture.h"
#include "util.h"

Texture::Texture(std::string path)
{
    this->LoadTexture(path);
}

Texture::Texture() {}

void Texture::getTexture(int (*box)[100][4])
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            (*box)[i][j] = this->box[i][j];
        }
    }
}

bool Texture::LoadTexture(std::string path)
{
    this->reset();
    std::ifstream texture(path);
    std::string line = "";

    if (texture.is_open())
    {
        int index = 0;
        while (getline(texture, line))
        {
            if (index < 100)
            {
                std::vector<std::string> values;
                split(line, values, ' ');
                if ((int)values.size() > 4)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        this->box[index][i] = std::atoi(values[i].c_str());
                    }
                }
                else
                {
                    for (int i = 0; i < (int)values.size(); i++)
                    {
                        this->box[index][i] = std::atoi(values[i].c_str());
                    }
                }
                index++;
            }
        }
        texture.close();
        return true;
    }
    else
    {
        return false;
    }
}

void Texture::reset()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->box[i][j] = 255;
        }
    }
}