

typedef struct ab{
    struct ab* izq;
    struct ab* der;
    char* clave;
} ab_t;

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 4(**) Dado un árbol binario, escriba una primitiva recursiva que cuente la cantidad 
 * de nodos que tienen exactamente dos hijos directos. ¿Qué orden de complejidad tiene la función implementada?
*/

size_t cant_nodos_con_dos_hijos(ab_t* ab){ // Lo implementé con postorder
    if(! ab) return 0;

    size_t suma = cant_nodos_con_dos_hijos(ab->izq) + cant_nodos_con_dos_hijos(ab->der);
    return ab->izq && ab->der ? suma +1 : suma; // Es O(n)
}

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 6(**) Suponer que se tiene un ABB A con una función de comparación cmp1 con n claves. También, se tiene otro 
 * ABB vacío B con función de comparación cmp2 (con cmp1 y cmp2 diferentes). ¿Es posible insertar en algún orden todas
 * las claves de A en B de tal forma que ambos tengan exactamente la misma estructura? Si es posible, describir 
 * un algoritmo que permita lograr esto; si no lo es, razonar por qué. (Considerar que la lógica a emplear debe funcionar para 
 * cualquier valor de n y cualquier estructura que tenga el ABB A.)
*/

/**
 * Respuesta: NO es posible. Si tuvieran la misma estructura, tendrían el mismo inorder. Si tienen el mismo inorder, 
 * el orden es el mismo, lo cual contradice la consigna de que cmp1 y 2 son diferentes (al menos supongamos 
 * que para los N elementos no dan lo mismo). Digamos, este sería un razonamiento por el absurdo. 
*/

/**
 * -------------------------------------------------------------------------------------------------------------------------
 * 10(**) Indicar si las siguientes afirmaciones son verdaderas o falsas. En caso de ser verdaderas, justificar, 
 * en caso de ser falsas poner un contraejemplo: 
 * 1. Si dos árboles binarios tienen el mismo recorrido inorder, entonces tienen la misma estructura. 
 * 2. Si dos árboles binarios tienen el mismo recorrido preorder, entonces tienen la misma estructura.
 * 3. Si dos árboles binarios de búsqueda (e idéntica función de comparación) tienen el mismo recorrido preorder, 
 * entonces tienen la misma estructura.
*/

/**
 * Respuesta.
 * 1: NO. Contraejemplo: raíz = 2, hijo_izq = 1, hijo_der = 3 | y | raíz = 3, hijo_izq = 2, hijo_izq de 2 = 1
 * 2: NO. Contraejemplo: raíz = 2, izq = 1 | y | raíz = 2, der = 1 (recordar que es AB, NO ABB), por eso podemos poner
 * al 1 a la derecha del 2, no importa el orden acá. 
 * 3: SÍ, ahora que tenemos ABB con su func. de comp, sí. en el 2 no importaba cuál era el izq y el der porque no era ABB, 
 * pero ahora con la func. de comp. sí y solamente hay una forma de acomodarlos. Con lo cual si tienen mismo preorder y misma
 * func. de comp., tienen misma estructura. 
*/
