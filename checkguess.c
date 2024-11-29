/* 
 * 
 * This function will check the user's guess (if it's correct or not)
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

    // create window and renderer
    SDL_Window* window = SDL_CreateWindow("Guess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event; // initialize events

    if (renderer == NULL) {
        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);

    } // end of if statement
    
    // download font
    TTF_Font *font = TTF_OpenFont("Dosis/static/Dosis-ExtraBold.ttf", 24); 
    if (!font){
        fprintf(stderr, "No font loaded: %s\n", TTF_GetError());
        return;
    }

    // make textboxes
    SDL_Color textColor = {0, 0, 0}; 

    // Create "Who is the murderer?" title
    SDL_Surface *title = TTF_RenderText_Solid(font, "Who is the murderer?", textColor); 
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, title);

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
    SDL_Rect titleRect = {150, 20, 300, 40};


    // draw buttons for each person
    SDL_Rect shaunButton = {450, 150, 100, 40};
    SDL_Rect shaunText = {shaunButton.x + 25 , shaunButton.y + 8, 50, 20}; 

    SDL_Rect glenButton = {250, 150, 100, 40};
    SDL_Rect glenText = {glenButton.x + 25 , glenButton.y + 8, 50, 20}; 

    SDL_Rect claytonButton = {50, 150, 100, 40};
    SDL_Rect claytonText = {claytonButton.x + 25 , claytonButton.y + 8, 50, 20}; 
    
    bool run = true;

    // Declare attempts variable
    int attempts = 0;


    while (run) {
        SDL_RenderClear(renderer);

        SDL_SetWindowMouseGrab(window, SDL_FALSE);
        SDL_SetWindowGrab(window, SDL_FALSE);
        
        // draw border
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &border);

        // draw background
        SDL_SetRenderDrawColor(renderer, 240, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &background);

        // Draw the "Who is the murderer?" text at the top
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);  
       
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
        
         // Display attempts
        char attemptsText[50];
        sprintf(attemptsText, "Attempts: %d", attempts);

        // Free any previously created surface/texture and create new ones
        SDL_Surface *attemptsSurface = TTF_RenderText_Solid(font, attemptsText, textColor);
        SDL_Texture *attemptsTexture = SDL_CreateTextureFromSurface(renderer, attemptsSurface);
        SDL_Rect attemptsRect = {250, 100, 100, 40}; // Position above buttons
        SDL_RenderCopy(renderer, attemptsTexture, NULL, &attemptsRect);


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
                    attempts++; 
                }

                if (x >= glenButton.x && x <= (glenButton.x + glenButton.w) &&
                    y >= glenButton.y && y <= (glenButton.y + glenButton.h)) {
                    printf("Glen\n");  
                    // User guessed correctly! Display a winning message
                    SDL_Surface *winMessage = TTF_RenderText_Solid(font, "You Win! Glen is the murderer!", textColor);
                    SDL_Texture *winTexture = SDL_CreateTextureFromSurface(renderer, winMessage);
                    SDL_Rect winRect = {150, 200, 300, 40};
                    SDL_RenderCopy(renderer, winTexture, NULL, &winRect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000); // Display the message for a few seconds
                    run = false; // Exit the game loop
                }

                if (x >= claytonButton.x && x <= (claytonButton.x + claytonButton.w) &&
                    y >= claytonButton.y && y <= (claytonButton.y + claytonButton.h)) {
                    printf("Clayton\n");  
                    attempts++;
                }
                // If attempts exceed 2, display the game over message
                if (attempts >= 2) {
                    SDL_Surface *gameOver = TTF_RenderText_Solid(font, "You've exhausted your number of tries!", textColor);
                    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOver);
                    SDL_Rect gameOverRect = {150, 200, 300, 40};
                    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(5000); // Delay to let the user see the message
                    run = false; // Exit the game loop
                }
            }
        } 

    } // end of while loop

    SDL_DestroyTexture(shaunTexture); 
    SDL_DestroyTexture(glenTexture);
    SDL_DestroyTexture(claytonTexture);
    TTF_CloseFont(font); 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    renderer = NULL; 
} 

