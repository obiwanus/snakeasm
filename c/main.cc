#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

enum Direction {
    RIGHT = 0,
    LEFT,
    UP,
    DOWN,
};

struct v2 {
    int x;
    int y;
};

#define MAX_SNAKE_SIZE 50

struct Snake {
    Direction direction;
    int size;
    v2 sections[MAX_SNAKE_SIZE];
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

    v2 start_point = {kTileCount / 2, kTileCount / 2};
    Snake snake;
    snake.direction = RIGHT;
    snake.size = 3;
    snake.sections[0] = start_point;
    snake.sections[1].x = start_point.x - 1;
    snake.sections[1].y = start_point.y;
    snake.sections[2].x = start_point.x - 2;
    snake.sections[2].y = start_point.y;

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    int frames_per_move = 30;  // determines game speed
    int frames_since_last_move = 30;

    // Frame loop
    while (true) {
        Uint32 frame_start_time = SDL_GetTicks();

        SDL_PumpEvents();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;
        if (keystate[SDL_SCANCODE_ESCAPE]) break;

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

            // Move the tail
            for (int i = snake.size - 1; i > 0; --i) {
                snake.sections[i] = snake.sections[i - 1];
            }

            // Move the head
            v2 *head = &snake.sections[0];
            switch (snake.direction) {
                case LEFT: {
                    head->x -= 1;
                } break;
                case RIGHT: {
                    head->x += 1;
                } break;
                case UP: {
                    head->y -= 1;
                } break;
                case DOWN: {
                    head->y += 1;
                } break;
            }

            // Wrap around the area
            head->x = (head->x + kTileCount) % kTileCount;
            head->y = (head->y + kTileCount) % kTileCount;

            // Render
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_Rect sdl_rect;
            sdl_rect.w = kTileSize;
            sdl_rect.h = kTileSize;
            for (int i = 0; i < snake.size; ++i) {
                sdl_rect.x = kTileGapSize + snake.sections[i].x * (kTileSize + kTileGapSize);
                sdl_rect.y = kTileGapSize + snake.sections[i].y * (kTileSize + kTileGapSize);
                SDL_RenderFillRect(renderer, &sdl_rect);
            }

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
