#ifndef MINESWEAPER_RESETBUTTON_H
#define MINESWEAPER_RESETBUTTON_H

#include "main.h"

class ResetButton {
public:
    ResetButton (int a, int b, int c, SDL_Renderer* renderer, int n, SDL_Texture** mass);
    ~ResetButton();

    int drawButton(SDL_Renderer* renderer);
    int state (SDL_Event event);
    int setWinner();
    int setLooser();
    int inGame();
private:
    int x, y, s, num;
    SDL_Texture** textures;
    int curTexture;
};

#endif //MINESWEAPER_RESETBUTTON_H
