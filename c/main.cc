#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    srand(time(NULL));

    const int kTileCount = 20;
    const int kTileSize = 20;
    const int kTileGapSize = 1;
    const int kWindowSize = kTileCount * kTileSize + (kTileCount + 1) * kTileGapSize;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(kWindowSize, kWindowSize, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect sdl_rect;
    sdl_rect.w = kTileSize;
    sdl_rect.h = kTileSize;
    for (int y = 0; y < kTileCount; ++y) {
        for (int x = 0; x < kTileCount; ++x) {
            if ((float(rand()) / float(RAND_MAX)) < 0.5f) continue;

            sdl_rect.x = kTileGapSize + x * (kTileSize + kTileGapSize);
            sdl_rect.y = kTileGapSize + y * (kTileSize + kTileGapSize);
            SDL_RenderFillRect(renderer, &sdl_rect);
        }
    }

    SDL_RenderPresent(renderer);

    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
