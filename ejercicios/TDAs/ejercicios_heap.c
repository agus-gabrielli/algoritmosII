#include <string.h>

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 4(★★) En un heap de máximos ¿cuáles son las posibles posiciones del arreglo donde podría encontrarse el mínimo?
*/

/**
 * Respuesta. En el arreglo, desde n/2 hasta el final, porque el mínimo sí o sí es alguna de las hojas. Estaría mal decir
 * en el último nivel porque si el árbol no tiene su último nivel completo, algunas hojas estarían también en el ante-
 * último nivel. También estaría muy mal decir que está en la última posición. 
*/


/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 6(★★★) ¿Puede utilizarse un Heap para implementar el TDA cola (en el que se extraen los elementos en el orden 
 * en que fueron insertados)? ¿Y para implementar el TDA pila?
*/

/**
 * Respuesta. Sí, se puede. Para la cola tendrías un heap de mínimos donde lo que compares sea la cantidad de elementos
 * totales (que hay ahora y además los que fueron borrados) que había al momento de insertar ese elemento en la cola. Con lo cual
 * aquellos que entraron primero van a tener mayor prioridad que aquellos que entraron después. Es importante esto de tener
 * en cuenta no sólo la cantidad actual de elementos al momento de insertar sino tamb los borrados porque si no habría elementos
 * que tendrían igual prioridad. Para implementar esto, en el arreglo del heap meteríamos structs con miembros dato y prioridad,
 * y lo que usaríamos en las función de comparación es la prioridad. Además, en un miembro del tda deberíamos tener la cantidad
 * de elementos totales (cantidad actual + borrados) para asignar la prioridad al momento de encolar.
 * 
 * Con la pila sería algo similar, nada maś que más fácil: heap de máximos en donde la prioridad que le asignamos a cada elto
 * al momento de apilar es la cantidad actual de elementos. Como al desapilar siempre desapilamos el tope, no va a ser necesario
 * considerar a los borrados. 
 * 
 * Con esta implementación:
 * --desencolar es O(log n) porque el reemplazo al que le aplicamos downheap va a bajar sí o sí al fondo. 
 * --encolar es O(1) porque siempre meto al final y como tiene la peor prioridad es imposible que suba, se queda ahí en el fondo
 * al apilcarse upheap (si bien el encolar de un heap es O(log n), con esta info adicional es O(1)).
 * --desapilar es O(log n) pues siempre el reemplazante, con downheap, va a ir al fondo, igual que en desencolar
 * --apilar es O(log n) pues el que apilo es el más prioritario y al ponerlo al fondo y aplicarle upheap, sube hasta arriba 
 * de todo. 
 * En conclusión, no conviene implementar la pila y cola con heap. 
*/

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 8(★★★) Escribir una función en C que, dado un arreglo de n cadenas y un entero positivo k, devuelva una lista con 
 * las k cadenas más largas. Se espera que el orden del algoritmo sea O(n log k). Justificar el orden.
*/

/**
 * Respuesta. Lo que voy a hacer es creo un heap DE MÍNIMOS con los k primeros elementos. Luego, voy a ir recorriendo el resto
 * de los n elementos del arreglo y viendo si alguno es mayor al heap_ver_tope (el cual es el mínimo de los k máximos hasta el
 * momento). Cuando algún elemento es mayor que el tope del heap, desencolo ese y encolo el que es mayor. Así hasta terminar. 
 * Luego, me van a quedar los k elementos más grandes en el heap. Simplemente, voy desencolando y agregando a una lista.
 * 
 * Veamos el orden: voy a iterar por todos los elementos. En el peor de los casos, en cada paso voy a desencolar y desencolar 
 * del heap de mínimos. Esto sería O(n * 2log k). Finalmente, una vez que tengo los k elementos más grandes, voy desencolando
 * e insertando último en la lista, lo cual es O(k log k). El total queda O(n log k).
*/

int es_mas_corta_que(const char* cad1, const char* cad2){
    size_t largo_cad1 = strlen(cad1);
    size_t largo_cad2 = strlen(cad2);
    //return largo_cad1 > largo_cad2 ? 1 : (largo_cad1 < largo_cad2 ? -1 : 0); 
    return largo_cad1 < largo_cad2 ? 1 : (largo_cad1 > largo_cad2 ? -1 : 0); 
}
typedef int (*es_mas_corta_que_t)(const char*, const char*);

// Asumimos que k < n
lista_t* obtener_k_max(char** cadenas, size_t n, size_t k){
    heap_t* heap_minimos = heap_crear(es_mas_corta_que_t);
    if(! heap_minimos) return NULL;

    for(size_t i = 0; i < n; i++){
        if(i < k)
            heap_encolar(heap_minimos, cadenas[i]);
        else if(strlen(heap_ver_actual(heap_minimos)) < strlen(cadenas[i])){
            heap_desencolar(heap_minimos);
            heap_encolar(heap_minimos, cadenas[i]);
        }
    }

    lista_t* res = lista_crear();
    while(! heap_esta_vacio(heap_minimos)){
        lista_insertar_ultimo(res, heap_desencolar(heap_minimos));
    }
    heap_destruir(heap_minimos);

    return res;
}

