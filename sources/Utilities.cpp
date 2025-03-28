#include "../include/Utilities.h"

int mainLoop (SDL_Renderer* renderer) {
    string minefieldBtnNames[] = {  "resources/field/empty.png",
                                    "resources/field/1.png",
                                    "resources/field/2.png",
                                    "resources/field/3.png",
                                    "resources/field/4.png",
                                    "resources/field/5.png",
                                    "resources/field/6.png",
                                    "resources/field/7.png",
                                    "resources/field/8.png",
                                    "resources/field/9.png",
                                    "resources/field/button.png",
                                    "resources/field/flag.png",
                                    "resources/field/mine.png",
                                    "resources/field/field.png",
                                    "resources/field/empty.png"};
    string resetBtnNames[] = {      "resources/reset/normal.png",
                                    "resources/reset/loose.png",
                                    "resources/reset/win.png"};
    SDL_Texture** minefieldBtnTextures = loadTextures(renderer, 15, minefieldBtnNames);
    SDL_Texture** resetBtnTextures = loadTextures(renderer, 4, resetBtnNames);
    Minefield* map = new Minefield (renderer, 10, 10, 15, minefieldBtnTextures);
    ResetButton* reset = new ResetButton ((WINDOW_WIDTH - 50) / 2, 25, 60, renderer , 4, resetBtnTextures);
    Background* back  = new Background (renderer);

    Uint32 time = 0;
    Uint32 deltaTime = 0;
    SDL_Event event;
    bool over = false;
    while(true) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                for (int i = 0; i < 15; i++)
                    SDL_DestroyTexture(minefieldBtnTextures[i]);
                for (int i = 0; i < 3; i++)
                    SDL_DestroyTexture(resetBtnTextures[i]);
                delete map;
                delete reset;
                delete back;
                return 0;
            }
            if (reset->state(event)) {
                reset->inGame();
                map->resetMap();
                over = false;
            }
            if (map->refreshBtns(event) && !over) {
                reset->setLooser();
                map->openMap();
                over = true;
            }
            if (map->win()) {
                reset->setWinner();
                map->openMap();
                over = true;
            }
            SDL_RenderClear(renderer);
            back->drawBackground(renderer);
            reset->drawButton(renderer);
            map->drawMap(renderer);
            SDL_RenderPresent(renderer);
        }

        deltaTime = SDL_GetTicks() - time;
        if (deltaTime < 16)
            SDL_Delay(16 - deltaTime);
    }
}
int drawImage (SDL_Renderer* renderer, SDL_Texture* img, int x, int y, int w, int h) {
    SDL_Rect desc;
    desc.x = x;
    desc.y = y;
    desc.w = w;
    desc.h = h;
    SDL_RenderCopy(renderer, img, NULL, &desc);
    return 0;
}
SDL_Texture* loadTexture (const char* path, SDL_Renderer* renderer, SDL_Texture** texture) {
    SDL_Surface* image = IMG_Load(path);
    if (image == NULL) {
        cout << "Ошибка загрузки текстуры!" << endl;
        return NULL;
    }
    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface (image);
    return 0;
}
SDL_Texture** loadTextures (SDL_Renderer* renderer, int n, string* names) {
    SDL_Texture** textures = new SDL_Texture*[n];
    for (int i = 0; i < n; i++)
        loadTexture (names[i].c_str(), renderer, &textures[i]);
    return textures;
}
