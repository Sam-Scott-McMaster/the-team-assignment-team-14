secrets: main.c secrets.h recipe.c map.c checkguess.c
	gcc -o secrets main.c recipe.c letter.c map.c checkguess.c -lSDL2 -lSDL2_image -lSDL2_ttf

recipe: recipe.c
	gcc -o recipe recipe.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

guess: checkguess.c
	gcc -o guess checkguess.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

map: map.c
    gcc -o map map.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm