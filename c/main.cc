#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

struct Player {
    int x;
    int y;
};

int main(int argc, char *argv[])
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    srand((int)time(NULL));

    const int kTileCount = 20;
    const int kTileSize = 20;
    const int kTileGapSize = 1;
    const int kWindowSize = kTileCount * kTileSize + (kTileCount + 1) * kTileGapSize;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(kWindowSize, kWindowSize, 0, &window, &renderer);

    const int kTargetFPS = 60;
    const Uint32 kFrameMS = 1000 / kTargetFPS;  // of course not precise

    Player player;
    player.x = kTileCount / 2;
    player.y = kTileCount / 2;

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (true) {
        Uint32 start_time = SDL_GetTicks();

        SDL_PumpEvents();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Update
        if (keystate[SDL_SCANCODE_LEFT]) {
            player.x -= 1;
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            player.x += 1;
        }
        if (keystate[SDL_SCANCODE_UP]) {
            player.y -= 1;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            player.y += 1;
        }

        player.x = (player.x + kTileCount) % kTileCount;
        player.y = (player.y + kTileCount) % kTileCount;

        // Render
        SDL_Rect sdl_rect;
        sdl_rect.w = kTileSize;
        sdl_rect.h = kTileSize;
        sdl_rect.x = kTileGapSize + player.x * (kTileSize + kTileGapSize);
        sdl_rect.y = kTileGapSize + player.y * (kTileSize + kTileGapSize);
        SDL_RenderFillRect(renderer, &sdl_rect);

        SDL_RenderPresent(renderer);

        const Uint32 frame_time = (SDL_GetTicks() - start_time);
        if (frame_time < kFrameMS) {
            SDL_Delay(kFrameMS - frame_time);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
