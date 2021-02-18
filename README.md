# MyCity

## Game Play

Create your own map or share it with your friends.

> Export Map

Press the "p" key and wait.

> Import Map

```cmd
./bin/main.exe <your_folder_location>
```

## Textures

Create your own textures and load them into the game.

> Create texture

Download the version "TextureCreatorPack.zip" and extract it, then open the "Release (exe)" folder and run the executable.
A window will appear, you can create a box and export it or also import an old box and then export it.

> Source add texture

- clone the repos
- run setup.bat (installing SDL)
- check your gcc version (build.bat)
  - gcc version 8.1.0 (x86_64-win32-seh-rev0, Built by MinGW-W64 project)
- go to "src" dir

In the window.h file at the bottom, you will find a section:

- Groupe section

```cpp
std::vector<GroupItem> GroupeLoadList =
{
    {// std::vector<std::string>

        // home make a cube
        "home", // icon for button

        {   // std::vector<std::string>
        "home/g1",  // (x,y)
        "home/g2",  // (x + 1,y)
        "home/g3",  // (x,y + 1)
        "home/g4",  // (x + 1,y + 1)
        },

        2 // line break (y + ...)
    }
};
```

- Texture section

```cpp

std::vector<std::string> TextureLoadList =
{
    // default textures
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
    // add your texture here 
    
    /*
    textures are load in ./assets/resources/<file>.box
    can be "water" -> ./assets/resources/water.box
    or "folder/test" -> ./assets/resources/folder/test.box
    */
};

```
