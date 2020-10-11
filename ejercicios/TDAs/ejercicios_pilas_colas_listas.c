#include <stdbool.h>
#include <stdio.h>
#include "pila.h"
#include "lista.h"

/*...........................................................................................*/

//12) Implementar una función que ordene de manera ascendente una pila de enteros sin conocer su 
//estructura interna y utilizando como estructura auxiliar sólo otra pila auxiliar. 
//Por ejemplo, la pila [ 4, 1, 5, 2, 3 ] debe quedar como [ 1, 2, 3, 4, 5 ] 
//(siendo el último elemento el tope de la pila, en ambos casos). Indicar y justificar el orden de la función.

void ordenar_ascendente(pila_t* pila){
    pila_t* pila_aux = pila_crear();
    //la pila auxiliar tiene como invariante que está ordenada descendentemente

    int* tope_original;
    size_t contador;
    while(!pila_esta_vacia(pila)){
        tope_original = pila_desapilar(pila);
        contador = 0;
        while(!pila_esta_vacia(pila_aux) && *(int*)tope_original > *(int*)pila_ver_tope(pila_aux)){
            pila_apilar(pila, pila_desapilar(pila_aux));
            contador++;
        }
        pila_apilar(pila_aux, tope_original);
        for(int i=0; i<contador; i++) pila_apilar(pila_aux, pila_desapilar(pila));
    }
    while(!pila_esta_vacia(pila_aux)) pila_apilar(pila, pila_desapilar(pila_aux));
    pila_destruir(pila_aux);
}
//la complejidad de este algo es O(n al 2)

void prueba_ej12(){
    int num1=1, num2=2, num3=3, num4=4, num5=5, num6=6;    
    pila_t* pila = pila_crear();
    pila_apilar(pila, &num4);
    pila_apilar(pila, &num1);
    pila_apilar(pila, &num3);
    pila_apilar(pila, &num5);
    pila_apilar(pila, &num2);
    pila_apilar(pila, &num6);

    ordenar_ascendente(pila);
    while(!pila_esta_vacia(pila)) printf("%d\n", *(int*)pila_desapilar(pila));
    pila_destruir(pila);
}

/*...........................................................................................*/

//14) Sabiendo que la firma del iterador interno de la lista enlazada es... Se tiene una lista en donde 
//todos los elementos son punteros a números enteros. Implementar la función visitar para que 
//calcule la suma de todos los números pares. Mostrar, además, una invocación completa a lista_iterar() 
//que haga uso del visitar implementado.

typedef struct comodin{
    size_t contador;
    int suma;
} comodin_t;

bool suma_pares(void* dato, void* extra){
    //el extra es un struct que tiene dos miembros: suma y contador

    if(0 == (((comodin_t*)extra)->contador ) % 2){ //cuando contador es par sumamos
        printf("estoy aqui\n");
        (((comodin_t*)extra)->suma ) += *(int*)dato;
    }
    printf("el contador es %zd\n", ((comodin_t*)extra)->contador);
    ((comodin_t*)extra)->contador ++;
    return true;
}

void llamado_a_iterador(){
    lista_t* lista = lista_crear();
    int num1=1, num2=2, num3=3, num4=4, num5=5;
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    lista_insertar_ultimo(lista, &num5);

    comodin_t* comoda = malloc(sizeof(comodin_t));
    comoda->contador = 0;
    comoda->suma = 0;

    lista_iterar(lista, suma_pares, comoda);
    printf("La suma es %d\n", comoda->suma);
    lista_destruir(lista, NULL);
    free(comoda);
}

/*...........................................................................................*/

//ej 5. TDA Comosición de funciones

typedef struct composicion {
    pila_t* funciones;
} composicion_t;

typedef double (*funcion_t)(double);

composicion_t* composicion_crear(){
    composicion_t* composicion = malloc(sizeof(composicion_t));
    if(!composicion) return NULL;

    composicion->funciones = pila_crear();
    if(! composicion->funciones){
        free(composicion);
        return NULL;
    }
    return composicion;
}

void composicion_destruir(composicion_t* composicion){
    pila_destruir(composicion->funciones);
    free(composicion);
}

bool composicion_agregar_funcion(composicion_t* composicion, funcion_t funcion){
    return pila_apilar(composicion->funciones, (void*)funcion);
}

double composicion_aplicar(composicion_t* composicion, double valor){
    double res = valor;
    while(! pila_esta_vacia(composicion->funciones)){
        res = ((funcion_t)pila_desapilar(composicion->funciones)) (res); //casteamos a funcion_t la funcion desapilada y se la aplicamos a res
    }
    return res;
}

/*...........................................................................................*/


int main(){
    //prueba_ej12();

    llamado_a_iterador();

    return 0;
}