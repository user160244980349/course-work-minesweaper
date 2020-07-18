#ifndef MINESWEAPER_BACKGROUND_H
#define MINESWEAPER_BACKGROUND_H

#include "main.h"

class Background {
public:
    Background (SDL_Renderer* renderer);
    ~Background ();

    int drawBackground (SDL_Renderer* renderer);
private:
    SDL_Texture* background;
};

#endif //MINESWEAPER_BACKGROUND_H
