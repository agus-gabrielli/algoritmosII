#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "testing.h"
#include "pila.h"

void prueba_crear_destruir(){
    printf("Inicio de prueba crear y destruir cola\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_un_elemento(){
    printf("Inicio de prueba de encolar y desencolar un elemento\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    int num1; //pruebo encolando un puntero a entero
    print_test("    Se encola un puntero a entero", cola_encolar(cola, &num1));
    print_test("    El primero de la cola es dicho elemento", &num1 == cola_ver_primero(cola));
    print_test("    La cola no está vacía", !cola_esta_vacia(cola));
    print_test("    Se desencola y se devuelve el elemento", cola_desencolar(cola));
    print_test("    La cola está ahora vacía", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_encolar_desencolar_varios(){
    printf("Inicio de prueba de encolar y desencolar varios elementos\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    int num1, num2, num3, num4; 
    print_test("    Se encola un puntero a entero", cola_encolar(cola, &num1));
    print_test("    Se encola un segundo puntero a entero", cola_encolar(cola, &num2));
    print_test("    El primero es el que se encoló primero", &num1 == cola_ver_primero(cola));
    print_test("    La cola no esta vacía", !cola_esta_vacia(cola));
    print_test("    Se encola por tercera vez un puntero a entero", cola_encolar(cola, &num3));
    print_test("    Se encola un cuarto puntero a entero", cola_encolar(cola, &num4));

    print_test("    El primero sigue siendo el que se encoló primero", &num1 == cola_ver_primero(cola));
    print_test("    La cola no esta vacía", !cola_esta_vacia(cola));

    print_test("    Se desencola y se devuelve el primer encolado", cola_desencolar(cola) == &num1);
    print_test("    El primero es el correcto", cola_ver_primero(cola) == &num2);
    print_test("    La cola no está vacía, todavía quedan elementos", !cola_esta_vacia(cola));
    print_test("    Se desencola por segunda vez y se devuelve el segundo encolado", cola_desencolar(cola) == &num2);
    print_test("    Se desencola por tercera vez y se devuelve el tercer encolado", cola_desencolar(cola) == &num3);
    print_test("    Se desencola por cuarta vez y se devuelve el cuarto y último encolado", cola_desencolar(cola) == &num4);
    print_test("    La cola está vacía", cola_esta_vacia(cola));
    print_test("    Desencolar devuelve NULL", !cola_desencolar(cola));
    print_test("    Ver primero devuelve NULL", !cola_ver_primero(cola));
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_encolar_NULL(){
    printf("Inicio de prueba de encolar NULL\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    print_test("    Se crea la cola", true);
    print_test("    Se encola NULL", cola_encolar(cola, NULL));
    print_test("    El primero es NULL", !cola_ver_primero(cola));  
    print_test("    La cola no está vacía", !cola_esta_vacia(cola));
    print_test("    Se desencola y se devuelve NULL que estaba encolado", !cola_desencolar(cola)); 
    print_test("    La cola ahora está vacía", cola_esta_vacia(cola));      
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_vacia_cuando_creada(){
    printf("Inicio de prueba de comprobación de tener la cola vacía cuando creada\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    print_test("    La cola recién creada está vacía", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_desencolar_verprimero_cuando_creada(){
    printf("Inicio de prueba de desencolar y ver_primero cuando creada\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    print_test("    No se puede desencolar, devuelve NULL", !cola_desencolar(cola));
    print_test("    No se puede ver el primer elemento, devuelve NULL", !cola_ver_primero(cola));
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_desencolar_hasta_vacia(){ 
    printf("Inicio de prueba de desencolar hasta estar vacía\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    long num1, num2, num3; //probamos encolando punteros a long para variar
    print_test("    Se encola el primer elemento", cola_encolar(cola, &num1));
    print_test("    Se encola un segundo elemento", cola_encolar(cola, &num2));
    print_test("    Se encola un tercer elemento", cola_encolar(cola, &num3));
    print_test("    Se encolaron tres elementos", true);
    print_test("    Se desencola el primer elemento encolado", cola_desencolar(cola) ==&num1);
    print_test("    Se desencola el segundo elemento encolado", cola_desencolar(cola) ==&num2);
    print_test("    Se desencola el tercer elemento encolado", cola_desencolar(cola) ==&num3);
    print_test("    Se desencolaron los tres elementos", true);
    printf("    Comprobemos que la cola se comporta como si fuese recien creada:\n");
    print_test("    La cola está vacía", cola_esta_vacia(cola));
    print_test("    Desencolar es inválido (devuelve NULL)", !cola_desencolar(cola));
    print_test("    Ver primero es inválido (devuelve NULL)", !cola_ver_primero(cola));
    print_test("    La cola se comporta como si fuese recien creada", true);
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

const size_t NUM_ELEMENTOS = 10000;
void prueba_volumen(){
    printf("Inicio de prueba de volumen con %zu elementos\n", NUM_ELEMENTOS);
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    //encolamos punteros a chars (posiciones de un arreglo de chars)
    char* vector_volumen = malloc(NUM_ELEMENTOS * sizeof(char)); 
    size_t errores_encolar = 0;
    size_t errores_desencolar = 0;
    for(size_t i = 0; i < NUM_ELEMENTOS; i++){ 
        if(!cola_encolar(cola, vector_volumen + i * sizeof(char))) errores_encolar++;
    }
    print_test("    Se encolaron todos los elementos", !errores_encolar); 
    void* elem_desencolado;
    for(size_t j = 0; j < NUM_ELEMENTOS; j++){ 
        elem_desencolado = cola_ver_primero(cola);
        if(elem_desencolado != cola_desencolar(cola)) errores_desencolar++;
        if(elem_desencolado != vector_volumen + j * sizeof(char)) errores_desencolar++;//chequeo que salen en el orden a como los encolé
    }
    print_test("    Se desencolaron todos los elementos", !errores_desencolar); 
    print_test("    La cola está vacía", cola_esta_vacia(cola));
    printf("    Se registraron %zu errores en la prueba\n", errores_encolar + errores_desencolar);
    free(vector_volumen);
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola", true);
    printf("\n");
}

void prueba_destruccion_no_vacia_NULL(){
    printf("Inicio de prueba de destrucción de la cola estando no vacía y pasando NULL a destruir\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    int num1, num2, num3;
    print_test("    Se encola un puntero a entero", cola_encolar(cola, &num1));
    print_test("    Se encola un segundo puntero a entero", cola_encolar(cola, &num2));
    print_test("    Se encola un tercer puntero a entero", cola_encolar(cola, &num3));
    cola_destruir(cola, NULL);
    print_test("    Se destruye la cola pasando como argumento NULL", true);
    printf("\n");
}

void prueba_destruccion_vacia_funcion1(){
    printf("Inicio de prueba de destrucción de la cola estando vacía y pasando free como función\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    print_test("    La cola está vacía", cola_esta_vacia(cola));
    cola_destruir(cola, free);
    print_test("    Se destruye la cola pasando como argumento free", true);
    printf("\n");
}

void prueba_destruir_funcion1(){
    printf("Inicio de prueba de destruir cola pasando la funcion free como argumento\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    void* dato;
    for(int i = 0; i < 5; i++){
        dato = malloc(sizeof(void*));
        cola_encolar(cola, dato);
    }
    print_test("    Se encolaron algunos punteros genéricos", true);
    print_test("    Se destruye la cola pasando la funcion free", true);
    cola_destruir(cola, free);
    printf("\n");
}

/*Tuve que crear esta funcion pues la funcion pila_destruir 
no recibe un void* y sino un pila_t**/
void eliminar_pila(void* pila){ 
    pila_destruir(pila);
    print_test("        Se destruye la pila", true);
}

void prueba_destruir_funcion2(){
    printf("Inicio de prueba de destruir cola pasando la funcion eliminar_pila como argumento\n");
    cola_t* cola = cola_crear();
    print_test("    Se crea la cola", true);
    pila_t* pila;
    for(int i = 0; i < 5; i++){
        pila = pila_crear();
        cola_encolar(cola, pila); //encolamos distintas pilas
    }
    print_test("    Se encolaron algunas pilas", true);
    print_test("    Se destruye la cola pasando la funcion eliminar_pila", true);
    cola_destruir(cola, eliminar_pila);
    printf("\n");
}

/*-----------------------------*/

void pruebas_cola_alumno(void){
    prueba_crear_destruir();
    prueba_un_elemento();
    prueba_encolar_desencolar_varios();
    prueba_encolar_NULL();
    prueba_vacia_cuando_creada();
    prueba_desencolar_verprimero_cuando_creada();
    prueba_desencolar_hasta_vacia();
    prueba_volumen();
    prueba_destruccion_no_vacia_NULL();
    prueba_destruccion_vacia_funcion1();
    prueba_destruir_funcion1();
    prueba_destruir_funcion2();

    printf("Fin de las pruebas del alumno.\n");
}