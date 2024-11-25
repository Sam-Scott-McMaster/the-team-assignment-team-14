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


void openRecipe(SDL_Window *window, SDL_Renderer *renderer) {
    
    // SDL_Window* window = SDL_CreateWindow("Recipe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event; // initialize events

    // make image
    SDL_Surface *image = IMG_Load("images/recipe.png");
    if (!image) {
        fprintf(stderr, "No image loaded: %s\n", IMG_GetError());
        return;
    }
    
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    if (!imageTexture) {
        fprintf(stderr, "No image texture created: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        return;
    }


    // download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    if (!font){
        fprintf(stderr, "No font loaded: %s\n", TTF_GetError());
        return;
    }

    // make textbox
    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface *text = TTF_RenderText_Solid(font, "Done", textColor); 
    if (!text) {
        fprintf(stderr, "No text surface rendered: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        exit(EXIT_FAILURE);
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text); 
    if (!textTexture) {
        fprintf(stderr, "Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(text);
        TTF_CloseFont(font);
        return;
    }

    
    // draw rectangles
    SDL_Rect border = {0,0,1000, 800}; 
    SDL_Rect picture = {10, 10, 980, 780}; 
    SDL_Rect button = {450, 750, 100, 25};
    SDL_Rect textBox = {button.x + 25 , button.y + 4, 50, 20}; 
    
    bool runRecipe = true;

    while (runRecipe) {
        SDL_RenderClear(renderer);

        // SDL_SetWindowResizable(window, SDL_FALSE);
        // SDL_SetWindowKeyboardGrab(window, SDL_TRUE);
        // SDL_SetWindowMouseGrab(window, SDL_TRUE);
        // SDL_SetWindowGrab(window, SDL_TRUE);
        
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
    //SDL_RenderClear(renderer);
    //  SDL_DestroyWindow(window);
    //  SDL_DestroyRenderer(renderer);
    //  SDL_Quit();
    //  IMG_Quit();
} 


void checkGuess(char *name){


}

int main(int argc, char *argv[]){


    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    if (IMG_Init(IMG_INIT_PNG) == 0) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    // initialize text
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow("SECRETS OF SUMMERSIDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 1000, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;


    SDL_Surface *test = IMG_Load("images/Corkboard-Main.png");
    SDL_Texture *testTexture = SDL_CreateTextureFromSurface(renderer, test);


    if (renderer == NULL) {

        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement

    SDL_Rect border = {0, 0, 2000, 1000};
    SDL_Rect corkboard = {50, 50, 1900, 900};
    SDL_Rect button = {1000, 500, 100, 100};

    bool run = true;

    while (run) {

        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowKeyboardGrab(window, SDL_TRUE);
        SDL_SetWindowMouseGrab(window, SDL_TRUE);
        SDL_SetWindowGrab(window, SDL_TRUE);
        
        // draw border
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &border);

        // draw corkboard
        SDL_SetRenderDrawColor(renderer, 189, 154, 122, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &corkboard);

        // render test picture
        SDL_RenderCopy(renderer, testTexture, NULL, NULL);

        // Draw button
        SDL_SetRenderDrawColor(renderer, 150, 150, 255, SDL_ALPHA_OPAQUE); // Set color for the button
        SDL_RenderFillRect(renderer, &button);

        // display
        SDL_RenderPresent(renderer);
        SDL_Delay(100);

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                run = false;

            } // end of if statement

            // handling mouse click
            if (event.type == SDL_MOUSEBUTTONDOWN){
                // coordinates of where the click occured
                int x = event.button.x; 
                int y = event.button.y; 

                // if the click is inside the button
                if (x >= button.x && x <= (button.x + button.w) &&
                    y >= button.y && y <= (button.y + button.h)) {
                    SDL_Delay(100);
                    SDL_RenderClear(renderer);
                    openRecipe(window, renderer); 
                    SDL_RenderClear(renderer);
                }
            }

        } // end of while loop

    } // end of while loop

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    exit(EXIT_SUCCESS); 
}