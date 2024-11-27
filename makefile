secrets: main.c secrets.h recipe.c
	gcc -o secrets main.c recipe.c letter.c -lSDL2 -lSDL2_image

recipe: recipe.c
	gcc -o recipe recipe.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

guess: checkguess.c
	gcc -o guess checkguess.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm
