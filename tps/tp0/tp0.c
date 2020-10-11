#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap (int *x, int *y) {
    int contenido_x = *x;  
    *x = *y;
    *y = contenido_x;
}


int maximo(int vector[], int n) {
    if(n == 0){ 
        return -1;
    }

    int posicion_maximo = 0;
    for(int i = 1; i < n; i++){
        if(vector[i] > vector[posicion_maximo]){
            posicion_maximo = i;
        }
    }
    return posicion_maximo;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    for(int i = 0; i < n1 && i < n2; i++){
        if(vector1[i] < vector2[i]){
            return -1;
        if(vector2[i] < vector1[i]){
            return 1;
        }
    }
    if(n1 < n2){
        return -1;
    } 
    if(n2 < n1){
        return 1;
    }
    return 0; //si son iguales en tamaño y elemento a elemento
}


void seleccion(int vector[], int n) {
    /*seleccionamos los máximos y los mandamos al final*/
    int* dir_max_actual;
    for(int i = 1; i < n; i++){
        dir_max_actual = &vector[maximo(vector, n-i+1)]; 
        swap(dir_max_actual, &vector[n-i]);
    }
}
