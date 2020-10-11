#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strutil.h"
#include "pila.h"
#include "tp1lib.h"

bool operar(pila_t* pila, char* op){
    long* res = malloc(sizeof(long));
    bool devolver_false = false;

    if(! ( strcmp("+", op) && strcmp("-", op) && strcmp("*", op) && strcmp("/", op) && strcmp("^", op) && strcmp("log", op) ) ){
        long* operando2 = pila_desapilar(pila);
        long* operando1 = pila_desapilar(pila);

        if(! operando1) devolver_false = true; //si faltan operandos
        else if(!strcmp("+", op)) *res = *operando1 + *operando2; 
        else if(!strcmp("-", op)) *res = *operando1 - *operando2; 
        else if(!strcmp("*", op)) *res = *operando1 * *operando2; 
        else if(!strcmp("/", op)){
            if(! *operando2) devolver_false = true;
            else *res = *operando1 / *operando2;
        }
        else if(!strcmp("^", op)){
            if(*operando2 < 0) devolver_false = true; 
            else *res = pow(*operando1, *operando2); 
        }
        else{
            if(*operando2 < 2) devolver_false = true; 
            else *res = log(*operando1) / log(*operando2); 
        }
        free(operando1);
        free(operando2); //si se libera null no hay problema
    }

    else if(! strcmp("?", op)){
        long* operando3 = pila_desapilar(pila);
        long* operando2 = pila_desapilar(pila);
        long* operando1 = pila_desapilar(pila);
        if(! operando1) devolver_false = true;
        else *res = *operando1 ? *operando2 : *operando3; 
        free(operando1);
        free(operando2);
        free(operando3);
    } 
    
    else if(! strcmp("sqrt", op)){
        long* operando = pila_desapilar(pila);
        if(! operando || *operando < 0) devolver_false = true;
        else *res = sqrt(*operando);
        free(operando);
    }

    else devolver_false = true; //si se ingresaron datos erróneos

    if(devolver_false){
        free(res);
        return false;
    }

    pila_apilar(pila, res);
    return true;
}

bool calcular_resultado(pila_t* pila_operandos, char** arreglo_linea){
    for(size_t i = 0; arreglo_linea[i]; i++){
        if(! strcmp("", arreglo_linea[i])) continue; 

        long* num = malloc(sizeof(long));
        *num = atol(arreglo_linea[i]);
        if(! es_alfanumerico(arreglo_linea[i]) && (*num || ! strcmp("0", arreglo_linea[i]))){
            pila_apilar(pila_operandos, num); //si es un número ó el 0 (caso borde), lo apilamos
            continue;
        }
        free(num);

        if(! operar(pila_operandos, arreglo_linea[i])) return false; 
    }

    long* resultado = pila_desapilar(pila_operandos);
    if(pila_esta_vacia(pila_operandos) && resultado){ //si todo salio bien, la pila debio quedar con 1 elto, el res
        printf("%ld\n", *resultado);
        free(resultado);
        return true;
    }
    free(resultado);
    return false;
}

int main(){
    char** arreglo_linea;
    size_t largo;
    pila_t* pila_operandos = pila_crear();
    char* linea = NULL;
    size_t capacidad = 0;

    while(getline(&linea, &capacidad, stdin) > 0){
        largo = strlen(linea);
        if(linea[largo-1] == '\n') linea[largo-1] = '\0'; //le sacamos el \n

        arreglo_linea = split(linea, ' ');
        if(!arreglo_linea){
            printf("ERROR\n");
            continue;
        }
        if(! calcular_resultado(pila_operandos, arreglo_linea)){
            printf("ERROR\n");
            while(! pila_esta_vacia(pila_operandos)) free(pila_desapilar(pila_operandos));
        }
        free_strv(arreglo_linea);
    }   

    pila_destruir(pila_operandos);
    free(linea);
    return 0;
}