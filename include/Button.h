#ifndef MINESWEAPER_BUTTON_H
#define MINESWEAPER_BUTTON_H

#include "main.h"

class Button {
public:
    int initButton (int a, int b, int c, SDL_Texture** mass);
    int drawButton(SDL_Renderer* renderer);
    int state (SDL_Event event);
    int operator = (char a);
    char returnChar ();
private:
    SDL_Texture** textures;
    int x, y, s;
    int curTexture;
};

#endif //MINESWEAPER_BUTTON_H
