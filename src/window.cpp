#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "texture.h"
#include "box.h"
#include "window.h"

Window::Window(std::string name, int width, int height)
{
    this->w = width;
    this->h = height - 50;
    this->run = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
    {
        std::cout << "Fail to init SDL " << std::endl;
        exit(1);
    }
    if (SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->render) != 0)
    {
        std::cout << "Fail to create window and renderer" << std::endl;
    }
    if (!this->window || !this->render)
    {
        std::cout << "Fail to create window and renderer" << std::endl;
    }

    SDL_SetWindowTitle(this->window, name.c_str());
    this->Init();
    this->Main();
    this->Loop();
}

void Window::Init()
{
    this->activeElement = "grass";
    this->LoadRessources();
    for (int y = 0; y < this->h / this->BOX_SIZE; y++)
    {
        for (int x = 0; x < this->w / this->BOX_SIZE; x++)
        {
            Box b = Box(BLOCK, x * this->BOX_SIZE, y * this->BOX_SIZE);
            this->cases.push_back(b);
        }
    }
    for (Box item : this->cases)
    {
        Coord pos = item.getCoord();
        int box[100][4];
        item.getBox(&box);

        int c = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                this->SetPixel(pos.x + i, pos.y + j, box[c][3], box[c][2], box[c][1], box[c][0]);
                c++;
            }
        }
    }
    this->UserAction();
    this->prensent();
}

void Window::UserAction()
{
    int y = this->h;
    this->color(145, 145, 145, SDL_ALPHA_OPAQUE);
    for (int i = this->h; i < this->h + 50; i++)
    {
        SDL_RenderDrawLine(this->render, 0, i, this->w, i);
    }
    this->color(48, 48, 48, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(this->render, 0, y, this->w, y);
    this->color(107, 107, 107, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(this->render, 0, y + 1, this->w, y + 1);

    int x = 20;
    int btn[100][4];
    std::pair<int, int> pos;

    for (std::string text : this->TextureLoadList)
    {
        x += this->BUTTON_SIZE*2;
        pos = {x, y + 10};

        this->getTexture(text, &btn);
        this->UserButton(btn, pos, text);
    }
}

void Window::UserButton(int texture[100][4], std::pair<int, int> pos, std::string id)
{
    bool isset = false;
    for (std::pair<std::pair<int, int>, std::string> it : this->buttons)
    {
        std::pair<int, int> btn = it.first;
        if (btn.first == pos.first && btn.second == pos.second)
        {
            isset = true;
        }
    }

    if (!isset)
    {
        std::pair<std::pair<int, int>, std::string> btnReg = {pos, id};
        this->buttons.push_back(btnReg);
        this->color(214, 214, 214, SDL_ALPHA_OPAQUE);
        for (int i = pos.second; i < pos.second + this->BUTTON_SIZE; i++)
        {
            SDL_RenderDrawLine(this->render, pos.first, i, pos.first + this->BUTTON_SIZE - 1, i);
        }

        this->color(107, 107, 107, SDL_ALPHA_OPAQUE);
        SDL_Rect rect = {pos.first, pos.second, this->BUTTON_SIZE, this->BUTTON_SIZE};
        SDL_RenderDrawRect(this->render, &rect);
        int c = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                this->SetPixel(pos.first + 3 + i, pos.second + 3 + j, texture[c][3], texture[c][2], texture[c][1], texture[c][0]);
                c++;
            }
        }
    }
}

void Window::LoadRessources()
{
    for (std::string id : this->TextureLoadList)
    {
        this->RegisterTexture(id);
    }
}

void Window::getTexture(std::string id, int (*b)[100][4])
{
    for (std::pair<std::string, int **> it : this->textures)
    {
        if (it.first == id)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    (*b)[i][j] = it.second[i][j];
                }
            }
        }
    }
}

void Window::RegisterTexture(std::string id)
{
    int b[100][4];
    Texture loader = Texture("./assets/resources/" + id + ".box");
    loader.getTexture(&b);

    int **a = new int *[100];
    for (int i = 0; i < 100; ++i)
    {
        a[i] = new int[4];

        a[i][0] = b[i][3];
        a[i][1] = b[i][2];
        a[i][2] = b[i][1];
        a[i][3] = b[i][0];
    }
    std::pair<std::string, int **> reg = {id, a};
    this->textures.push_back(reg);
}

void Window::Mouse_Move(int x, int y)
{
    if (this->mouseActive)
    {
        this->cursor = {x, y};
    }
}

void Window::Mouse_Down(int x, int y)
{
    if (y > this->h)
    {
        for (std::pair<std::pair<int, int>, std::string> it : this->buttons)
        {
            std::pair<int, int> btn = it.first;
            if (x >= btn.first && x <= btn.first + this->BUTTON_SIZE && y >= btn.second && y <= btn.second + this->BUTTON_SIZE)
            {
                this->activeElement = it.second;
            }
        }
    }
    else
    {
        this->mouseActive = true;
        this->cursor = {x, y};
        this->Main();
    }
}

void Window::Mouse_Up(int x, int y)
{
    this->mouseActive = false;
    this->cursor = {x, y};
}

void Window::Mouse_Wheel(int wheel)
{
    int y = this->cursor.y + -wheel * 10;
    if (y < this->h && y >= 0)
    {
        this->cursor = {this->cursor.x, y};
        this->Main();
    }
}

void Window::Keydown(SDL_Keycode code)
{
    int x = this->cursor.x;
    int y = this->cursor.y;

    switch (code)
    {
    case SDLK_LEFT:
        x -= 10;
        break;
    case SDLK_RIGHT:
        x += 10;
        break;
    case SDLK_UP:
        y -= 10;
        break;
    case SDLK_DOWN:
        y += 10;
        break;
    case SDLK_SPACE:
        this->Mouse_Down(x,y);
        this->mouseActive = false;
        break;
    }

    if (x != this->cursor.x || y != this->cursor.y)
    {
        if (x < this->w && x >= 0)
        {
            this->cursor.x = x;
        }
        if (y < this->h && y >= 0)
        {
            this->cursor.y = y;
        }
        this->Main();
    }
}

void Window::Keyup(SDL_Keycode code)
{
}

void Window::Main()
{
    int Cursor_x = (cursor.x / this->BOX_SIZE) * this->BOX_SIZE, Cursor_y = (cursor.y / this->BOX_SIZE) * this->BOX_SIZE;

    std::vector<Box> temp = {};
    for (unsigned long i = 0; i < this->cases.size(); i++)
    {
        Box item = this->cases[i];
        Coord pos = item.getCoord();

        if (pos.x == Cursor_x && pos.y == Cursor_y)
        {
            if (this->mouseActive)
            {
                int b[100][4];
                this->getTexture(this->activeElement, &b);
                item.setBox(b);
                item.selectBox();
                this->DrawCase(item);
            }

            if (!item.isSelected())
            {
                item.selectBox();
                this->DrawCase(item);
            }
        }
        else
        {
            if (item.isSelected())
            {
                item.deselectBox();
                this->DrawCase(item);
            }
        }
        temp.push_back(item);
    }
    this->cases.clear();
    for (Box it : temp)
    {
        this->cases.push_back(it);
    }

    this->prensent();
}

void Window::Loop()
{
    while (this->run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                this->close();
                break;
            case SDL_MOUSEWHEEL:
                this->Mouse_Wheel(event.button.x);
                break;
            case SDL_MOUSEMOTION:
                this->Mouse_Move(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->Mouse_Down(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                this->Mouse_Up(event.button.x, event.button.y);
                break;
            case SDL_KEYDOWN:
                this->Keydown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                this->Keyup(event.key.keysym.sym);
                break;
            }
        }
    }

    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void Window::SetPixel(int x, int y, int r, int g, int b, int a)
{
    this->color(r, g, b, a);
    SDL_RenderDrawPoint(this->render, x, y);
}

void Window::close()
{
    this->run = false;
}

void Window::clear()
{
    this->color(0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->render);
}

void Window::prensent()
{
    SDL_RenderPresent(this->render);
}

void Window::color(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(this->render, r, g, b, a);
}

void Window::DrawCase(Box item)
{
    Coord pos = item.getCoord();
    int box[100][4];
    item.getBox(&box);

    int c = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            this->SetPixel(pos.x + i, pos.y + j, box[c][3], box[c][2], box[c][1], box[c][0]);
            c++;
        }
    }
}

Window::~Window()
{
    this->close();
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

/*

 void on(std::string, void (*)(Window, std::string));
    void emit(std::string, std::string);
    std::vector<std::pair<std::string, void (*)(Window, std::string)>> events;

void Window::on(std::string name, void (*callback)(Window, std::string))
{
    std::pair<std::string, void (*)(Window, std::string)> event = {name, callback};
    this->events.push_back(event);
}

void Window::emit(std::string name, std::string data)
{
    for (std::pair<std::string, void (*)(Window, std::string)> event : this->events)
    {
        if (event.first == name)
        {
            (*event.second)(*this, data);
        }
    }
}

*/