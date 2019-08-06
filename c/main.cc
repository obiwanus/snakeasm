#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

enum Direction {
    RIGHT = 0,
    LEFT,
    UP,
    DOWN,
};

struct Snake {
    int x;
    int y;
    Direction direction;
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

    Snake snake;
    snake.x = kTileCount / 2;
    snake.y = kTileCount / 2;
    snake.direction = RIGHT;

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    int frames_per_move = 30;  // determines game speed
    int frames_since_last_move = 30;

    // Frame loop
    while (true) {
        Uint32 frame_start_time = SDL_GetTicks();

        SDL_PumpEvents();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;

        // Collect input
        if (keystate[SDL_SCANCODE_LEFT]) {
            snake.direction = LEFT;
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            snake.direction = RIGHT;
        }
        if (keystate[SDL_SCANCODE_UP]) {
            snake.direction = UP;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            snake.direction = DOWN;
        }

        frames_since_last_move++;
        if (frames_since_last_move >= frames_per_move) {
            frames_since_last_move = 0;

            // Move the snake
            switch (snake.direction) {
                case LEFT: {
                    snake.x -= 1;
                } break;
                case RIGHT: {
                    snake.x += 1;
                } break;
                case UP: {
                    snake.y -= 1;
                } break;
                case DOWN: {
                    snake.y += 1;
                } break;
            }

            // Wrap around the area
            snake.x = (snake.x + kTileCount) % kTileCount;
            snake.y = (snake.y + kTileCount) % kTileCount;

            // Render
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_Rect sdl_rect;
            sdl_rect.w = kTileSize;
            sdl_rect.h = kTileSize;
            sdl_rect.x = kTileGapSize + snake.x * (kTileSize + kTileGapSize);
            sdl_rect.y = kTileGapSize + snake.y * (kTileSize + kTileGapSize);
            SDL_RenderFillRect(renderer, &sdl_rect);

            SDL_RenderPresent(renderer);
        }

        const Uint32 frame_time = (SDL_GetTicks() - frame_start_time);
        if (frame_time < kFrameMS) {
            SDL_Delay(kFrameMS - frame_time);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
