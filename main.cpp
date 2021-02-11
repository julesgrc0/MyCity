#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "src/window.h"
#include "src/box.h"

int main(int argc, char **argv)
{
    std::string import = "";
    if (argc >= 2)
    {
        import = std::string(argv[1]);
    }

    Window win = Window("MyCity", 800, 500, import);
    return 0;
}
