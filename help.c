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

void openHelp(SDL_Window *newWindow) {
    // Creates a new window and renderer 
    //SDL_Init(SDL_INIT_VIDEO);
    //SDL_Window *newWindow = SDL_CreateWindow("--help", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);

    //displays image 
    SDL_Surface *image = IMG_Load("images/Help.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(newRenderer, image);
    //SDL_FreeSurface(newLetter); 

    //download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    SDL_Delay(100); 

    // make textbox
    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface *text = TTF_RenderText_Solid(font, "Done", textColor); 
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(newRenderer, text); 
    text = NULL; 
    SDL_Delay(100);

    SDL_Rect button = {450, 650, 100, 25};
    SDL_Rect textBox = {button.x + 25 , button.y + 4, 50, 20}; 
    

    int helpOpen = 1; //true
    SDL_Event event;

    while (helpOpen) {  //to keep window open until user quits 
        SDL_SetWindowMouseGrab(newWindow, SDL_TRUE);
        SDL_SetWindowGrab(newWindow, SDL_TRUE);

        while (SDL_PollEvent(&event)) {
            // if the click is inside the button
            if (event.type == SDL_MOUSEBUTTONDOWN){
                int x = event.button.x; 
                int y = event.button.y;
            
                if (x >= button.x && x <= (button.x + button.w) &&
                    y >= button.y && y <= (button.y + button.h)) {
                    helpOpen = 0;
                    SDL_DestroyTexture(texture);
                    SDL_DestroyTexture(textTexture); 
                    textTexture = NULL; 
                    texture = NULL; 
                }

            }
        }

        SDL_RenderClear(newRenderer);
        SDL_RenderCopy(newRenderer, texture, NULL, NULL);
        // draw button
        SDL_SetRenderDrawColor(newRenderer, 178, 190, 181, SDL_ALPHA_OPAQUE); 
        SDL_RenderFillRect(newRenderer, &button); 
        // render button and add the text on top
        SDL_RenderCopy(newRenderer, textTexture, NULL, &textBox); 
        SDL_RenderPresent(newRenderer);
    }

    // Destory once user clicks out
    SDL_DestroyRenderer(newRenderer);
    newRenderer = NULL; 
    TTF_CloseFont(font); 
    
}

void help_commandline(){
	printf("App name : Secrets of Summerside\n");
	printf("Version number - 1.1.0\n");
	printf("Usage: TO START GAME.\n");
    printf("TYPE - make secrets \n");
    printf("NEXT TYPE -  ./secrets\n");
	printf("PRESS CONTINUE to reveal corkboard\n");
	printf("Click on each window to reveal clues, PRESS DONE to exit window\n");
	printf("Choose your suspect and CLICK GUESS to check your answer\n");
	printf("These instructions are also availble in the game. PRESS help button to view\n");
    printf("Read README.md file for more\n");

} 