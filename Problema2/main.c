#include <stdio.h>
#include <stdlib.h>
#define REPTAM 1000 // Number of lines in the input file
#define LEVTAM 8 // Maximum number of integers per line

// The functions may not be as efficient as possible, but I made them as modular as I could to make it understandable.

void readFile(int [REPTAM][LEVTAM]);
int checkSafety(int [REPTAM][LEVTAM]);
int isLineSafe(int [REPTAM][LEVTAM], int);
int checkDampenedSafety(int [REPTAM][LEVTAM]);
int isDampenedLineSafe(int [REPTAM][LEVTAM], int);

int main()
{
    int array[REPTAM][LEVTAM] = {NULL};
    int safety = 0;

    // PART 1

    readFile(array);
    safety = checkSafety(array);
    printf("Safety: %i\n", safety); // 591 for my input file

    // PART 2

    safety = checkDampenedSafety(array);
    printf("Dampened safety: %i\n", safety); // 621 for my input file

    return 0;
}

void readFile(int array[REPTAM][LEVTAM]){
    int i = 0, j = 0, aux = 0;
    char aux2;
    FILE * fread = fopen("input.txt", "r");

    for (i = 0; i < REPTAM; i++){
        for (j = 0; j < LEVTAM; j++){
            fscanf(fread, "%i", &aux); // Assign to a temporary variable
            array[i][j] = aux;

            aux2 = fgetc(fread); // Get the space so that fscanf doesn't
            if (aux2 == '\n' || aux2 == EOF) break; // Check if we found the end of the line or the file
        }
    }

    fclose(fread);
}

int checkSafety(int array[REPTAM][LEVTAM]){
    int i = 0, safeLines = 0;

    for (i = 0; i < REPTAM; i++)
        safeLines += isLineSafe(array, i);

    return safeLines;
}

int isLineSafe(int array[REPTAM][LEVTAM], int currentRep){
    int i = 0, levelNumber = 0, diff = 0, isAscending, isDescending;

    isAscending = 1;
    isDescending = 1;

    // Determining the number of levels / elements each line has
    for (i = 0; i < LEVTAM; i++)
        if (array[currentRep][i] != NULL) levelNumber++;

    // Using said number to not iterate unnecessarily in this loop
    for (i = 0; i < levelNumber - 1; i++){
        diff = array[currentRep][i + 1] - array[currentRep][i];

        if (diff < 1 || diff > 3) isAscending = 0;
        if (-diff < 1 || -diff > 3) isDescending = 0;
    }

    if (isAscending || isDescending) return 1;
    else return 0;
}

int checkDampenedSafety(int array[REPTAM][LEVTAM]){
    int i = 0, safeLines = 0;

    for (i = 0; i < REPTAM; i++)
        safeLines += isDampenedLineSafe(array, i);

    return safeLines;
}

// Basically bruteforcing lol
int isDampenedLineSafe(int array[REPTAM][LEVTAM], int currentRep){
    if (isLineSafe(array, currentRep)) return 1; // Avoid unnecessary checks if the line is already safe

    int i = 0, j = 0, levelNumber = 0, diff = 0, isAscending, isDescending;

    // Determining the number of levels / elements each line has - Same as in isLineSafe()
    for (i = 0; i < LEVTAM; i++)
        if (array[currentRep][i] != NULL) levelNumber++;

    // Creating a new modified array of the same size, but we fill it with all levels except one for each iteration
    for (i = 0; i < levelNumber; i++){
        int modifiedReport[LEVTAM] = {NULL}, newLevelNumber = 0;

        for (j = 0; j < levelNumber; j++){
            if (j != i){
                modifiedReport[newLevelNumber] = array[currentRep][j]; // Copying the line to the new array but without a single level
                newLevelNumber++;
            }
        }

        // From here it's basically the same as in isLineSafe() but with one less iteration, accounting for the removed level
        isAscending = 1;
        isDescending = 1;

        for (j = 0; j < newLevelNumber - 1; j++){
            diff = modifiedReport[j + 1] - modifiedReport[j];

            if (diff < 1 || diff > 3) isAscending = 0;
            if (-diff < 1 || -diff > 3) isDescending = 0;
        }

        if (isAscending || isDescending) return 1;
    }

    return 0;
}
