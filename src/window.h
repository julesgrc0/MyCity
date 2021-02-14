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

enum Direction{
    UP_DOWN,
    LEFT_RIGHT,
    BOTH
};

struct CaseFix{
    std::string exept;
    std::string fix1;
    std::string fix2;
};

class Window
{
public:
    Window(std::string, int, int, std::string);
    ~Window();

    void Init();
    void Main();
    void Loop();
    void GameAction(int,int);

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
    void RegisterTexture(std::string id);
    void getTexture(std::string id, int (*b)[100][4]);

    void LoadRessources();
    void UserAction();
    void UserButton(int[100][4], std::pair<int, int>, std::string id);

    void FixCases(std::string,Direction,std::vector<CaseFix>);

private:
    SDL_Renderer *render;
    SDL_Window *window;

    const int BOX_SIZE = 10;
    const int BUTTON_SIZE = 16;

    std::vector<Box> cases;
    std::vector<Box> around;
    std::vector<std::pair<std::pair<int, int>, std::string>> buttons;
    std::vector<std::pair<std::string, int **>> textures;
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
            "water"
        };

    std::string activeElement;
    std::string import;
    bool run;
    int w, h;
    bool mouseActive = false;
    Cursor cursor = {0, 0};
};

#endif // !_WINDOW_