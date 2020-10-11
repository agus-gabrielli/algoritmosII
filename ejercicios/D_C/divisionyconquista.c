#include <stdbool.h>
#include <stdio.h>

/*...........................................................................................*/

//ejercicio resuelto
/*Implementar un algoritmo en C que reciba un arreglo de enteros de tamaño n, 
ordenado ascendentemente y sin elementos repetidos, y determine en O(logn) si es mágico. 
Un arreglo es mágico si existe algún valor i tal que 0 <= i < n y arr[i] = i*/

bool _es_magico(int* vector, int n, int indice){
    if(n == 1) return vector[indice] == indice;

    int mitad = n/2;
    if(vector[indice] > indice){
        return false;
    } else if(vector[indice] < indice){
        return _es_magico(vector + mitad+1, mitad, mitad/2);
    } else{
        return true; //si vector[indice] == indice
    }
}

bool es_magico(int* vector, int n){ //wrap
    return _es_magico(vector, n, n/2);
}

/*...........................................................................................*/

/* Implementar, por división y conquista, una función que dado un arreglo y su largo, 
determine si el mismo se encuentra ordenado. Indicar y justificar el orden.*/

bool esta_ordenado(int arreglo[], size_t ini, size_t fin){
    if(ini==fin) return true;

    size_t medio = (ini + fin) / 2;    
    bool izquierda_esta_ordenada = esta_ordenado(arreglo, ini, medio);
    bool derecha_esta_ordenada = esta_ordenado(arreglo, medio+1, fin);
    bool ordenado_total = arreglo[medio] < arreglo[medio+1];

    return izquierda_esta_ordenada && derecha_esta_ordenada && ordenado_total;
}

/*...........................................................................................*/

//Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, unos seguidos de ceros). Se pide
//una función de orden logn que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.

//Es muy parecido a búsqueda binaria, hay que ir descartando mitades

size_t _pos_primer_cero(int arreglo[], size_t ini, size_t fin){
    if(ini == fin && arreglo[ini] == 0) return 0; //si se cruzan los índices significa que no encontramos un 0 en todo el arreglo

    size_t medio = (ini + fin) / 2;
    if(arreglo[medio] == 1 && arreglo[medio+1] == 0) return medio+1;
    if(arreglo[medio] == 0) return _pos_primer_cero(arreglo, ini, medio-1);
    if(arreglo[medio] == 1) return _pos_primer_cero(arreglo, medio+1, fin);
}

int pos_primer_cero(int arreglo[], size_t n){
    if(arreglo[n-1] == 1) return -1;
    return _pos_primer_cero(arreglo, 0, n-1);
}

/*...........................................................................................*/

//Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de 
//la raíz cuadrada de un número n, en tiempo O(logn). 
//Por ejemplo, para n = 10 debe devolver 3, y para n = 25 debe devolver 5.

//De vuelta, el algo. debe ser similar a busqueda binaria porque es O(logn). Si fuese O(nlogn) habría que pensar 
//similar a mergesort o quicksort, etc. 

int _parte_entera_raiz(int n, size_t ini, size_t fin){
    if(ini > fin) return (ini+fin)/2;

    size_t medio = (ini+fin)/2;
    if(medio*medio == n) return medio;
    if(medio*medio > n) return _parte_entera_raiz(n, ini, medio-1);
    if(medio*medio < n) return _parte_entera_raiz(n, medio+1, fin);
}

int parte_entera_raiz(int n){
    _parte_entera_raiz(n, 1, n);
}

/*...........................................................................................*/

//Implementar, por división y conquista, una función que dado un arreglo sin elementos repetidos 
//y casi ordenado (todos los elementos se encuentran ordenados, salvo uno), obtenga el elemento fuera de lugar

size_t pos_oveja_negra(int arreglo[], size_t ini, size_t fin){
    if(ini == fin) return 0;

    size_t medio = (ini+fin) / 2;
    size_t pos_izq = pos_oveja_negra(arreglo, ini, medio);
    size_t pos_der = pos_oveja_negra(arreglo, medio+1, fin);
    if(arreglo[medio] > arreglo[medio+1]) return medio + pos_izq + pos_der;
    return pos_izq + pos_der;

}

/*...........................................................................................*/

int main(){
    //ej resuelto:
    //int vector[] = {-3,-2,1,3,5,6,8,9};
    //printf("%d\n", es_magico(vector, sizeof(vector)));

    //ej 9:
    //int vector[] = {1,3,4,6,5,10,20,21};
    //printf("esta ordenado %d\n", esta_ordenado(vector, 0, 7));

    //ej 11:
    //int vector[] = {1,1,1,1,1,1,1,1,0,0};
    //printf("resultado %d\n", pos_primer_cero(vector, 10));

    //ej 12:
    //printf("el resultado es %d\n", parte_entera_raiz(15230));
    
    //ej 10:
    int vector[] = {1,2,3,5,4,6,7,8};
    printf("la posicion es %zd\n", pos_oveja_negra(vector, 0, 9));
    
    return 0;
}