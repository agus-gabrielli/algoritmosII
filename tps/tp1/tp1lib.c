#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp1lib.h"

typedef enum precedencia {BAJA_PREC, MEDIA_PREC, ALTA_PREC} precedencia_t;
typedef enum asociatividad {ASOC_IZQ, ASOC_DER} asociatividad_t;

struct operador{
    char* simbolo;
    precedencia_t prec; 
    asociatividad_t asoc; 
};

operador_t* crear_operador(char* token){
    operador_t* op = malloc(sizeof(operador_t));
    if(! op){
        free(token);
        return NULL;
    }

    if(! strcmp(token, "+")){
        op->simbolo = token; 
        op->prec = BAJA_PREC;
        op->asoc = ASOC_IZQ;
    }
    else if(! strcmp(token, "-")){
        op->simbolo = token; 
        op->prec = BAJA_PREC;
        op->asoc = ASOC_IZQ;
    }
    else if(! strcmp(token, "*")){
        op->simbolo = token; 
        op->prec = MEDIA_PREC;
        op->asoc = ASOC_IZQ;
    }
    else if(! strcmp(token, "/")){
        op->simbolo = token; 
        op->prec = MEDIA_PREC;
        op->asoc = ASOC_IZQ;
    }
    else if(! strcmp(token, "^")){
        op->simbolo = token; 
        op->prec = ALTA_PREC;
        op->asoc = ASOC_DER;
    }
    else if(! strcmp(token, "(")){ //si bien los paréntesis no son operadores, a nuestra conveniencia los tratamos como tales
        op->simbolo = token; 
    }
    else if(! strcmp(token, ")")){
        op->simbolo = token; 
    }
    
    return op;
}

void destruir_operador(operador_t* op){
    free(op);
}

void liberar_simbolo(operador_t* op){
    free(op->simbolo);
}

char* obtener_simbolo(operador_t* op){
    return op->simbolo;
}

bool operadores_iguales(operador_t* op1, char* token){
    return ! strcmp(op1->simbolo, token);
}

bool mayor_precedencia(operador_t* op1, operador_t* op2){
    return op1->prec > op2->prec;
}

bool igual_precedencia(operador_t* op1, operador_t* op2){
    return op1->prec == op2->prec;
}

bool es_asoc_izq(operador_t* op){
    return ! op->asoc;
}

// Otra funcione útiles

void de_pila_a_salida(pila_t* pila, char** arreglo_salida, size_t* pos_salida){
    operador_t* op_desapilado = pila_desapilar(pila);
    arreglo_salida[*pos_salida] = obtener_simbolo(op_desapilado);
    (*pos_salida)++;
    destruir_operador(op_desapilado);
}   

bool es_alfanumerico(char* str){ 
    for(int i = 0; str[i]; i++){
        if(isalpha(str[i])) return true;
    }
    return false;
}