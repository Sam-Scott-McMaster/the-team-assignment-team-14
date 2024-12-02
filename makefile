secrets: main.c secrets.h recipe.c map.c checkguess.c help.c
	gcc -o secrets main.c recipe.c letter.c map.c checkguess.c help.c -lSDL2 -lSDL2_image -lSDL2_ttf

letter:
	gcc -o letter letter.c -lSDL2 -lSDL2_image -lSDL2_ttf 

test: 
	gcc -o test checkguess-test.c
testcoverage:
	gcc -o checkguess --coverage checkguess-test.c



all: main.c secrets.h recipe.c map.c checkguess.c help.c letter.c
	gcc -o all recipe.c main.c map.c checkguess.c letter.c  help.c `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -lm
