#pragma once
#ifndef _WINDOW_
#define _WINDOW_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "box.h"
#include "texture.h"

struct Cursor
{
    int x, y;
};

enum Direction
{
    UP_DOWN,
    LEFT_RIGHT,
    BOTH,
    LEFT,
    TOP,
    BOTTOM,
    RIGHT
};

struct CaseFix
{
    std::string exept;
    std::string fix1;
    std::string fix2;
};

struct Pos
{
    int x, y;
};

struct GroupItem
{
    std::string id;
    std::vector<std::string> list;
    int width;
};

class Window
{
public:
    Window(std::string, int, int, std::string);
    ~Window();

    void Init();
    void Main();
    void Loop();
    void GameAction(int, int);

    void Mouse_Down(int, int);
    void Mouse_Move(int, int);
    void Mouse_Wheel(int);
    void Mouse_Up(int, int);

    void Keydown(SDL_Keycode);
    void Keyup(SDL_Keycode);

    void close();
    void color(int r, int g, int b, int a);
    void clear();
    void prensent();

    void SetPixel(int x, int y, int r, int g, int b, int a);
    void DrawCase(Box item);
    void DrawGroup(GroupItem item);

    void RegisterGroupTexture(std::string, std::vector<std::string>);
    void RegisterTexture(std::string id);

    void getTexture(std::string id, int (*b)[100][4]);
    std::vector<int **> getGroupTexture(std::string);

    void LoadRessources();
    void UserAction();
    void UserButton(int[100][4], std::pair<int, int>, std::string id);

    void FixCases(Pos, Direction, std::vector<CaseFix>);
    void ChangeBox(Pos, std::string);

private:
    SDL_Renderer *render;
    SDL_Window *window;

    const int BOX_SIZE = 10;
    const int BUTTON_SIZE = 16;
    const std::string GroupSufix = "group-";

    std::vector<Box> cases;
    std::vector<Box> around;
    std::vector<std::pair<std::pair<int, int>, std::string>> buttons;
    std::vector<std::pair<std::string, int **>> textures;
    std::vector<std::pair<std::string, std::vector<int **>>> GroupeTextures;

    std::vector<std::string> TextureLoadList =
        {
            "grass",
            "road-grass-dl",
            "road-grass-dr",
            "road-grass-ul",
            "road-grass-ur",
            "road-grass-lr",
            "road-grass-ud",
            "road-grass-multi",
            "block",
            "water",
    };

    std::vector<GroupItem> GroupeLoadList = {
        {"home",
         {
             "home/g1",
             "home/g2",
             "home/g3",
             "home/g4",
         },
         2
         },
    };

    std::string activeElement;
    std::string import;
    bool run;
    int w, h;
    bool mouseActive = false;
    Cursor cursor = {0, 0};
};

#endif // !_WINDOW_