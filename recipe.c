/* Meigan Rogers
 * This function will "enlarge" one of the clues that the user clicks on
 * Focuses on the recipe clue
 * on mac before executing and compiling: export DYLD_FRAMEWORK_PATH=/Library/Frameworks
 * 
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


void openRecipe(SDL_Window* recipeWindow) {
    
    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(recipeWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event; // initialize events
    SDL_Delay(100); 
    
    // make image
    SDL_Surface * image = IMG_Load("images/recipe.png"); 
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    //puts("Freeing image surface"); 
    //SDL_FreeSurface(image); 
    image = NULL; 
    SDL_Delay(100); 

    //download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    SDL_Delay(100); 

    // make textbox
    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface *text = TTF_RenderText_Solid(font, "Done", textColor); 
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text); 
    //puts("Freeing surface"); 
    //SDL_FreeSurface(text); 
    text = NULL; 
    SDL_Delay(100); 

    // draw rectangles
    SDL_Rect border = {0,0,1000, 800}; 
    SDL_Rect picture = {10, 10, 980, 780}; 
    SDL_Rect button = {450, 750, 100, 25};
    SDL_Rect textBox = {button.x + 25 , button.y + 4, 50, 20}; 
    
    bool runRecipe = true;
    SDL_Delay(100); 

    while (runRecipe) {

        SDL_SetWindowMouseGrab(recipeWindow, SDL_TRUE);
        SDL_SetWindowGrab(recipeWindow, SDL_TRUE);

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

            // handling mouse click
            if (event.type == SDL_MOUSEBUTTONDOWN){
                // coordinates of where the click occured
                int x = event.button.x; 
                int y = event.button.y; 

                // if the click is inside the button
                if (x >= button.x && x <= (button.x + button.w) &&
                    y >= button.y && y <= (button.y + button.h)) {
                    runRecipe = false;
                    SDL_DestroyTexture(imageTexture);
                    SDL_DestroyTexture(textTexture); 
                    textTexture = NULL; 
                    imageTexture = NULL; 
                }
            }
            SDL_Delay(100); 
        } 

    }

    SDL_Delay(100); 
    SDL_DestroyRenderer(renderer);
    renderer = NULL; 
    SDL_Delay(100); 
    TTF_CloseFont(font); 
} 