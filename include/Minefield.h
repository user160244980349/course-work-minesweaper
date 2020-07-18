#ifndef MINESWEAPER_MINEFIELD_H
#define MINESWEAPER_MINEFIELD_H

#include "main.h"
#include "Button.h"

class Minefield {
public:
    Minefield (SDL_Renderer* renderer, int x, int y, int n, SDL_Texture** mass);
    ~Minefield ();

    int drawMap (SDL_Renderer* renderer);
    int refreshBtns (SDL_Event event);
    bool win ();
    int returnNumOfFlags ();
    int openMap ();
    int resetMap ();
private:
    char** invisiblePart;
    char* symbols;
    Button** buttons;
    int width, height, num, numOfFlags;
    int btnSize;
    SDL_Texture** textures;

    int createInvisiblePart ();
    int initSymbols ();
    int plantMines ();
    int checkMines (int x, int y);
    int setTips ();
    int openNearNull (int x, int y);
    int openNulls (int x, int y);
    bool openSquare (int x, int y);
    Button** initButtons (int x, int y);
    bool open (int x, int y);
    bool flag (int x, int y);
};

#endif //MINESWEAPER_MINEFIELD_H
