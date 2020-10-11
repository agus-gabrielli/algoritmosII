#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include "testing.h"

void prueba_crear_destruir(){
    printf("Inicio de prueba crear y destruir lista\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_un_elemento1(){
    printf("Inicio de prueba de insertar_primero un elemento y borrarlo\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo de la lista es 0", 0 == lista_largo(lista));
    int num1; //pruebo insertando un puntero a entero
    print_test("    Se inserta_primero un puntero a entero", lista_insertar_primero(lista, &num1));
    print_test("    El primero de la lista es dicho elemento", &num1 == lista_ver_primero(lista));
    print_test("    El útlimo de la lista es dicho elemento", &num1 == lista_ver_ultimo(lista));
    print_test("    El largo de la lista es 1", 1 == lista_largo(lista));
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    Se borra_primero correctamente", &num1 == lista_borrar_primero(lista));
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo de la lista es 0", 0 == lista_largo(lista));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_un_elemento2(){
    printf("Inicio de prueba de insertar_ultimo un elemento y borrarlo\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo de la lista es 0", 0 == lista_largo(lista));
    int num1; //pruebo insertando un puntero a enteros
    print_test("    Se inserta_ultimo un puntero a entero", lista_insertar_ultimo(lista, &num1));
    print_test("    El primero de la lista es dicho elemento", &num1 == lista_ver_primero(lista));
    print_test("    El útlimo de la lista es dicho elemento", &num1 == lista_ver_ultimo(lista));
    print_test("    El largo de la lista es 1", 1 == lista_largo(lista));
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    Se borra_primero correctamente", &num1 == lista_borrar_primero(lista));
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo de la lista es 0", 0 == lista_largo(lista));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_insertar_borrar_varios(){
    printf("Inicio de prueba de insertar y borrar varios elementos\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    int num1, num2, num3, num4; 
    print_test("    Se inserta_primero un puntero a entero", lista_insertar_primero(lista, &num3));
    print_test("    Se inserta_primero otro puntero a entero", lista_insertar_primero(lista, &num2));
    print_test("    El largo de la lista es 2", 2 == lista_largo(lista));
    print_test("    Se inserta_ultimo otro puntero a entero", lista_insertar_ultimo(lista, &num4));
    print_test("    Se inserta_primero un cuarto puntero a entero", lista_insertar_primero(lista, &num1));
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    El largo de la lista es 4", 4 == lista_largo(lista));
    print_test("    El primero de la lista es el correcto", &num1 == lista_ver_primero(lista));
    print_test("    El último de la lista es el correcto", &num4 == lista_ver_ultimo(lista));
    print_test("    Se borra al primer elemento", &num1 == lista_borrar_primero(lista));
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    El largo de la lista es ahora  3", 3 == lista_largo(lista));
    print_test("    El primero de la lista es el correcto", &num2 == lista_ver_primero(lista));
    print_test("    El último de la lista es el correcto", &num4 == lista_ver_ultimo(lista));
    print_test("    Se borra al primer elemento", &num2 == lista_borrar_primero(lista));
    print_test("    Se borra al primer elemento", &num3 == lista_borrar_primero(lista));
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    El largo de la lista es ahora  1", 1 == lista_largo(lista));
    print_test("    El primero y el último son el mismo, y el correcto", &num4 == lista_ver_primero(lista) && &num4 == lista_ver_ultimo(lista));
    print_test("    Se borra al primer elemento", &num4 == lista_borrar_primero(lista));
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo de la lista es 0", 0 == lista_largo(lista));
    print_test("    Lista ver_primero es NULL", !lista_ver_primero(lista));
    print_test("    Lista ver_ultimo es NULL", !lista_ver_ultimo(lista));
    print_test("    Lista borrar_primero devuelve NULL", !lista_borrar_primero(lista));    
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_insertar_NULL(){
    printf("Inicio de prueba de insertar NULL\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    print_test("    Se inserta_primero NULL", lista_insertar_primero(lista, NULL));
    print_test("    El primero es NULL", !lista_ver_primero(lista));  
    print_test("    El último es NULL", !lista_ver_ultimo(lista));  
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    Se borra y se devuelve NULL que estaba insertado", !lista_borrar_primero(lista)); 
    print_test("    La lista ahora está vacía", lista_esta_vacia(lista));      
    printf("Se repite la operación pero insertando_ultimo NULL");
    print_test("    Se inserta_ultimo NULL", lista_insertar_ultimo(lista, NULL));
    print_test("    El primero es NULL", !lista_ver_primero(lista));  
    print_test("    El último es NULL", !lista_ver_ultimo(lista));  
    print_test("    La lista no está vacía", !lista_esta_vacia(lista));
    print_test("    Se borra y se devuelve NULL que estaba insertado", !lista_borrar_primero(lista)); 
    print_test("    La lista ahora está vacía", lista_esta_vacia(lista));      
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_vacia_cuando_creada(){
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo es 0", !lista_largo(lista));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);
    printf("\n");
}

void prueba_borrar_verprimero_verultimo_cuando_creada(){
    printf("Inicio de prueba de borrar_primero, ver_primero y ver_ultimo cuando creada\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);
    print_test("    No se puede borrar_primero", !lista_borrar_primero(lista));
    print_test("    No se puede ver_primero", !lista_ver_primero(lista));
    print_test("    No se puede ver_ultimo", !lista_ver_ultimo(lista));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);    
    printf("\n");
}

void prueba_borrar_hasta_vacia(){ 
    printf("Inicio de prueba de borrar_primero hasta estar vacía\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);    
    long num1, num2, num3; //probamos insertando punteros a long para variar
    print_test("    Se inserta el primer elemento", lista_insertar_primero(lista, &num3));
    print_test("    Se inserta un segundo elemento", lista_insertar_primero(lista, &num2));
    print_test("    Se inserta un tercer elemento", lista_insertar_primero(lista, &num1));
    print_test("    Se insertaron tres elementos", true);
    print_test("    Se borra_primero correctamente", lista_borrar_primero(lista) ==&num1);
    print_test("    Se borra_primero correctamente", lista_borrar_primero(lista) ==&num2);
    print_test("    Se borra_primero correctamente", lista_borrar_primero(lista) ==&num3);
    print_test("    Se borraron los tres elementos", true);
    printf("    Comprobemos que la lista se comporta como si fuese recien creada:\n");
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    print_test("    El largo es 0", !lista_largo(lista));
    print_test("    borrar_primero es inválido (devuelve NULL)", !lista_borrar_primero(lista));
    print_test("    Ver primero es inválido (devuelve NULL)", !lista_ver_primero(lista));
    print_test("    Ver último es inválido (devuelve NULL)", !lista_ver_ultimo(lista));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);        
    printf("\n");
}

const size_t NUM_ELEMENTOS = 10000;
void prueba_volumen(){
    printf("Inicio de prueba de volumen con %zu elementos\n", NUM_ELEMENTOS);
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);       
    //insertamos_ultimo punteros a chars (posiciones de un arreglo de chars)
    char* vector_volumen = malloc(NUM_ELEMENTOS * sizeof(char)); 
    size_t errores_insertar = 0;
    size_t errores_borrar = 0;
    for(size_t i = 0; i < NUM_ELEMENTOS; i++){ 
        if(!lista_insertar_ultimo(lista, vector_volumen + i * sizeof(char))) errores_insertar++;
    }
    print_test("    Se insertaron_ultimo todos los elementos", !errores_insertar); 
    void* elem_borrado;
    for(size_t j = 0; j < NUM_ELEMENTOS; j++){ 
        elem_borrado = lista_ver_primero(lista);
        if(elem_borrado != lista_borrar_primero(lista)) errores_borrar++;
        if(elem_borrado != vector_volumen + j * sizeof(char)) errores_borrar++;//chequeo que salen en el orden a como los inserté
    }
    print_test("    Se borraron todos los elementos", !errores_borrar); 
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    printf("    Se registraron %zu errores en la prueba\n", errores_insertar + errores_borrar);
    free(vector_volumen);
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true);   
    printf("\n");
}

void prueba_destruccion_no_vacia_NULL(){
    printf("Inicio de prueba de destrucción de la lista estando no vacía y pasando NULL a destruir\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista);       
    int num1, num2, num3;
    print_test("    Se inserta_ultimo un puntero a entero", lista_insertar_ultimo(lista, &num1));
    print_test("    Se inserta_ultimo un segundo puntero a entero", lista_insertar_ultimo(lista, &num2));
    print_test("    Se inserta_ultimo un tercer puntero a entero", lista_insertar_ultimo(lista, &num3));
    lista_destruir(lista, NULL);
    print_test("    Se destruye la lista", true); 
    printf("\n");
}

void prueba_destruccion_vacia_funcion1(){
    printf("Inicio de prueba de destrucción de la lista estando vacía y pasando free como función\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista); 
    print_test("    La lista está vacía", lista_esta_vacia(lista));
    lista_destruir(lista, free);
    print_test("    Se destruye la lista", true); 
    printf("\n");
}

void prueba_destruir_funcion1(){
    printf("Inicio de prueba de destruir lista pasando la funcion free como argumento\n");
    lista_t* lista = lista_crear();
    print_test("    Se crea la lista", lista); 
    void* dato;
    for(int i = 0; i < 5; i++){
        dato = malloc(sizeof(void*));
        lista_insertar_ultimo(lista, dato);
    }
    print_test("    Se insertaron_ultimo algunos punteros genéricos", true);
    print_test("    Se destruye la lista pasando la funcion free", true);
    lista_destruir(lista, free);
    printf("\n");
}

//PRUEBAS ITERADOR INTERNO

bool sumar_todos(void* dato, void* extra){
    *(int*) extra += *(int*) dato;
    return true;
}

void prueba_iterador_interno1(){
    printf("Inicio de prueba de iterador interno con función sumar_todos que suma todos los datos de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 1, num2 = 5, num3 = 10, num4 = 15; 
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num1));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num2));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num3));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num4));
    print_test("    Se insertaron 4 punteros a enteros", true);
    int suma = 0;
    lista_iterar(lista, sumar_todos, &suma);
    print_test("    Se iteró y se sumaron todos los elementos correctamente", num1+num2+num3+num4 == suma);
    lista_destruir(lista, NULL);
    printf("\n");
}

typedef struct comodin{
    int suma;
    int contador;
} comodin_t;

bool sumar_primeros_2(void* dato, void* extra){
    ((comodin_t*) extra)->suma += *(int*) dato;
    ((comodin_t*) extra)->contador ++;
    if( ((comodin_t*) extra)->contador >= 2) return false; //cambié de lugar esta línea, de manera que si se 
    //llama accidentalmente de vuelta a la función cuando contador >=2 porque no cortó el iterador, suma dé mal 
    return true;
}

void prueba_iterador_interno2(){
    printf("Inicio de prueba de iterador interno con función sumar_primeros_2 que suma los primeros 2 datos de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 1, num2 = 5, num3 = 10, num4 = 15; 
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num1));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num2));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num3));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, &num4));
    print_test("    Se insertaron 4 punteros a enteros", true);

    comodin_t* extra = malloc(sizeof(comodin_t));
    extra->suma = 0;
    extra->contador = 0;
    lista_iterar(lista, sumar_primeros_2, extra);
    print_test("    Se iteró y se sumaron los dos primeros elementos correctamente", num1+num2 == extra->suma);
    free(extra);
    lista_destruir(lista, NULL);
    printf("\n");
}

//PRUEBAS ITERADOR EXTERNO

void prueba_iterador_externo_sumar_elementos(){
    printf("Inicio de prueba de iterador externo, sumando todos los elementos de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 1, num2 = 5, num3 = 10, num4 = 15; 
    int* nums[] = {&num1, &num2, &num3, &num4};
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, nums[0]));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, nums[1]));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, nums[2]));
    print_test("    Se inserta último un puntero a entero", lista_insertar_ultimo(lista, nums[3]));
    print_test("    Se insertaron 4 punteros a enteros", true);
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);
    int suma = 0;
    for(int i=0;!lista_iter_al_final(iter); i++){
        print_test("    El elemento actual es el correcto", lista_iter_ver_actual(iter) == nums[i]);
        suma += *(int*) lista_iter_ver_actual(iter);
        lista_iter_avanzar(iter);
    }
    print_test("    Se iteró con el iterador externo y se sumaron los elementos correctamente", num1+num2+num3+num4 == suma);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true);
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_insertar_principio(){
    printf("Inicio de prueba en la que el iterador inserta un elemento cuando está al principio de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 3 punteros a enteros", true);
    print_test("    El largo de la lista es 3", lista_largo(lista) == 3);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);
    print_test("    El iterador está en la primera posición", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("    Se insertó un puntero en dicha posición",lista_iter_insertar(iter, &num1));
    print_test("    El primero de la lista es el puntero recién insertado", lista_ver_primero(lista) == &num1);
    print_test("    El largo de la lista ahora es 4", lista_largo(lista) == 4);
    print_test("    El último sigue siendo el correcto", lista_ver_ultimo(lista) == &num4);
    print_test("    El iterador está parado sobre el puntero recién insertado", &num1 == lista_iter_ver_actual(iter));
    print_test("    Se avanza una posición", lista_iter_avanzar(iter));
    print_test("    El iterador está parado ahora sobre el elemento que antes era primero", lista_iter_ver_actual(iter) == &num2);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true);
    print_test("    El primero de la lista sigue siendo el puntero recién insertado", lista_ver_primero(lista) == &num1);    
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_insertar_final(){
    printf("Inicio de prueba en la que el iterador inserta un elemento cuando está al final de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    print_test("    Se insertaron 3 punteros a enteros", true);
    print_test("    El largo de la lista es 3", lista_largo(lista) == 3);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);

    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó el iterador hasta llegar al final de la lista", lista_iter_al_final(iter));

    print_test("    Se insertó un puntero en dicha posición",lista_iter_insertar(iter, &num4));
    print_test("    El último de la lista es el puntero recién insertado", lista_ver_ultimo(lista) == &num4);
    print_test("    El largo de la lista ahora es 4", lista_largo(lista) == 4);
    print_test("    El primero sigue siendo el correcto", lista_ver_primero(lista) == &num1);
    print_test("    El iterador está parado sobre el puntero recién insertado", &num4 == lista_iter_ver_actual(iter));
    print_test("    El iter ahora ya no está más en el final de la lista", !lista_iter_al_final(iter));
    print_test("    Se avanza una posición", lista_iter_avanzar(iter));
    print_test("    Ahora si el iterador llegó al final de la lista", lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true);
    print_test("    El último de la lista sigue siendo el puntero recién insertado", lista_ver_ultimo(lista) == &num4);    
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_insertar_medio(){
    printf("Inicio de prueba en la que el iterador inserta un elemento cuando está por el medio de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 3 punteros a enteros", true);
    print_test("    El largo de la lista es 3", lista_largo(lista) == 3);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);
    print_test("    Se avanza una posición", lista_iter_avanzar(iter));
    print_test("    El iterador no está al final de la lista", !lista_iter_al_final(iter));
    print_test("    Tampoco está al principio de la lista", !lista_iter_al_final(iter));
    print_test("    Se insertó un puntero en dicha posición", lista_iter_insertar(iter, &num2));
    print_test("    El iterador está parado sobre el puntero recién insertado", &num2 == lista_iter_ver_actual(iter));
    print_test("    No se modificó el último de la lista", lista_ver_ultimo(lista) == &num4);
    print_test("    Tampoco se modificó el primero", lista_ver_primero(lista) == &num1);
    print_test("    El largo de la lista ahora es 4", lista_largo(lista) == 4);
    print_test("    Se avanza una posición", lista_iter_avanzar(iter));
    print_test("    El iterador está parado ahora sobre el elemento que antes era segundo", lista_iter_ver_actual(iter) == &num3);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true);
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_borrar_principio(){
    printf("Inicio de prueba en la que el iterador borra el elemento cuando está al principio de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 4 punteros a enteros", true);
    print_test("    El largo de la lista es 4", lista_largo(lista) == 4);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);
    print_test("    El iterador está en la primera posición", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("    El iterador borró el elemento en dicha posición y devuelve el dato correcto", &num1 == lista_iter_borrar(iter));
    print_test("    El primero de la lista es ahora el elemento donde está el iterador", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    print_test("    El iterador está parado sobre el puntero correcto", &num2 == lista_iter_ver_actual(iter));
    print_test("    El largo de la lista ahora es 3", lista_largo(lista) == 3);
    print_test("    El último sigue siendo el correcto", lista_ver_ultimo(lista) == &num4);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true); 
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_borrar_ultimo(){
    printf("Inicio de prueba en la que el iterador borra el elemento cuando está sobre el último de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 4 punteros a enteros", true);
    print_test("    El largo de la lista es 4", lista_largo(lista) == 4);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);

    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó el iterador hasta llegar al último elemento de la lista", lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));

    print_test("    El iterador borró el elemento en dicha posición y devuelve el dato correcto", &num4 == lista_iter_borrar(iter));
    print_test("    El último de la lista es ahora el elemento anterior al que se borró", lista_ver_ultimo(lista) == &num3);
    print_test("    El iterador ahora está al final de la lista", lista_iter_al_final(iter));
    print_test("    El largo de la lista ahora es 3", lista_largo(lista) == 3);
    print_test("    El primero sigue siendo el correcto", lista_ver_primero(lista) == &num1);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true); 
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_borrar_medio(){
    printf("Inicio de prueba en la que el iterador borra el elemento cuando está al principio de la lista\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 4 punteros a enteros", true);
    print_test("    El largo de la lista es 4", lista_largo(lista) == 4);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);
    print_test("    Se avanza una posición", lista_iter_avanzar(iter));
    print_test("    El iterador no está al final de la lista", !lista_iter_al_final(iter));
    print_test("    Tampoco está al principio de la lista", !lista_iter_al_final(iter));
    print_test("    El iterador borró el elemento en dicha posición y devuelve el dato correcto", &num2 == lista_iter_borrar(iter));
    print_test("    El iterador está ahora parado sobre el elemento correcto", &num3 == lista_iter_ver_actual(iter));
    print_test("    El largo de la lista ahora es 3", lista_largo(lista) == 3);
    print_test("    El último sigue siendo el correcto", lista_ver_ultimo(lista) == &num4);    
    print_test("    Tampoco se modificó el primero", lista_ver_primero(lista) == &num1);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true); 
    lista_destruir(lista, NULL);
    printf("\n");
}

void prueba_iterador_externo_borrar_final(){
    printf("Inicio de prueba en la que al llamar a lista_iter_borrar cuando lista_iter_al_final es true se devuelve NULL\n");
    lista_t* lista = lista_crear();
    int num1 = 5, num2 = 10, num3 = 15, num4 = 20; 
    lista_insertar_ultimo(lista, &num1);
    lista_insertar_ultimo(lista, &num2);
    lista_insertar_ultimo(lista, &num3);
    lista_insertar_ultimo(lista, &num4);
    print_test("    Se insertaron 4 punteros a enteros", true);
    print_test("    El largo de la lista es 4", lista_largo(lista) == 4);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("    Se creó el iterador", true);

    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));
    print_test("    Se avanzó una posición",  lista_iter_avanzar(iter));

    print_test("    Se avanzó el iterador hasta llegar al final de la lista", lista_iter_al_final(iter));

    print_test("    Al intentar borrar el elemento, como no hay ninguno, se devuelve NULL", !lista_iter_borrar(iter));
    print_test("    El último de la lista no cambió", lista_ver_ultimo(lista) == &num4);
    print_test("    El primero sigue siendo el correcto", lista_ver_primero(lista) == &num1);
    print_test("    El iterador sigue en el final de la lista", lista_iter_al_final(iter));
    print_test("    El largo de la lista sigue siendo 4", lista_largo(lista) == 4);
    lista_iter_destruir(iter);
    print_test("    Se destruyó el iterador", true); 
    lista_destruir(lista, NULL);
    printf("\n");
}

void pruebas_lista_alumno(void){
    prueba_crear_destruir();
    prueba_un_elemento1();
    prueba_un_elemento2();
    prueba_insertar_borrar_varios();
    prueba_insertar_NULL();
    prueba_vacia_cuando_creada();
    prueba_borrar_verprimero_verultimo_cuando_creada();
    prueba_borrar_hasta_vacia();
    prueba_volumen();
    prueba_destruccion_no_vacia_NULL();
    prueba_destruccion_vacia_funcion1();
    prueba_destruir_funcion1();

    prueba_iterador_interno1();
    prueba_iterador_interno2();
    prueba_iterador_externo_sumar_elementos();
    prueba_iterador_externo_insertar_principio();
    prueba_iterador_externo_insertar_final();
    prueba_iterador_externo_insertar_medio();
    prueba_iterador_externo_borrar_principio();
    prueba_iterador_externo_borrar_ultimo();
    prueba_iterador_externo_borrar_medio();
    prueba_iterador_externo_borrar_final();

    printf("Fin de las pruebas del alumno.\n");
}