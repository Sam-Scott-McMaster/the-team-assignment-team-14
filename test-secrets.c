/*
 Purpose: Unit testing for Secrets of Summerside.
Author: Sachika Saxnea, McMaster University
 Last Updated: Wednesday, November 27, 2024
 This program uses the SDL and SDL_image libraries.
 This program unit tests every function and prints pass/fail messages accordingly
 Uses the test version of each function (example letter.c , this program uses test-letter.c)(see changes in test-letter.c file)

*/
#include <stdio.h>
#include <stdlib.h>
#include "secrets-test.h"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
/*
int test_Letter() {

    int result = Letter(); //calls return values 
    return result;  //return a value for testing purposes 
}
*/
int test_openRecipe(){
    int result = openRecipe();
    return result;

}

int test_openMap(){
    int result = openMap();
    return result;
}
int main() {
    //int letterResult = test_Letter();  //assign integer
    int recipeResult = test_openRecipe();
    int mapResult = test_openMap();
    /*if (letterResult == EXIT_SUCCESS) {  
        printf("Letter Function Passed Test\n"); //print success message if 0
    } else {
        printf("Letter Function Failed\n"); //prints fail message if 1
        exit(EXIT_FAILURE);
    } */

    if (recipeResult == EXIT_SUCCESS) {
        printf("Recipe Function Passed Test\n");
    } else {
        printf(" Recipe Function Failed\n");
        exit(EXIT_FAILURE);
    }
      if (mapResult == EXIT_SUCCESS) {
        printf("Map Function Passed Test\n");
    
    } else {
        printf("Letter Function Failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}