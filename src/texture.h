#pragma once
#ifndef _TEXTURE_
#define _TEXTURE_

#include <vector>
#include <iostream>

class Texture
{
public:
    Texture();
    Texture(std::string path);
    bool LoadTexture(std::string path);
    void getTexture(int (*box)[100][4]);

private:
    int box[100][4];
    void reset();
};

#endif // !_TEXTURE_