#include "../include/Background.h"
#include "../include/Utilities.h"

using namespace std;

Background::Background (SDL_Renderer* renderer) {
    loadTexture ("Resources/background/background.png", renderer, &background);
}
Background::~Background () {
    SDL_DestroyTexture (background);
}
int Background::drawBackground (SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, NULL, NULL);
    return 0;
}

