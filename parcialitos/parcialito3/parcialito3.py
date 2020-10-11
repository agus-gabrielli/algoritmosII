# Ejercicios 2, 4 y 6
# Padrón: 104954, Agustín Gabrielli

# ------------------------------------ Ejercicio 2 ------------------------------------
""" Se tiene un grafo no dirigido que nos modela la situación de batallas en una guerra entre dos bandos. En dicho grafo,
cada vértice es una nación, y cada arista (v, w) indica que se ha iniciado una batalla entre dichas naciones. Implementar
un algoritmo que reciba dicho grafo y nos indique si podemos afirmar que al menos una nación ha traicionado su bando.
Dada la naturaleza de la situación, cada nación mantiene secreto cuál es su bando, así que se debe trabajar sólo con la
información de los ataques. Indicar y justificar la complejidad del algoritmo implementado. """

# Solución

""" El algoritmo que voy a utilizar es el de determinar si un grafo es bipartito: el conjunto de vértices (naciones) se debería dividir
en dos, ya que hay dos bandos. En caso de que una nación ataque a su bando enemigo y también a su bando aliado, eso reflejaría que el grafo
haciendo que ya no sea bipartito. Todo esto dentro de una misma componente conexa. O sea voy a tener que analizar si cada componente
conexa es bipartita para concluir si el grafo total es bipartito. 

Complejidad: el algoritmo es O(V + E) siendo V la cantidad de países y E la cantidad de batallas entre países, si es que el grafo
se implementó como lista de adayacencias (diccionario de diccionarios). Esto es porque consiste en recorrer el grafo con BFS haciendo
algunas operaciones O(1) con el diccionario del bando y demás. El BFS es O(V + E) porque recorremos todos los vértices, y recorremos
también todas las aristas (2 veces, pero es lo mismo) cuando hacemos V veces el grafo.adyacentes de cada vértice. """

def hay_traicion_cc(grafo, pais, visitados): # Usé BFS para recorrer la componente conexa
    cola = Cola()
    bando[pais] = 1
    cola.encolar(pais)

    while not cola.esta_vacia():
        p = cola.desencolar()
        visitados.add(pais)

        for enemigo in grafo.adyacentes(p):
            if bando[p] is bando[enemigo]: # Si son del mismo bando y son adyacentes, hubo traición
                return True
            if bando[enemigo] is None:
                bando[p] is 1 ? bando[enemigo] = 2 : bando[enemigo] = 1
                cola.encolar(enemigo)
    return False

def hay_traicion(grafo):
    bando = {} # Los bandos van a ser 1 ó 2
    visitados = set()
    for p in grafo:
        bando[p] = None

    for p in grafo:
        if p not in visitados and hay_traicion_cc(grafo, p, visitados):
            return True

    # En ninguna componente conexa hubo traición
    return False 

# ------------------------------------ Ejercicio 4 ------------------------------------
"""La compañía AlgoPiping de cloacas ha ganado la licitación para renovar todas las cañerías de ciudad Gótica. Para quien
no sepa, una licitación la gana quién propone el menor precio por la realización de un servicio. Por lo tanto, ahora deben
obtener la mayor ganancia reduciendo los costos. No pueden reducir la calidad de los materiales para reducir los costos (si
bien es una práctica usual en ciudad Gótica, el gobernador no tiene más margen para negociados). Tiene un mapa de la
ciudad con todas las cañerías existentes hoy en día que van de un puntos de la ciudad a otro (algunas incluso generan ciclos,
para asegurar el servicio en caso de fallas) y cuánto dinero costaría arreglar cada cañería. Ahora bien, en ningún lado de la
publicación de la licitación se pide que se arreglen todas las cañerías, sino que se asegure que al arreglarse queden todas los
puntos de la ciudad conectadas a la red (no importa qué sucede en caso de fallas, la ciudad no tenía fondos para cubrir
pedir tanto).
Explicar cómo modelarías este problema utilizando grafos, cómo obtendrías cuáles cañerías deberían arreglarse y cuál sería
la complejidad de hacer todo ello. Hacer un breve seguimiento de ejemplo que propongas, con unos 6 puntos. """

# Solución

"""¿Cómo modelaría el problema con grafos? Utilizaría un grafo no dirigido (pues no importa el sentido de las cañerías) y pesado.
Los vértices son aquellos puntos de la ciudad a los que llegan las cañerías, y las 
aristas serían justamente esas cañerías. Cada arista tendría como peso el coste de la reparación de dicha cañería.

¿Cómo obtendría cuales cañerías deberían arreglarse, de forma que gaste lo menor posible y que deje a todos los puntos de la ciudad 
conectados al sistema de cañerías? Calcularía un árbol de tendido mínimo del grafo mencionado arriba, usando, por ejemplo, el Algoritmo 
de Prim. Esto cumple con lo pedido porque, en primer lugar, como el árbol resultado es de "tendido/recubridor", contiene a todos los vértices
o puntos de la ciudad; en segundo lugar, es el de menor costo posible porque el algoritmo logra que la suma de los pesos de las aristas
de este árbol sea mínima. La complejidad del algoritmo es O(E log(V)) siendo E la cantidad de cañerías y V la cantidad de puntos de la 
ciudad. Eso es porque, en el peor de los casos, por cada arista del grafo vamos a encolar/desencolar de un heap con E aristas, eso es 
O(E log (E)), pero como en el peor de los casos E = V(V-1) = V^2 --> O(E log (E)) = O(E 2log (V)) = O(E log (V).

El seguimiento está en la foto adjuntada en el zip. """

# ------------------------------------ Ejercicio 6 ------------------------------------
""" Indicar si las siguientes afirmaciones son verdaderas o falsas. Justificar.
a. Al resolver el problema de maximización de flujo buscamos caminos entre la fuente y el sumidero en la red residual. Si
en dicho camino se utiliza una arista que no existe en el grafo original, significa que el flujo en la arista original (la del
grafo original) se debe aumentar.
b. No podemos resolver el problema de maximización de flujo si hay ciclos en el grafo.
c. Si calculo el árbol de tendido mínimo de un grafo, y luego sobre ese árbol obtengo los caminos mínimos de un vértice a
todos los demás, los caminos pueden coincidir con los caminos mínimos en el grafo original, pero no siempre sucederá.
Aclaración: dar los ejemplos o contraejemplos que justifiquen/ejemplifiquen tu respuesta. """

# Solución

""" 
a. Falso. Al contrario, significa que conviene reducir el flujo que pasa por esa arista (del original) para aprovechar y mandar ese
flujo por otra arista que sea más provechosa. Una arista del grafo residual (de peso x) que no está en el grafo original significa
que se llevó x flujo por la arista del grafo original entre esos mismos vértices. Si un camino de aumento pasa por esta arista, pasa 
lo que expliqué arriba: hay que reducir el flujo por esta arista para poder aumentar el flujo máximo de la red.  

b. Falso. Siempre que tengamos una red de flujo hay solución al problema de maximización de flujo. Sin embargo, a veces hay que hacer
modificaciones al grafo original para que el algoritmo que se utiliza -Ford Fulkerson- pueda resolverlo. Dependiendo de los ciclos que se
tengan, habrá o no que hacer algunas modificaciones.
Si los ciclos son de longitud (cantidad de aristas) mayor o igual a 3, no habría problema de aplicar el algoritmo directamente
sobre ese grafo -siempre y cuando cumpla con todas las otras restricciones-. Ahora, si hay bucles los sacamos, y si hay ciclos de longitud 2,
o sea aristas antiparalelas, debemos poner un vértice intermedio entre los vértices de forma tal que ahora el ciclo es de longitud 3 (una
arista la dejamos como estaba, la otra hacemos que pase por este vértice intermedio, usando el mismo peso original en los dos tramos). Con
estas modificaciones, ya sí se podría aplicar el algoritmo. 

c. Verdadero. Hay veces que eso puede pasar, pero en general no porque son definiciones distintas para cosas distintas que poco tienen que ver. 
En la imagen adjunta se muestra un ejemplo de cada situación.
"""