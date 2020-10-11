#include "lista.h"
#include <string.h>
#include "hash.h"
/**
 * Padrón: 104954
 * Alumno: Agustín Gabrielli
 * Ejercicios: 1, 3a (postorder), 4 (hash abierto)
 * */

/**
 * -----------------------------------------------------------------------------------------------------------------------
 * Ejercicio 1
 * Decidir si las siguientes afirmaciones son verdaderas o falsas, y justificar.
 * 
 * a. Se puede implementar una primitiva que permita cambiar la función de prioridad de un Heap (y acomodar sus
 * elementos a la nueva función) en O(n).
 * 
 * b. Si desencolo en un TDA Heap (de máximos) cuyo arreglo interno comenzó como [10, 7, 5, 5, 6, 3, 4, 3, 2], el
 * estado resultante será [7, 5, 5, 3, 6, 3, 4, 2].
 * 
 * c. No siempre conviene implementar una Cola de Prioridad con un Heap.
*/

/**
 * Respuestas:
 * a) Sí, se puede. De hecho, lo que habría que hacer es, además de remplazar la función de prioridad vieja por la nueva,
 * se llama a heapify, el cual le dará forma de heap al arreglo teniendo en cuenta la nueva función. Como heapify es O(n) siendo
 * n la cantidad de elementos que hay en el heap, esta primitiva sería O(n). 
 * 
 * b) No, es falso. El seguimiento que hice está en papel (foto que pasé). El estado resultante es [7, 6, 5, 5, 2, 3, 4, 3].
 * Falló en el downheap del 2, al swappear el 2 con el 5 en lugar de con el 6. 
 * 
 * c) Verdadero. Supongamos que k es el número de prioridades que puede haber. Si k es bajo, es más eficiente implementar la 
 * cola de prioridades teniendo k colas distintas. Por ejemplo, si se encola un elemento con la prioridad más alta, por dentro
 * se encola en la cola de la prioridad más alta. Cuando se desencola, siempre se va a intentar desencolar de la cola con más
 * prioritaria, si está vacía sigue jerárquicamente con las demás. Como se dijo, si k es bajo (por ej. 2, 3, 4 etc.) todas las
 * operaciones son O(1) mientras que las del heap son O(log n), n la cantidad de elementos totales en la cola de prioridades. 
 * Ahora, si k es grande, o si por ej. sólo sabemos cuándo un elemento es más prioritario con otro comparándolos, ahí es donde el
 * heap es la mejor opción. 
*/

/**
 * -----------------------------------------------------------------------------------------------------------------------
 * Ejercicio 3A (Postorder)
 * Implementar una primitiva lista_t* ab_debajo_de(ab_t* ab, const char* clave) que reciba una clave y devuelva
 * todos los elementos debajo del nodo cuya clave es la indicada, en postorder. Indicar y 
 * justificar la complejidad del algoritmo implementado.
 */

typedef struct ab {
struct ab* izq;
struct ab* der;
char* clave;
} ab_t;

// Búsca la clave y devuelve el árbol cuya raíz la contiene.  
ab_t* obtener_subarbol(ab_t* ab, const char* clave){
    if(! ab) return NULL;

    if(strcmp(ab->clave, clave) == 0)
        return ab;
    obtener_subarbol(ab->izq, clave);
    obtener_subarbol(ab->der, clave);
    return NULL;
}

void _ab_debajo_de(ab_t* ab, lista_t* lista){
    if(! ab) return;

    _ab_debajo_de(ab_t* ab->izq, lista_t* lista);
    _ab_debajo_de(ab_t* ab->der, lista_t* lista);
    lista_insertar_ultimo(lista, ab->clave);
}

lista_t* ab_debajo_de(ab_t* ab, const char* clave){
    ab_t* subarbol = obtener_subarbol(ab, clave);
    if(! subarbol) return NULL;

    lista_t* resultado = lista_crear();
    if(! resultado) return NULL;

    _ab_debajo_de(subarbol, resultado);
    return resultado;
}

/**
 * Complejidad del algoritmo implementado: el mayor problema acá es que el árbol no es ABB, simplemente un AB con lo 
 * cual buscar una clave por un árbol de n elementos es O(n). Esto se ve en la función auxiliar obtener_subarbol. 
 * Lo que sigue a esa búsqueda es simplemente iterar post-order por ese subárbol e ir insertando en la lista (esto último es
 * O(1)), y esto, en el peor de los casos -que la clave que pasa Bárbara sea la raíz del ab- es O(n) también (obvio que
 * si se da este último caso, obtener_subarbol es O(1), pero luego iterar es O(n)). Entonces, el total es O(n).
*/

/**
 * -----------------------------------------------------------------------------------------------------------------------
 * Ejercicio 4 (Hash abierto).
 * Implementar una primitiva del Hash Abierto que permita obtener
 * una lista con las claves y valores existentes dentro del Hash. A fines del ejercicio, pueden suponer que en hash.h ya se
 * encuentra definida una estructura typedef struct {const char* clave; void* dato; } hash_par_t;, y la lista debe
 * ser de punteros a dicha estructura. Indicar y justificar la complejidad del algoritmo implementado.
*/

/**
 * Asumo que campo_hash_t es el struct que contiene a la clave y dato en las listas de cada posición de la tabla, que
 * es lo estándar en la implementación de hash abierto. Igual lo incluyo a continuación:
 * */
typedef struct campo_hash{
    char* clave;
    void* dato;
} campo_hash_t;

struct hash_par{ // Typedef en el .h
    const char* clave;
    void* dato;
}; 

hash_par_t* crear_par(campo_hash_t* campo){
    hash_par_t* par = malloc(sizeof(hash_par_t));
    if(! par) return NULL;

    par->clave = campo->clave;
    par->dato = campo->dato;

    return par;
}

lista_t* obtener_lista_pares(hash_t* hash){
    lista_t* resultado = lista_crear();
    if(! resultado) return NULL;

    for(size_t i = 0; i < hash->capacidad; i++){
        if(lista_esta_vacia(hash->tabla[i])) continue; // Asumo que hay listas en todas las posiciones del hash

        lista_iter_t* iter = lista_iter_crear(hash->tabla[i]);
        if(! iter){
            lista_destruir(resultado, free);
            return NULL;
        }

        while(! lista_iter_al_final(iter)){
            lista_insertar_ultimo(resultado, (void*)crear_par(lista_iter_ver_actual(iter)));
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }

    return resultado;
}

/**
 * Complejidad del algoritmo. Hay que pasar por todos los (supongamos n) pares clave-dato del hash, iterando
 * por la tabla y, en cada posición, iterando por la lista correspondiente. Como para cada uno de esos campos
 * hay que hacer operaciones O(1) (como crear el struct hash_par_t e insertarlo a la lista resultado), 
 * la complejidad total termina siendo O(n). 
*/