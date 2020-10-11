#include "pila.h"
#include <stdlib.h>
#define CAPACIDAD_INICIAL 20
#define FACTOR_REDIMENSION 2

struct pila {
    void** datos;
    size_t cantidad;  
    size_t capacidad;  
};

//Declaracion funcion auxiliar
bool redimensionar(pila_t* pila, size_t nueva_capacidad);

//PRIMITIVAS
pila_t* pila_crear(void){
    pila_t* p = malloc(sizeof(pila_t));
    if(p == NULL) return NULL;

    p->capacidad = CAPACIDAD_INICIAL;
    p->datos = malloc(p->capacidad * sizeof(void*));
    if(p->datos == NULL){
        free(p);
        return NULL;
    }
    p->cantidad = 0;
    return p;
}

void pila_destruir(pila_t* pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t* pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t* pila, void* valor){
    if(pila->cantidad == pila->capacidad){ 
        if(!redimensionar(pila, pila->capacidad*FACTOR_REDIMENSION)){ 
            return false;
        } 
    }    
    pila->datos[pila->cantidad++] = valor; 
    return true;
}

void* pila_ver_tope(const pila_t* pila){
    if(pila_esta_vacia(pila)) return NULL;

    return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t* pila){
    if(pila_esta_vacia(pila)) return NULL;

    void* valor_desapilado = pila_ver_tope(pila);
    pila->cantidad--;
    if(FACTOR_REDIMENSION*FACTOR_REDIMENSION*pila->cantidad == pila->capacidad && pila->capacidad > CAPACIDAD_INICIAL){
        redimensionar(pila, pila->capacidad/FACTOR_REDIMENSION); 
    }
    return valor_desapilado;
}

//FUNCION AUXILIAR
bool redimensionar(pila_t* pila, size_t nueva_capacidad){    
    void** auxiliar = realloc(pila->datos, nueva_capacidad * sizeof(void*));
    if(!auxiliar) return false; 

    pila->capacidad = nueva_capacidad;
    pila->datos = auxiliar;
    return true;
}