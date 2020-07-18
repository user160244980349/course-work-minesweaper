#ifndef MINESWEAPER_UTILITIES_H
#define MINESWEAPER_UTILITIES_H

#include "main.h"
#include "Minefield.h"
#include "ResetButton.h"
#include "Background.h"

using namespace std;

int mainLoop (SDL_Renderer* renderer);
int drawImage (SDL_Renderer* renderer, SDL_Texture* img, int x, int y, int w, int h);
SDL_Texture* loadTexture (const char* path, SDL_Renderer* renderer, SDL_Texture** texture);
SDL_Texture** loadTextures (SDL_Renderer* renderer, int n, string* names);

#endif //MINESWEAPER_UTILITIES_H
