/* Meigan Rogers, Nov 24 2024
 * 
 * This function will "enlarge" one of the clues that the user clicks on
 * Focuses on the recipe clue
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


#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


void openRecipe() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    }

    // create window and renderer
    SDL_Window* window = SDL_CreateWindow("Recipe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
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

    // make image
    SDL_Surface * image = IMG_Load("images/recipe.png");
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    // if (!image) {
    //     fprintf(stderr, "No image loaded: %s\n", IMG_GetError());
    //     return;
    // }
    
    // if (!imageTexture) {
    //     fprintf(stderr, "No image texture created: %s\n", SDL_GetError());
    //     SDL_FreeSurface(image);
    //     return;
    // }

    
    // download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    if (!font){
        fprintf(stderr, "No font loaded: %s\n", TTF_GetError());
        return;
    }

    // make textbox
    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface *text = TTF_RenderText_Solid(font, "Done", textColor); 
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text); 
    
    // draw rectangles
    SDL_Rect border = {0,0,1000, 800}; 
    SDL_Rect picture = {10, 10, 980, 780}; 
    SDL_Rect button = {450, 750, 100, 25};
    SDL_Rect textBox = {button.x + 25 , button.y + 4, 50, 20}; 
    
    bool runRecipe = true;

    while (runRecipe) {
        SDL_RenderClear(renderer);

        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowKeyboardGrab(window, SDL_TRUE);
        SDL_SetWindowMouseGrab(window, SDL_TRUE);
        SDL_SetWindowGrab(window, SDL_TRUE);
        
        // draw border
        SDL_SetRenderDrawColor(renderer, 197, 183, 124, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &border);

        // draw recipe
        SDL_SetRenderDrawColor(renderer, 189, 154, 122, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &picture);
    
        // render image and add picture on top
        SDL_RenderCopy(renderer, imageTexture, NULL, &picture); 
       
       // draw button
        SDL_SetRenderDrawColor(renderer, 178, 190, 181, SDL_ALPHA_OPAQUE); 
        SDL_RenderFillRect(renderer, &button); 

        // render button and add the text on top
        SDL_RenderCopy(renderer, textTexture, NULL, &textBox); 

        // display
        SDL_RenderPresent(renderer);
        SDL_Delay(100); 

        // handles events
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                runRecipe = false;
            } 

            // handling mouse click
            if (event.type == SDL_MOUSEBUTTONDOWN){
                // coordinates of where the click occured
                int x = event.button.x; 
                int y = event.button.y; 

                // if the click is inside the button
                if (x >= button.x && x <= (button.x + button.w) &&
                    y >= button.y && y <= (button.y + button.h)) {
                    runRecipe = false; 
                }
            }
        } 

    } // end of while loop

    SDL_DestroyTexture(imageTexture); 
    SDL_DestroyTexture(textTexture); 
    SDL_FreeSurface(text); 
    SDL_FreeSurface(image); 
    TTF_CloseFont(font); 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
} 


void checkGuess(char *name){


}

int main(int argc, char *argv[]){
    openRecipe(); 
}