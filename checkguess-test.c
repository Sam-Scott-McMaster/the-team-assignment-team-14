#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void checkguess_logic(int argc, char* argv[]) {
    int attempts = 0;
    bool run = true;
    const char* murderer = "Glen";

    
    while (run && attempts < argc - 1) {  // loops through according to the number of guesses given
        const char* current_guess = argv[attempts + 1];  
        if (strcmp(current_guess, murderer) == 0) {
            printf("You Win! Glen is the murderer!\n");
            run = false;  // Exit the game loop 
        } else {
            attempts++;
            if (attempts < argc - 1) {  
                printf("Incorrect guess ");
            } else {  // No attempts left
                printf("Game Over! You've exhausted your number of tries.\n");
                run = false;  // End the game after the last attempt
            }
        }
    }
}

int main(int agrc, char *argv[]){
    checkguess_logic(agrc, argv);
    return 0;
}


