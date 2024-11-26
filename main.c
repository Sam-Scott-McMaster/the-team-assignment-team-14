// Purpose: Secrets of Summerside.
// Author: Tharny Elilvannan, McMaster University
// Last Updated: Tuesday, November 26, 2024
// This program uses the SDL and SDL_image libraries.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "secrets.h"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    if (IMG_Init(IMG_INIT_PNG) == 0) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    SDL_Window* window = SDL_CreateWindow("SECRETS OF SUMMERSIDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 1000, SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;

    // create corkboard screen
    SDL_Surface *corkboard = IMG_Load("images/Corkboard-Main.png");
    SDL_Texture *corkboardTexture = SDL_CreateTextureFromSurface(renderer, corkboard);

    // create introduction screen
    SDL_Surface *introduction = IMG_Load("images/Introduction.png");
    SDL_Texture *introductionTexture = SDL_CreateTextureFromSurface(renderer, introduction);

    if (renderer == NULL) {

        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    SDL_Rect continueButton = {20, 20, 20, 20};

    bool run = true;

    while (run) {

        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowKeyboardGrab(window, SDL_TRUE);
        SDL_SetWindowMouseGrab(window, SDL_TRUE);
        SDL_SetWindowGrab(window, SDL_TRUE);
        
        // draw border
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &border);

        // draw corkboard
        // SDL_SetRenderDrawColor(renderer, 189, 154, 122, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &corkboard);

        // render picture
        SDL_RenderCopy(renderer, introductionTexture, NULL, NULL);

        SDL_RenderDrawRect(renderer, &continueButton);

        // display
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                run = false;

            } // end of if statement

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                int x = event.button.x; 
                int y = event.button.y; 

                if (x >= continueButton.x && x <= (continueButton.x + continueButton.w) && y >= continueButton.y && y <= (continueButton.y + continueButton.h)) {
                
                    SDL_RenderCopy(renderer, corkboardTexture, NULL, NULL);

                    SDL_RenderPresent(renderer);
                    
                    while (run) {

                        while (SDL_PollEvent(&event)) {

                            if (event.type == SDL_QUIT) {

                            run = false;
                        
                            } // end of if statement

                        } // end of while loop

                     } // end of while loop
                
                } // end of if statement

            } // end of if statement

        } // end of while loop

    } // end of while loop

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    exit(EXIT_SUCCESS);

} // end of main function