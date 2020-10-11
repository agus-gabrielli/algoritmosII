#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h> //para size_t

//La lista está planteada como una lista de punteros genéricos.
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t; 

/*---------------PRIMITIVAS LISTA---------------*/

//Crea una lista.
//Post: devuelve una lista vacía, de largo 0.
lista_t *lista_crear(void);

//Devuelve verdadero si la lista no tiene elementos, falso en caso contrario.
//Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

//Inserta un elemento con el dato al comienzo de la lista. Devuelve falso en caso de error.
//Pre: la lista fue creada. 
//Post: se agregó un elemento dato al comienzo de la lista. El largo de la lista aumenta en 1. 
bool lista_insertar_primero(lista_t *lista, void *dato);

//Inserta el dato al final de la lista. Devuelve falso en caso de error.
//Pre: la lista fue creada. 
//Post: se agregó un elemento dato al final de la lista. El largo de la lista aumenta en 1. 
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//Borra el primer elemento de la lista, devolviendo el mismo. Si la lista está vacía,
//devuelve NULL.
//Pre: la lista fue creada
//Post: se devolvió el dato del primer elemento anterior y el largo de la lista se reduce en 1, si no estaba vacía. 
void *lista_borrar_primero(lista_t *lista);

//Devuelve el dato del primer elemento de la lista. Si está vacía, devuelve NULL.
//Pre: la lista fue creada. 
//Post: se devolvió el dato del primer elemento, si la lista no estaba vacía.
void *lista_ver_primero(const lista_t *lista);

//Devuelve el dato del último elemento de la lista. Si está vacía, devuelve NULL.
//Pre: la lista fue creada. 
//Post: se devolvió el dato del último elemento, si la lista no estaba vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve la cantidad actual de elementos en la lista. 
//Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista se llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista. destruir_dato puede ser NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/*---------------PRIMITIVA ITERADOR INTERNO---------------*/

//Itera toda la lista aplicando la función visitar a cada dato. En cada elemento por el que pase analiza:
//si visitar devuelve true al aplicarse el dato, se sigue iterando. Si devuelve false, se para la iteración. 
//El extra puede usarse como una variable auxiliar, y debe coincidir con el segundo parámetro de visitar. 
//Pre: la lista fue creada y contiene al menos un elemento. 
//Post: se iteró por la lista aplicando la función visitar en los elementos que recorrió.  
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/*---------------PRIMITIVAS ITERADOR EXTERNO---------------*/
//NO se deben usar las primitivas de la lista que involucran insertar 
//o eliminar elementos mientras se esté usando el iterador externo. 

//Devuelve un iterador externo para la lista, NULL en caso de error. 
//Pre: la lista está creada y contiene al menos un elemento. 
lista_iter_t *lista_iter_crear(lista_t *lista);

//Avanza hacia el siguiente elemento devolviendo true, en caso de que todavía no haya llegado al final. 
//Si ya se había llegado al final de la lista, se devuelve false. 
//Pre: iter fue creado. 
//Post: se avanzó al siguiente, devolviendo true, o se devolvió false si lista_iter_al_final era true.
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve el dato del elemento sobre el cual está el iterador actualmente. Si el iterador
//está en el final, devuelve NULL.
//Pre: iter fue creado. 
//Post: se devolvió el dato, o NULL si lista_iter_al_final es true.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Devuelve true si el iterador llegó al final de la lista, es decir, 
//si anteriormente se avanzó luego del útlimo elemento de la lista. 
//Pre: iter fue creado. 
//Post: devolvió true en caso de haber llegado al final, false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

//Se destruye el iterador. 
//Pre: iter fue creado.
void lista_iter_destruir(lista_iter_t *iter);

//Se inserta un elemento con su dato en la posición de la lista donde está el iterador y devuelve true.
//Si ocurrió un error, devuelve false.  
//Pre: iter fue creado. 
//Post: se intertó un dato en la posición del iterador y devolvió true, aumentando en 1 el largo de la lista.
//Devolvió false si hubo error. 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Elimina el elemento sobre el cual estaba el iterador, devolviendo el dato que contenía, o
//devuelve NULL si lista_iter_al_final es true (si se llegó al final o está vacía).
//Pre: iter fue creado. 
//Post: Se eliminó el elemento sobre el cual estaba el iterador, devolviendo el dato que contenía y disminuyendo
//en 1 el largo de la lista, o se devuelve NULL si no se puedo borrar. 
void *lista_iter_borrar(lista_iter_t *iter);

/*---------------PRUEBAS ALUMNO---------------*/

// Realiza pruebas sobre la implementación del alumno.
void pruebas_lista_alumno();

#endif