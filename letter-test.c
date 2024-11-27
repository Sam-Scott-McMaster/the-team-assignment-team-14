#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int Letter() {
    // Initialize SDL
    //if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       // printf("SDL_Init failed: %s\n", SDL_GetError());
        //return EXIT_FAILURE;  // Error occurred
   // }

    // Create window
    SDL_Window *newWindow = SDL_CreateWindow("Letter Clue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!newWindow) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;  // Error occurred
    }

    // Create renderer
    SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!newRenderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(newWindow);
        SDL_Quit();
        return EXIT_FAILURE;  // Error occurred
    }

    // Load image
    SDL_Surface *newLetter = IMG_Load("images/letter.png");
    if (!newLetter) {
        printf("IMG_Load failed: %s\n", IMG_GetError());
        SDL_DestroyRenderer(newRenderer);
        SDL_DestroyWindow(newWindow);
        SDL_Quit();
        return EXIT_FAILURE;  // Error occurred
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(newRenderer, newLetter);
    SDL_FreeSurface(newLetter);
    if (!texture) {
        printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(newRenderer);
        SDL_DestroyWindow(newWindow);
        SDL_Quit();
        return EXIT_FAILURE;  // Error occurred
    }

    // Simulate running for 2 seconds
    Uint32 startTime = SDL_GetTicks();
    int letterOpen = 1;  // true
    SDL_Event event;
    while (letterOpen) {  // keep window open until user quits 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                letterOpen = 0;
            }
        }
        if (SDL_GetTicks() - startTime >= 2000) {
            letterOpen = 0; // close after 2 seconds for testing purposes
        }

        // Clear render and texture
        SDL_RenderClear(newRenderer);
        SDL_RenderCopy(newRenderer, texture, NULL, NULL);
        SDL_RenderPresent(newRenderer);
    }

    // Destroy resources after use
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(newRenderer);
    SDL_DestroyWindow(newWindow);
    SDL_Quit();

    return EXIT_SUCCESS;  // Success
}

