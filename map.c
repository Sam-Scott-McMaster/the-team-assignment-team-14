// Purpose: Displays and interacts with a map image, allowing the user to enlarge it upon clicking.
// Author: Midhousha Anura, anuram


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
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


void openMap(SDL_Window *mapWindow) {

    // Creates the window and renderer
    //SDL_Window* window = SDL_CreateWindow("Map View", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(mapWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;


    if (renderer == NULL) {
        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
   

    // Loads the map image
    SDL_Surface *image = IMG_Load("images/map.png");
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
   
    //SDL_FreeSurface(image); 
    image = NULL; 

    // Loads the font for the text
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24);
    if (!font) {
        fprintf(stderr, "No font loaded: %s\n", TTF_GetError());
        return;
    }


    // Creates "Done" button text to allow the user to exit the window
    SDL_Color textColor = {0, 0, 0};
    SDL_Surface *text = TTF_RenderText_Solid(font, "Done", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text);

    //SDL_FreeSurface(text); 
    text = NULL; 


    // Define rectangles for drawing
    SDL_Rect border = {0, 0, 1000, 800};
    SDL_Rect picture = {10, 10, 980, 780};
    SDL_Rect button = {450, 750, 100, 25};
    SDL_Rect textBox = {button.x + 25, button.y + 4, 50, 20};


    bool runMap = true;


    while (runMap) {
        SDL_RenderClear(renderer);
        SDL_SetWindowMouseGrab(mapWindow, SDL_TRUE);
        SDL_SetWindowGrab(mapWindow, SDL_TRUE);


        // Draws border
        SDL_SetRenderDrawColor(renderer, 197, 183, 124, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &border);


        // Draws map rectangle
        SDL_SetRenderDrawColor(renderer, 189, 154, 122, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &picture);
   
        // Renders map image
        SDL_RenderCopy(renderer, imageTexture, NULL, &picture);
       
        // Draws button
        SDL_SetRenderDrawColor(renderer, 178, 190, 181, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &button);


        // Renders text on top of the button
        SDL_RenderCopy(renderer, textTexture, NULL, &textBox);


        // Updates display
        SDL_RenderPresent(renderer);
        SDL_Delay(100);


        // Handles events
        while (SDL_PollEvent(&event)) {
            // if (event.type == SDL_QUIT) {
            //     runMap = false;
            // }
            // Handles mouse click
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;


                // If the click is inside the button, close the window
                if (x >= button.x && x <= (button.x + button.w) &&
                    y >= button.y && y <= (button.y + button.h)) {
                    runMap = false; // Exit the loop and close the window 
                }
            }
            SDL_Delay(100); 
        }


    } // End of while loop

    SDL_Delay(100);
    // Cleanups and free resources
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(textTexture);
    textTexture = NULL; 
    imageTexture = NULL; 
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    renderer = NULL; 
}