#ifndef TP1LIB_H
#define TP1LIB_H

#include <stdbool.h>
#include "pila.h"

typedef struct operador operador_t;

//Crea y devuelve el operador según el token que se le pase. Como precondición, el token 
//debe ser "+", "-", "*", "/", "^", "(" ó ")". Devuelve Null en caso de error. 
operador_t* crear_operador(char* token);

void destruir_operador(operador_t* op);

void liberar_simbolo(operador_t* op);

char* obtener_simbolo(operador_t* op);

bool operadores_iguales(operador_t* op1, char* token);

bool mayor_precedencia(operador_t* op1, operador_t* op2);

bool igual_precedencia(operador_t* op1, operador_t* op2);

bool es_asoc_izq(operador_t* op);

//OTRAs FUNCIONES DE UTILIDAD

//Pasa un operador de la pila de operadores al arreglo de salida. 
void de_pila_a_salida(pila_t* pila, char** arr_salida, size_t* pos_salida);

bool es_alfanumerico(char* str);

#endif