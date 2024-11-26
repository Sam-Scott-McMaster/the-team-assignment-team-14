secrets: main.c secrets.h recipe.c
	gcc -o secrets main.c recipe.c letter.c -lSDL2 -lSDL2_image