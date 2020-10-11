#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo{
    void* dato; 
    struct nodo* prox;
} nodo_t;

struct lista{
    nodo_t* prim;
    nodo_t* ult;
    int largo;
};

struct lista_iter{
    nodo_t* act; //actual
    nodo_t* ant; //anterior 
    lista_t* lista;
};

//FUNCIÓN AUXILIAR
nodo_t* crear_nodo(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;

    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

//PRIMITIVAS LISTA

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
    return lista->prim == NULL && lista->ult == NULL; //ó largo == 0
}

bool lista_insertar_primero(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if(!nodo) return false;

    if(lista_esta_vacia(lista)) lista->ult = nodo;
    else nodo->prox = lista->prim;

    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if(!nodo) return false;

    if(lista_esta_vacia(lista)) lista->prim = nodo;
    else lista->ult->prox = nodo;

    lista->ult = nodo;
    lista->largo++;
    return true;    
}

void* lista_borrar_primero(lista_t* lista){
    if(lista_esta_vacia(lista)) return NULL;
    nodo_t* nodo_a_eliminar = lista->prim;
    void* dato = nodo_a_eliminar->dato;
    lista->prim = nodo_a_eliminar->prox;
    if(!nodo_a_eliminar->prox) lista->ult = NULL;
    free(nodo_a_eliminar);
    lista->largo--;
    return dato;
}

void* lista_ver_primero(const lista_t* lista){
    if(lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato; 
}

void* lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato; 
}

size_t lista_largo(const lista_t* lista){
    return lista->largo;
}

void lista_destruir(lista_t* lista, void (*destruir_dato)(void*)){
    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato) destruir_dato(dato);
    }
    free(lista);
}

/*---------------PRIMITIVA ITERADOR INTERNO---------------*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* act = lista->prim;
    while(act && visitar(act->dato, extra)){
        act = act->prox;
    }
}

/*---------------PRIMITIVAS ITERADOR EXTERNO---------------*/
lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(!iter) return NULL;

    iter->act = lista->prim;
    iter->ant = NULL;
    iter->lista = lista;
    return iter;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return !iter->act;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)) return false;

    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(lista_iter_al_final(iter)) return NULL;
    return iter->act->dato; 
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* nodo = crear_nodo(dato);
    if(!nodo) return false;

    if(iter->ant) iter->ant->prox = nodo; 
    else iter->lista->prim = nodo; //caso borde: insertar al principio
    if(lista_iter_al_final(iter)) iter->lista->ult = nodo; //caso borde: insertar al final
    nodo->prox = iter->act;
    iter->act = nodo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)) return NULL;
    void* dato = iter->act->dato;
 
    nodo_t* a_eliminar = iter->act;
    iter->act = iter->act->prox;
    free(a_eliminar);
    if(iter->ant) iter->ant->prox = iter->act; 
    else iter->lista->prim = iter->act; //caso borde: borrar al principio
    if(lista_iter_al_final(iter)) iter->lista->ult = iter->ant; //caso borde: borrar al final
    iter->lista->largo--;
    return dato;
}