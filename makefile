secrets: main.c secrets.h recipe.c map.c checkguess.c help.c letter.c 
	gcc -o secrets main.c recipe.c letter.c map.c checkguess.c help.c -lSDL2 -lSDL2_image -lSDL2_ttf

letter:
	gcc -o letter letter.c -lSDL2 -lSDL2_image -lSDL2_ttf 

test: 
	gcc -o test --coverage checkguess-test.c

