secrets: main.c secrets.h recipe.c map.c checkguess.c help.c
	gcc -o secrets main.c recipe.c letter.c map.c checkguess.c help.c -lSDL2 -lSDL2_image -lSDL2_ttf

recipe: recipe.c
	gcc -o recipe recipe.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

guess: checkguess.c
	gcc -o guess checkguess.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

map: map.c
	gcc -o map map.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm

letter:
	gcc -o letter letter.c -lSDL2 -lSDL2_image -lSDL2_ttf 

test: 
	gcc -o test letter-test.c recipe-test.c map-test.c test-secrets.c -lSDL2 -lSDL2_image -lSDL2_ttf