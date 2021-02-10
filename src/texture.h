#pragma once
#ifndef _TEXTURE_
#define _TEXTURE_

#include<vector>
#include<iostream>

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
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
};


#endif // !_TEXTURE_