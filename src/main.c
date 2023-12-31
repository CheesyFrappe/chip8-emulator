#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include <Windows.h>
#include "chip8.h"
#include "chip8keyboard.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("You must provide a file to load\n");
        return -1;
    }

    const char* filename = argv[1];
    printf("The filename to load is %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if(!f)
    {
        printf("Failed to open the file\n");
        return -1;
    }

    fseek(f, 0, SEEK_END);  // seeks eof to see the size of the file
    long size = ftell(f);   // return size 
    fseek(f, 0, SEEK_SET);  // set to beginning to start reading

    char buffer[size];
    int res = fread(buffer, size, 1, f);
    if(res != 1)
    {
        printf("Failed to read from file\n");
        return -1;
    } 

    struct chip8 chip8;
    chip8_init(&chip8); // initialize chip8 by setting its value NULL
    chip8_load(&chip8, buffer, size); // loads program to memory
    chip8_keyboard_set_map(&chip8.keyboard, keyboard_map);
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, // undefined position for x-axis
        SDL_WINDOWPOS_UNDEFINED, // undefined position for x-axis
        CHIP8_WINDOW_MULTIPLIER * CHIP8_WIDTH,
        CHIP8_WINDOW_MULTIPLIER * CHIP8_HEIGHT,
        SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // handles events by polling events from library and storing it in variable
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto out;
                break;

            case SDL_KEYDOWN:
            {
                char key = event.key.keysym.sym;
                int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                if (vkey != -1)
                {
                    chip8_keyboard_down(&chip8.keyboard, vkey);
                }
            }
            break;

            case SDL_KEYUP:
            {
                char key = event.key.keysym.sym;
                int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                if (vkey != -1)
                {
                    chip8_keyboard_up(&chip8.keyboard, vkey);
                }
            }
            break;
            };
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // alpha value followed by RGB values
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_WIDTH; x++)
        {
            for (int y = 0; y < CHIP8_HEIGHT; y++)
            {
                if (chip8_screen_is_set(&chip8.screen, x, y))
                {
                    /*
                        CHIP8 emulator has a 64x32 display.
                        Since this is very small for today's machines, it should be displayed 10x bigger.
                        Hence, coordinates and sizes of the pixel is multiplied by 'CHIP8_WINDOW_MULTIPLIER'.
                    */
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;  
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer); // apply the changes

        if (chip8.registers.delay_timer > 0)
        {
            Sleep(1);
            chip8.registers.delay_timer -= 1;
            //printf("Delay\n");
        }

        if (chip8.registers.sound_timer > 0)
        {
            Beep(17500, 10 * chip8.registers.sound_timer);
            chip8.registers.sound_timer = 0;
        }

        // char = 8 bits (1 byte)
        // short = 16 bits (2 byte)
        unsigned short opcode = chip8_memory_get_short(&chip8.memory, chip8.registers.PC);
        chip8.registers.PC += 2;
        chip8_exec(&chip8, opcode);
        //printf("%x\n", opcode);

    }

out:
    SDL_DestroyWindow(window);
    return 0;
}