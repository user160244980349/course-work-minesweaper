#include "../include/Button.h"
#include "../include/Utilities.h"

using namespace std;

int Button::initButton (int a, int b, int c, SDL_Texture** mass) {
    x = a;
    y = b;
    s = c;
    textures = mass;
    curTexture = 10;
    return 0;
}
int Button::drawButton(SDL_Renderer* renderer) {
    drawImage(renderer, textures[curTexture], x, y, s, s);
    return 0;
}
int Button::state (SDL_Event event) {
    static bool pressedL;
    static bool pressedR;
    if ((event.button.x > x) &&
        (event.button.x < x + s) &&
        (event.button.y > y) &&
        (event.button.y < y + s)) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                pressedL = true;
            }
            if (curTexture == 10 && pressedL)
                curTexture = 14;
            if (curTexture == 14 && !pressedL)
                curTexture = 10;
            if (event.type == SDL_MOUSEBUTTONUP && pressedL == true) {
                if (curTexture == 14)
                    curTexture = 10;
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
    else
    if (curTexture == 14)
        curTexture = 10;
    return 0;
}
int Button::operator = (char a) {

    if (a == 'f') {
        curTexture = 11;
        return 0;
    }
    if (a == '-') {
        curTexture = 10;
        return 0;
    }
    if (a == 'x') {
        curTexture = 12;
        return 0;
    }
    if (a >= '0' && a <= '9') {
        curTexture = a - '0';
        return 0;
    }
    return 0;
}
char Button::returnChar () {
    if (curTexture == 12)
        return 'x';
    if (curTexture == 11)
        return 'f';
    if (curTexture == 10)
        return '-';
    return '0' + curTexture;
}
