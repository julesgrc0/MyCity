#pragma once

#ifndef _BOX_
#define _BOX_

struct Size
{
    int w, h;
};

struct Rgba
{
    int r, g, b, a;
};

struct Coord
{
    int x, y;
};

class Box
{
public:
    Box(std::string typeName, int x, int y);
    void setPixel(int index, struct Rgba color);
    Rgba getPixel(int index);

    void setType(std::string typeName);
    std::string getType();

    bool isSelected();
    void selectBox();
    void deselectBox();

    void getBox(int (*box)[100][4]);
    void setBox(int box[100][4]);

    struct Size getBoxBounds();
    struct Coord getCoord();
    void setCoord(Coord c);

private:
    std::string type;
    int colors[100][4];
    int backUp[100][4];
    int x, y;
    bool selected = false;
    const int height = 10;
    const int width = 10;
};

#endif // !_BOX_