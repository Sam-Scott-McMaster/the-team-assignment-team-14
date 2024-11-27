#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "secrets.h"

void Letter() {
    // Creates a new window and renderer 
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *newWindow = SDL_CreateWindow("Letter Clue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);

    //displays image 
    SDL_Surface *newLetter = IMG_Load("images/letter.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(newRenderer, newLetter);
    SDL_FreeSurface(newLetter); 

    int letterOpen = 1; //true
    SDL_Event event;
    while (letterOpen) {  //to keep window open until user quits 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                letterOpen = 0;
            }
        }

        // Clear render and texture
        SDL_RenderClear(newRenderer);
        SDL_RenderCopy(newRenderer, texture, NULL, NULL);
        SDL_RenderPresent(newRenderer);
    }

    // Destory once user clicks out
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(newRenderer);
    SDL_DestroyWindow(newWindow);
}