#include <stdio.h>
#include "SDL2/SDL.h"
#include "config.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,    // undefined position for x-axis
        SDL_WINDOWPOS_UNDEFINED,    // undefined position for x-axis
        CHIP8_WINDOW_MULTIPLIER * CHIP8_WIDTH, 
        CHIP8_WINDOW_MULTIPLIER * CHIP8_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    while(1)
    {   
        SDL_Event event;
        while(SDL_PollEvent(&event))    // handles events by polling events from library and storing it in variable
        {
            if(event.type == SDL_QUIT)
            {
                goto out;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // alpha value followed by RGB values
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 40;
        r.h = 40;
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);    // apply the changes
    }

out:
    SDL_DestroyWindow(window);
    return 0;
}