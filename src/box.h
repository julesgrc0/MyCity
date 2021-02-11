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

enum BoxTypes
{
    WATER,
    ROAD_WATER,
    ROAD,
    GRASS,
    BUILD,
    HOUSE,
    BRIDGE,
    BLOCK
};

class Box
{
public:
    Box(enum BoxTypes type, int x, int y);
    void setPixel(int index, struct Rgba color);
    Rgba getPixel(int index);

    void setType(enum BoxTypes type);
    enum BoxTypes getType();

    bool isSelected();
    void selectBox();
    void deselectBox();

    void getBox(int (*box)[100][4]);
    void setBox(int box[100][4]);

    struct Size getBoxBounds();
    struct Coord getCoord();

private:
    BoxTypes type;
    int colors[100][4];
    int backUp[100][4];
    int x, y;
    bool selected = false;
    const int height = 10;
    const int width = 10;
};

#endif // !_BOX_