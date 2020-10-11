#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Pruebas unitarias del alumno

void prueba_crear_destruir(){
    printf("****Inicio de prueba crear y destruir pila****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo la pila", true);
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

void prueba_apilar_desapilar(){
    printf("****Inicio de prueba apilar y deapilar algunos elementos****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true);

    int num1, num2, num3, num4; //pruebo apilando puntero a enteros
    print_test("Se apila un puntero a entero", pila_apilar(pila, &num1));
    print_test("El tope es dicho puntero a entero", pila_ver_tope(pila) == &num1);
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    print_test("Al desapilar se devuelve el tope correspondiente", &num1 == pila_desapilar(pila));
    print_test("La pila ahora esta vacia", pila_esta_vacia(pila));
    print_test("Apilamos un puntero a entero", pila_apilar(pila, &num2));
    print_test("Apilamos otro puntero a entero", pila_apilar(pila, &num3));
    print_test("Apilamos otro puntero a entero", pila_apilar(pila, &num4));
    print_test("Verificamos que la pila no esta vacia", !pila_esta_vacia(pila));
    print_test("Desapilamos correctamente", &num4 == pila_desapilar(pila));
    print_test("Desapilamos correctamente", &num3 == pila_desapilar(pila));
    print_test("Desapilamos correctamente", &num2 == pila_desapilar(pila));
    print_test("La pila ahora esta vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

const size_t NUM_ELEMENTOS = 10000;
void prueba_volumen(){
    printf("****Inicio de prueba de volumen con %zu elementos****\n", NUM_ELEMENTOS);
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true);

    /*Como tengo que llenar la pila de punteros distintos, elijo apilar punteros que corresponden 
    a las posiciones de un arreglo de chars. Si se desea probar con un arreglo de otro tipo remplazar 
    sizeof(char) por sizeof(tipo).*/
    char* vector_volumen = malloc(NUM_ELEMENTOS * sizeof(char)); 
    size_t errores_apilar = 0;
    size_t errores_desapilar = 0;
    for(size_t i = 0; i < NUM_ELEMENTOS; i++){ 
        if(!pila_apilar(pila, vector_volumen + i * sizeof(char))) errores_apilar++;
        if(pila_ver_tope(pila) != vector_volumen + i * sizeof(char)) errores_apilar++;
    }
    print_test("Se apilaron todos los elementos", !errores_apilar); 
    void* elem_desapilado;
    //en el proximo for castie a int el NUM_ELEMENTOS pues size_t rompe en este ciclo en cuenta regresiva (por ser sin signo)
    for(int j = (int) NUM_ELEMENTOS -1; j >= 0; j--){ 
        elem_desapilado = pila_ver_tope(pila);
        if(elem_desapilado != pila_desapilar(pila)) errores_desapilar++;
        if(elem_desapilado != vector_volumen + j * sizeof(char)) errores_desapilar++;//chequeo que salen en el orden inverso a como los apile
    }
    print_test("Se desapilaron todos los elementos", !errores_desapilar); 
    printf("Se registraron %zu errores en la prueba\n", errores_apilar + errores_desapilar);
    pila_destruir(pila);
    free(vector_volumen);
    print_test("Se destruyo la pila", true);
}

void prueba_apilar_NULL(){
    printf("****Inicio de prueba de apilar elemento NULL****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true);
    print_test("Se apilo NULL", pila_apilar(pila, NULL));
    print_test("El tope es efectivamente NULL", !pila_ver_tope(pila));
    print_test("Se desapilo NULL", !pila_desapilar(pila));
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

void prueba_desapilar_hasta_vacia(){ //esto cubre las pruebas 5 y 8 que pide la catedra
    printf("****Inicio de prueba de desapilar hasta estar vacia****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true);
    short num1, num2, num3; //probamos apilando punteros a short para variar
    pila_apilar(pila, &num1);
    pila_apilar(pila, &num2);
    pila_apilar(pila, &num3);
    print_test("Se apilaron tres elementos", true);
    pila_desapilar(pila);
    pila_desapilar(pila);
    pila_desapilar(pila);
    print_test("Se desapilaron los tres elementos", true);
    printf("Comprobemos que la pila se comporta como si fuese recien creada:\n");
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    print_test("Desapilar es invalido (devuelve NULL)", !pila_desapilar(pila));
    print_test("Ver tope es invalido (devuelve NULL)", !pila_ver_tope(pila));
    print_test("La pila se comporta como si fuese recien creada", true);
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

void prueba_desapilar_vertope_cuando_creada(){
    printf("****Inicio de prueba de chequear que desapilar y vertope cuando recien creada una pila son invalidas****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true); 
    print_test("No se puede desapilar", !pila_desapilar(pila)); 
    print_test("No se puede ver tope", !pila_ver_tope(pila)); 
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

void prueba_esta_vacia_cuando_creada(){
    printf("****Inicio de prueba que una pila recien creada esta vacia****\n");
    pila_t* pila = pila_crear();
    print_test("Se creo una pila", true); 
    print_test("La pila esta vacia", pila_esta_vacia(pila)); 
    pila_destruir(pila);
    print_test("Se destruyo la pila", true);
}

void pruebas_pila_alumno() {
    
    prueba_crear_destruir();
    prueba_apilar_desapilar();
    prueba_volumen();
    prueba_apilar_NULL();
    prueba_desapilar_hasta_vacia();
    prueba_desapilar_vertope_cuando_creada();
    prueba_esta_vacia_cuando_creada();
    printf("---Finalizaron las pruebas del alumno---\n");
}