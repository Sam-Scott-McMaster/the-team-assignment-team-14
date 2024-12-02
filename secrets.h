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

void Letter(SDL_Window *);
void openRecipe(SDL_Window *);
void openMap(SDL_Window *);
void checkguess();
void openHelp(SDL_Window *);
void help_commandline();