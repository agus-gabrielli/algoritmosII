#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pila.h"
#include "cola.h"
#include "tp1lib.h"
#include "strutil.h"

char* obtener_postfija(cola_t* cola_tokens, size_t largo){
    char** arreglo_salida = malloc(sizeof(char*) * (largo+1));
    size_t pos_salida = 0;
    pila_t* pila_op = pila_crear();

    for(size_t i = 0; ! cola_esta_vacia(cola_tokens); i++){
        char* token = cola_desencolar(cola_tokens);

        long num = atol(token);
        if(num || ! strcmp("0", token)){
            arreglo_salida[pos_salida] = token;
            pos_salida++;
            continue;
        }

        operador_t* op = crear_operador(token);

        if(operadores_iguales(op, "(")){
            pila_apilar(pila_op, op);
            continue;
        }

        if(operadores_iguales(op, ")")){
            while(! operadores_iguales(pila_ver_tope(pila_op), "(")){
                de_pila_a_salida(pila_op, arreglo_salida, &pos_salida);
            }
            operador_t* paren_izq = pila_desapilar(pila_op);
            liberar_simbolo(paren_izq);
            destruir_operador(paren_izq);
            destruir_operador(op);
            free(token);
            continue;
        }    
    
        //op es + - * / ó ^
        while( (! pila_esta_vacia(pila_op)) && (! operadores_iguales(pila_ver_tope(pila_op), "(") ) && ( mayor_precedencia(pila_ver_tope(pila_op), op) || ( igual_precedencia(pila_ver_tope(pila_op), op) && es_asoc_izq(op) ) ) ){
            de_pila_a_salida(pila_op, arreglo_salida, &pos_salida);
        }
        pila_apilar(pila_op, op);
    }   

    while(! pila_esta_vacia(pila_op)){
        de_pila_a_salida(pila_op, arreglo_salida, &pos_salida);
    }

    pila_destruir(pila_op);
    arreglo_salida[pos_salida] = NULL;
    char* linea_resultado = join(arreglo_salida, ' ');
    free_strv(arreglo_salida);
    return linea_resultado;
}

cola_t* obtener_cola_tokens(char* linea, size_t* largo_cola){
    cola_t* cola_tokens = cola_crear();

    for(size_t i = 0; linea[i] && ! (linea[i] == '\n'); i++){ 
        if(linea[i] == ' ') continue;

        if(! isdigit(linea[i])){ 
            cola_encolar(cola_tokens, substr(linea + i, 1)); 
            (*largo_cola)++;
            continue;
        } 

        size_t j = i + 1; //entonces es un número
        while(isdigit(linea[j])) j++;
        cola_encolar(cola_tokens, substr(linea + i, j - i)); 
        (*largo_cola)++;
        i = j - 1;
    }
    return cola_tokens;
}

int main(){
    cola_t* cola_tokens;
    size_t largo = 0;
    char* linea = NULL;
    size_t capacidad = 0;

    while(getline(&linea, &capacidad, stdin) > 0){
        cola_tokens = obtener_cola_tokens(linea, &largo);

        char* linea_salida = obtener_postfija(cola_tokens, largo);
    
        printf("%s\n", linea_salida);

        cola_destruir(cola_tokens, NULL); 
        free(linea_salida);
    }   
    free(linea);

    return 0;
}