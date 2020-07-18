#include "../include/ResetButton.h"
#include "../include/Utilities.h"

using namespace std;

ResetButton::ResetButton (int a, int b, int c, SDL_Renderer* renderer, int n, SDL_Texture** mass) {
    x = a;
    y = b;
    s = c;
    num = n;
    textures = mass;
    curTexture = 0;
}
ResetButton::~ResetButton() {

}

int ResetButton::drawButton(SDL_Renderer* renderer) {
    drawImage(renderer, textures[curTexture], x, y, s, s);
    return 0;
}
int ResetButton::state (SDL_Event event) {
    static bool pressedL;
    static bool pressedR;
    if ((event.button.x > x) &&
        (event.button.x < x + s) &&
        (event.button.y > y) &&
        (event.button.y < y + s)) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (event.type == SDL_MOUSEBUTTONDOWN)
                pressedL = true;
            if (event.type == SDL_MOUSEBUTTONUP && pressedL == true) {
                pressedL = false;
                return 1;
            }
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            if (event.type == SDL_MOUSEBUTTONDOWN)
                pressedR = true;
            if (event.type == SDL_MOUSEBUTTONUP && pressedR == true) {
                pressedR = false;
                return 2;
            }
        }
    }
    return 0;
}
int ResetButton::setWinner() {
    curTexture = 2;
    return 0;
}
int ResetButton::setLooser() {
    curTexture = 1;
    return 0;
}
int ResetButton::inGame() {
    curTexture = 0;
    return 0;
}
