#include <stdio.h>
#include <stdbool.h>
#include "hash.h"
#include <stdlib.h>

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 5(★★) Implementar una función de orden O(n) que dado un arreglo de n números enteros devuelva true o 
 * false según si existe algún elemento que aparezca más de la mitad de las veces.
*/
bool mas_de_mitad(int* numeros, size_t largo){
    hash_t* apariciones = hash_crear(NULL);
    if(! apariciones) return false;

    size_t veces = 0;

    /**
     * Hay que hacer la aclaración de que mis datos del hash son size_t (y no hay problema, si bien
     * nosotros implementamos el hash con datos como punteros y no andaría, para no complicarla podemos hacer eso).
    */

    for(size_t i = 0; i < largo; i++){
        veces = 1;
        if(! hash_pertenece(apariciones, numeros[i]))
            hash_guardar(apariciones, numeros[i], veces); 
        else{
            veces = hash_obtener(apariciones, numeros[i]);
            hash_guardar(apariciones, numeros[i], ++veces);
        }
        if(veces > largo / 2){
            hash_destruir(apariciones);
            return true;
        }
    }
    
    hash_destruir(apariciones);
    return false;
}

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 6(★★) Se desea implementar una función que decida si dos Hash dados representan o no el mismo Diccionario. 
 * Considere para la solución que es de interés la mejor eficiencia temporal posible. 
 * Indique, para su solución, eficiencia en tiempo y espacio. Nota: Dos tablas de hash representan 
 * el mismo diccionario si tienen la misma cantidad de elementos; todas las claves del primero 
 * están en el segundo; todas las del segundo, en el primero; y los datos asociados a cada una 
 * de esas claves son iguales (se pueden comparar los valores con “==”).
*/

bool diccionarios_iguales(const hash_t* hash1, const hash_t* hash2){
    if(hash_cantidad(hash1) != hash_cantidad(hash2))
        return false;

    hash_iter_t* iter_hash1 = hash_iter_crear(hash1);
    if(! iter_hash1) return false; 
    /** Iteramos sólo uno de ellos y vemos que todos los eltos estén incluidos en el otro y con datos iguales. Al tener
     *igual cantidad, eso ya basta.
    */
   char* clave_act;
    while(! hash_iter_al_final(iter_hash1)){
        clave_act = hash_iter_ver_actual(iter_hash1);
        if(! hash_obtener(hash2, clave_act) && hash_obtener(hash2, clave_act) != hash_obtener(hash1, clave_act)){
            hash_iter_destruir(iter_hash1);
            return false;
        }            
    }
    hash_iter_destruir(iter_hash1);
    return true;
}

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 14(★★★) Supongamos que queremos crear una estructura Diccionario inmutable. Dicho TDA es un Diccionario 
 * que no será modificado. No tendrá altas, ni bajas. Los elementos se los pasan al crearlo 
 * (por ejemplo, a través de otra implementación de diccionario, o con un par de arreglos con las claves y valores). 
 * Explicar cómo harías para implementar esto de forma eficiente, considerando que su mayor utilidad es 
 * realizar búsquedas lo más rápido posible.
*/

/**
 * Respuesta --> implementaría un Hash & Displace. Ya sabemos que éste tiene la precondición de que ya debemos saber
 * las claves con antelación, y eso es justo lo que pasa acá. Hash & Displace tiene el beneficio enorme de que no usa 
 * espacio de más, si son n claves, crea la tabla de n claves y listo, usa el espacio justo. Además, siempre buscar por la 
 * tabla es O(1) y eso no se debería degenerar nada, como si puede pasar con otros tipos de hashing.
*/

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 16(★★★★★) Se quiere implementar un TDA Diccionario con las siguientes primitivas: obtener(x) devuelve el 
 * valor de x en el diccionario; insertar(x, y) inserta en el diccionario la clave x con el valor y (entero); 
 * borrar(x) borra la entrada de x; add(x, n) le suma n al contenido de x; add_all(m) le suma m a todos los valores. 
 * Proponer una implementación donde todas las operaciones sean \mathcal{O}(1)O(1). Justificar el orden de las operaciones.
*/

// Los datos del hash van a tener enteros (esto no compila por como está implementado este hash, cuyos datos son void*)
typedef struct diccionario_alternativo{
    hash_t* hash; 
    int add_all_acumulado;
} dic_alt_t;

dic_alt_t* crear_dic_alt(funcion_destruccion_t* destruir){
    dic_alt_t* dic = malloc(sizeof(dic_alt_t));
    if(! dic) return NULL;

    dic->hash = hash_crear(destruir);
    if(! dic->hash){
        free(dic);
        return NULL;
    } 

    dic->add_all_acumulado = 0;
    return dic;
}

bool dic_alt_insertar(dic_alt_t* dic, char* clave, int dato){
    return hash_guardar(dic->hash, clave, dato - dic->add_all_acumulado); 
    /**
     * Guardamos pero RESTANDO EL ADD_ALL_ACUMULADO de ese momento para que cuando obtengamos el valor, no se sume eso que ya
     * estaba antes
     */
}

int dic_alt_obtener(dic_alt_t* dic, char* clave){
    return hash_obtener(dic->hash, clave) + dic->add_all_acumulado;
}

int dic_alt_borrar(dic_alt_t* dic, char* clave){
    return hash_borrar(dic->hash, clave) + dic->add_all_acumulado;
}

bool dic_alt_add(dic_alt_t* dic, char* clave, int valor){
    return hash_guardar(dic->hash, clave, hash_obtener(dic->hash, clave) + valor);
}

void dic_alt_add_all(dic_alt_t* dic, int valor){
    dic->add_all_acumulado += valor;
}