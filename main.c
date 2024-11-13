// Purpose: Secrets of Summerside.
// Author: Tharny Elilvannan, McMaster University
// Last Updated: Wednesday, November 13, 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
// #include <SDL3/SDL_image.h>
#include "secrets.h"

// exit code 1: error while initializing

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVENTS) == 1) {

        fprintf(stderr, "%s\n", SDL_GetError());
        exit(1);

    } // end of if statement

    SDL_Window* window = SDL_CreateWindow("SECRETS OF SUMMERSIDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_FULLSCREEN);

    while (true) {

    } // end of while loop

} // end of main function