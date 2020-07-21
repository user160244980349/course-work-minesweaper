#include "../include/main.h"
#include "../include/Utilities.h"

int main(int argc, char *argv[]) {
    char name[] = "MineSweaper";
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "Ошибка инициализации библиотеки SDL!" << std::endl;
        return -1;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "Ошибка инициализации библиотеки IMG!" << std::endl;
        return -1;
    }

    window = SDL_CreateWindow (name, 10, 10, WINDOW_WIDTH, WINDOW_HEIGHT, !SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Ошибка создания окна!" << std::endl;
        return -1;
    }

    SDL_Surface* icon = IMG_Load("resources/icon/icon.png");
    SDL_SetWindowIcon(window, icon);
    renderer = SDL_CreateRenderer (window, 1, 0);
    if (renderer == NULL) {
        std::cout << "Ошибка создания рендера!" << std::endl;
        return -1;
    }

    mainLoop(renderer);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
