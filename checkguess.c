/* 
 * 
 * This function will check the user's guess (if it's correct or not)
 * on mac before executing: export DYLD_FRAMEWORK_PATH=/Library/Frameworks
 * 
 * McMaster University
 * 
 * */

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

void checkguess() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    }

    // create window and renderer
    SDL_Window* window = SDL_CreateWindow("Guess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event; // initialize events

    if (renderer == NULL) {
        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement
    
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    if (!font){
        fprintf(stderr, "No font loaded: %s\n", TTF_GetError());
        return;
    }

    // make textboxes
    SDL_Color textColor = {0, 0, 0}; 

    // text 1: Shaun
    SDL_Surface *shaun = TTF_RenderText_Solid(font, "Shaun", textColor); 
    SDL_Texture *shaunTexture = SDL_CreateTextureFromSurface(renderer, shaun); 

    // text 2: Glen
    SDL_Surface *glen = TTF_RenderText_Solid(font, "Glen", textColor); 
    SDL_Texture *glenTexture = SDL_CreateTextureFromSurface(renderer, glen); 

    // text 3: Clayton
    SDL_Surface *clayton = TTF_RenderText_Solid(font, "Clayton", textColor); 
    SDL_Texture *claytonTexture = SDL_CreateTextureFromSurface(renderer, clayton); 

    
    // draw rectangles
    SDL_Rect border = {0,0,600, 400}; 
    SDL_Rect background = {10, 10, 580, 380}; 

    // draw buttons for each person
    SDL_Rect shaunButton = {570, 200, 100, 50};
    SDL_Rect shaunText = {shaunButton.x + 25 , shaunButton.y + 4, 50, 20}; 

    SDL_Rect glenButton = {370, 200, 100, 50};
    SDL_Rect glenText = {glenButton.x + 25 , glenButton.y + 4, 50, 20}; 

    SDL_Rect claytonButton = {170, 200, 100, 50};
    SDL_Rect claytonText = {claytonButton.x + 25 , claytonButton.y + 4, 50, 20}; 
    
    bool run = true;

    while (run) {
        SDL_RenderClear(renderer);

        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowKeyboardGrab(window, SDL_TRUE);
        SDL_SetWindowMouseGrab(window, SDL_FALSE);
        SDL_SetWindowGrab(window, SDL_FALSE);
        
        // draw border
        SDL_SetRenderDrawColor(renderer, 197, 183, 124, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &border);


        // draw background
        SDL_SetRenderDrawColor(renderer, 240, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &background); 
       
       // draw shaun button
        SDL_SetRenderDrawColor(renderer, 178, 190, 181, SDL_ALPHA_OPAQUE); 
        SDL_RenderFillRect(renderer, &shaunButton); 
        SDL_RenderCopy(renderer, shaunTexture, NULL, &shaunText); 

        // draw glen button
        SDL_SetRenderDrawColor(renderer, 178, 190, 181, SDL_ALPHA_OPAQUE); 
        SDL_RenderFillRect(renderer, &glenButton); 
        SDL_RenderCopy(renderer, glenTexture, NULL, &glenText); 

        // draw clayton button
        SDL_SetRenderDrawColor(renderer, 178, 190, 181, SDL_ALPHA_OPAQUE); 
        SDL_RenderFillRect(renderer, &claytonButton); 
        SDL_RenderCopy(renderer, claytonTexture, NULL, &claytonText); 

        // display
        SDL_RenderPresent(renderer);
        SDL_Delay(100); 

        // handles events
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                run = false;
            } 

            // handling mouse click
            if (event.type == SDL_MOUSEBUTTONDOWN){
                // coordinates of where the click occured
                int x = event.button.x; 
                int y = event.button.y; 

                 // if the click is inside the button
                if (x >= shaunButton.x && x <= (shaunButton.x + shaunButton.w) &&
                    y >= shaunButton.y && y <= (shaunButton.y + shaunButton.h)) {
                    printf("Shaun\n");  
                }

                if (x >= glenButton.x && x <= (glenButton.x + glenButton.w) &&
                    y >= glenButton.y && y <= (glenButton.y + glenButton.h)) {
                    printf("Glen\n");  
                }

                if (x >= claytonButton.x && x <= (claytonButton.x + claytonButton.w) &&
                    y >= claytonButton.y && y <= (claytonButton.y + claytonButton.h)) {
                    printf("Clayton\n");  
                }
            }
        } 

    } // end of while loop

    SDL_DestroyTexture(shaunTexture); 
    SDL_DestroyTexture(glenTexture);
    SDL_DestroyTexture(claytonTexture);
    SDL_FreeSurface(shaun);
    SDL_FreeSurface(glen);
    SDL_FreeSurface(clayton); 
    TTF_CloseFont(font); 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
} 

int main(int argc, char *argv[]){
    checkguess(); 
}