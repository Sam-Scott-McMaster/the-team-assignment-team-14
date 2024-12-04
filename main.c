// Purpose: Secrets of Summerside.
// Author: Tharny Elilvannan, McMaster University
// Last Updated: December 04, 2024
// This program uses the SDL, SDL_ttf, and SDL_image libraries.

// Changes by: Meigan Rogers

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __APPLE_CC__
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "secrets.h"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


int main(int argc, char *argv[]) {

     if (strcmp(argv[1], "--help") == 0) {

            help_commandline();
            exit(EXIT_SUCCESS);

    } // end of if statement

    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    // initialize SDL image
    if (IMG_Init(IMG_INIT_PNG) == 0) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if 

    // initialize SDL font
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    // create the main window
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

    //buttons
    SDL_Rect continueButton = {1390, 875, 345, 80};
    SDL_Rect map = {185, 614, 235, 266};
    SDL_Rect recipe = {739, 180, 273, 364};
    SDL_Rect letter = {1485, 226, 322, 218};
    SDL_Rect guessButton = {1623, 821, 305, 80};
    SDL_Rect helpButton = {1720, 14, 146, 33};

    
    bool runIntro = true;
    bool run = false; 

    // draws the introduction page
    while (runIntro) {

        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowMouseGrab(window, SDL_TRUE);
        SDL_SetWindowGrab(window, SDL_TRUE);

        // render picture
        SDL_RenderCopy(renderer, introductionTexture, NULL, NULL);
        SDL_RenderDrawRect(renderer, &continueButton);

        // display
        SDL_RenderPresent(renderer);
        SDL_Delay(100);

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                runIntro = false;
            } // end of if statement

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                int x = event.button.x; 
                int y = event.button.y; 

                if (x >= continueButton.x && x <= (continueButton.x + continueButton.w) && y >= continueButton.y && y <= (continueButton.y + continueButton.h)) {
                    runIntro = false; 
                    run = true; 
                
                } // end of if statement

            } // end of if statement

        } // end of while loop

    } // end of while loop

    // draws main corkboard
    while (run) {

        SDL_SetWindowMouseGrab(window, SDL_FALSE);
        SDL_SetWindowGrab(window, SDL_FALSE);

        SDL_RenderClear(renderer);
        // draw the button rectangles on the window
        SDL_RenderCopy(renderer, corkboardTexture, NULL, NULL);
        SDL_RenderDrawRect(renderer, &map);
        SDL_RenderDrawRect(renderer, &recipe);
        SDL_RenderDrawRect(renderer, &letter);
        SDL_RenderDrawRect(renderer, &guessButton);
        SDL_RenderDrawRect(renderer, &helpButton);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                run = false;
                        
            } // end of if statement

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // coordinates of the mouse click
                int x = event.button.x; 
                int y = event.button.y; 
                
                // if the map was clicked
                if (x >= map.x && x <= (map.x + map.w) && y >= map.y && y <= (map.y + map.h)) {
                    SDL_Window* mapWindow = SDL_CreateWindow("Map View", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
                    SDL_Delay(100); 
                    openMap(mapWindow);
                    SDL_Delay(100); 
                    SDL_DestroyWindow(mapWindow); 
                    mapWindow = NULL; 
                    SDL_PumpEvents();
                    SDL_Delay(2000);
                    break; 
                } // end of if statement

                // if the recipe was clicked
                if (x >= recipe.x && x <= (recipe.x + recipe.w) && y >= recipe.y && y <= (recipe.y + recipe.h)) {
                    SDL_Window *recipeWindow = SDL_CreateWindow("Recipe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
                    SDL_Delay(100); 
                    openRecipe(recipeWindow);
                    SDL_Delay(100); 
                    SDL_DestroyWindow(recipeWindow); 
                    recipeWindow = NULL;  
                    SDL_PumpEvents(); 
                    SDL_Delay(2000);
                    break; 
                } // end of if statement

                // if the letter was clicked
                if (x >= letter.x && x <= (letter.x + letter.w) && y >= letter.y && y <= (letter.y + letter.h)) {
                    SDL_Window *letterWindow = SDL_CreateWindow("Letter Clue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
                    SDL_Delay(100); 
                    Letter(letterWindow);
                    SDL_Delay(100); 
                    SDL_DestroyWindow(letterWindow); 
                    letterWindow = NULL;  
                    SDL_PumpEvents(); 
                    SDL_Delay(2000);
                    break; 
                } // end of if statement

                // if the guess button was clicked
                if (x >= guessButton.x && x <= (guessButton.x + guessButton.w) && y >= guessButton.y && y <= (guessButton.y + guessButton.h)) {
                    checkguess();
                    SDL_DestroyWindow(window);
                    SDL_DestroyRenderer(renderer);
                    SDL_Quit();
                    IMG_Quit();
                    TTF_Quit(); 
                    exit(EXIT_SUCCESS);
                } // end of if statement

                // if the help button was clicked
                if (x >= helpButton.x && x <= (helpButton.x + helpButton.w) && y >= helpButton.y && y <= (helpButton.y + helpButton.h)) {
                    SDL_Window *helpWindow = SDL_CreateWindow("--help", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
                    SDL_Delay(100); 
                    openHelp(helpWindow);
                    SDL_Delay(100); 
                    SDL_DestroyWindow(helpWindow); 
                    helpWindow = NULL;  
                    SDL_PumpEvents(); 
                    SDL_Delay(2000);
                    break; 
                } // end of if statement

            } // end of if statement

        } // end of while loop

    } // end of while loop

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit(); 
    exit(EXIT_SUCCESS);

} // end of main function