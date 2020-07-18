#include "../include/Minefield.h"
#include "../include/Utilities.h"

using namespace std;

Minefield::Minefield (SDL_Renderer* renderer, int x, int y, int n, SDL_Texture** mass) {
    width = x, height = y, num = n; numOfFlags = 0;
    initSymbols();
    createInvisiblePart ();
    plantMines ();
    setTips ();
    textures = mass;
    btnSize = 35;
    buttons = initButtons ((WINDOW_WIDTH - width * btnSize) / 2, 120);
}
Minefield::~Minefield () {
    for (int i = 0; i < height; i++) {
        delete buttons[i];
        delete invisiblePart[i];
    }
    delete symbols;
    delete buttons;
    delete invisiblePart;
}

int Minefield::createInvisiblePart () {
    invisiblePart = new char*[height];
    if (invisiblePart == NULL) {
        cout << "Ошибка создания поля" << endl;
        return -1;
    }
    for (int i = 0; i < height; i++) {
        invisiblePart[i] = new char[width];
        if (invisiblePart[i] == NULL) {
            cout << "Ошибка создания поля" << endl;
            return -1;
        }
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            invisiblePart[i][j] = '0';
    return 0;
}
int Minefield::initSymbols () {
    symbols = new char[10];
    if (symbols == NULL) {
        cout << "Ошибка инициализации символов!" << endl;
        return -1;
    }
    for (int i = 0; i < 10; i++)
        symbols[i] = '0' + i;
    return 0;
}
int Minefield::plantMines () {
    int x, y, n = num;
    srand(time(NULL));
    while (n) {
        x = rand () % width;
        y = rand () % height;
        if (invisiblePart[y][x] == '0') {
            invisiblePart[y][x] = 'x';
            n--;
        }
    }
    return 0;
}
int Minefield::checkMines (int x, int y) {
    int n = 0;
    for (int i = y - 1; i <= y + 1; i++)
        for (int j = x - 1; j <= x + 1; j++) {
            if (i < height && i >= 0 && j < width && j >= 0) {
                if (invisiblePart[i][j] == 'x')
                    n++;
            }
        }
    return n;
}
int Minefield::setTips () {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            if (invisiblePart[i][j] != 'x')
                invisiblePart[i][j] = symbols[checkMines (j, i)];
        }
    return 0;
}
int Minefield::openNearNull (int x, int y) {
    for (int k = y - 1; k <= y + 1; k++)
        for (int z = x - 1; z <= x + 1; z++)
            if (k < height && k >= 0 && z < width && z >= 0 && buttons[k][z].returnChar() == '-' && invisiblePart[k][z] != '-')
                buttons[k][z] = invisiblePart[k][z];
    return 0;
}
int Minefield::openNulls (int x, int y) {
    int n = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i < height && i >= 0 && j < width && j >= 0) {
                if (invisiblePart[i][j] == '0') {
                    openNearNull(j, i);
                    invisiblePart[i][j] = '-';
                    openNulls(j, i);
                }
            }
        }
    }
    return false;
}
bool Minefield::openSquare (int x, int y) {
    if (buttons[y][x].returnChar() == 'f')
        return false;
    if (invisiblePart[y][x] == '-')
        buttons[y][x] = '0';
    else
        buttons[y][x] = invisiblePart[y][x];
    if (buttons[y][x].returnChar () == 'x')
        return true;
    else
        return false;
}
Button** Minefield::initButtons (int x, int y) {
    Button** btns = new Button*[height];
    for (int i = 0; i < height; i++)
        btns[i] = new Button[width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            btns[i][j].initButton (x + i * btnSize, y + j * btnSize, btnSize, textures);
    return btns;
}
bool Minefield::open (int x, int y) {
    if (buttons[y][x].returnChar () == 'f')
        return false;
    if (invisiblePart[y][x] == '0')
        return openNulls(x, y);
    else
        return openSquare(x, y);
}
bool Minefield::flag (int x, int y) {
    if (buttons[y][x].returnChar () == '-') {
        buttons[y][x] = 'f';
        numOfFlags++;
        return 0;
    }
    if (buttons[y][x].returnChar () == 'f') {
        buttons[y][x] = '-';
        numOfFlags--;
        return 0;
    }
    return 0;
}
int Minefield::drawMap (SDL_Renderer* renderer) {
    drawImage(renderer, textures[13], (int) (WINDOW_WIDTH - width * btnSize) / 2 - 3, 118, width * btnSize + 6,
              height * btnSize + 5);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            buttons[i][j].drawButton(renderer);
    return 0;
}
int Minefield::refreshBtns (SDL_Event event) {
    int trigger;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            trigger = buttons[i][j].state (event);
            if (trigger == 1) {
                return open(j,i);
            }
            if (trigger == 2) {
                return flag(j,i);
            }
        }
    return false;
}
bool Minefield::win () {
    int n = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (buttons[i][j].returnChar () == '-' || buttons[i][j].returnChar () == 'f')
                n++;
        }
    }
    if (n == num)
        return true;
    else
        return false;
}
int Minefield::returnNumOfFlags () {
    return numOfFlags;
}
int Minefield::openMap () {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (invisiblePart[i][j] == '-')
                buttons[i][j] = '0';
            else
                buttons[i][j] = invisiblePart[i][j];
    return 0;
}
int Minefield::resetMap () {
    for (int i = 0; i < height; i++)
        delete invisiblePart[i];
    delete invisiblePart;
    createInvisiblePart ();
    plantMines ();
    setTips ();
    for (int i = 0; i < height; i++)
        delete buttons[i];
    delete buttons;
    buttons = initButtons ((WINDOW_WIDTH - width * btnSize) / 2, 120);
    return 0;
}
