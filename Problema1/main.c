#include <stdio.h>
#include <stdlib.h>
#define TAM 1000

int main()
{
    int array1[TAM], array2[TAM], distancia = 0, similaridad = 0;

    // Parte 1
    leerArchivo(array1, array2);
    sortArray(array1);
    sortArray(array2);
    distancia = calcularDistancia(array1, array2);

    printf("Distancia: %i\n", distancia);


    // Parte 2

    similaridad = calcularSimilaridad(array1, array2);
    printf("Similaridad: %i", similaridad);
}

void leerArchivo(int * array1, int * array2){

    int i = 0;
    FILE * flectura = fopen("input.txt", "r");

    for (i = 0; i < TAM; i++){
        fscanf(flectura, "%i   ", array1+i);
        fscanf(flectura, "%i\n", array2+i);
    }

    fclose(flectura);
}

void sortArray(int * inputArray){

    int i, j, aux;

    for (i = 0; i < TAM - 1; i++) {
        aux = inputArray[i];

        for (j = 0; j < TAM - 1 - i; j++){
            if (inputArray[j] > inputArray[j+1]){
                aux = inputArray[j+1];
                inputArray[j+1] = inputArray[j];
                inputArray[j] = aux;
            }
        }
    }
}

int calcularDistancia(int * array1, int * array2){

    int i = 0, min = 0, max = 0, distanciaLocal = 0, distanciaTotal = 0;

    for(i = 0; i < TAM; i++){
        if (array1[i] < array2[i]){
            min = array1[i];
            max = array2[i];
        } else{
            min = array2[i];
            max = array1[i];
        }

        distanciaLocal = max - min;
        //printf("Distancia de %i a %i: %i\n", array1[i], array2[i], distanciaLocal);

        distanciaTotal += distanciaLocal;

        //printf("Distancia total actual: %i\n\n", distanciaTotal);
    }

    return distanciaTotal;
}

int calcularSimilaridad(int * array1, int * array2){
    int i = 0, j = 0, numeroVeces = 0, similaridad = 0;

    for (i = 0; i < TAM; i++){
        numeroVeces = 0;
        for (j = 0; j < TAM; j++){
            if (array1[i] == array2[j]) numeroVeces++;
        }
        similaridad += (array1[i] * numeroVeces);
        //printf("Numero de veces para el %i: %i\n", array1[i], numeroVeces);
        //printf("La similaridad tras la posicion %i es: %i\n\n", i, similaridad);
    }
    return similaridad;
}
