#include "pa2m.h"

#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef struct {
	size_t id;
	size_t salud;
	char *nombre_entrenador;
	char *nombre;
} pkm_para_destruir_t;

int comparador(void *elemento, void *contexto)
{
	if (elemento == contexto)
		return 0;

	return ERROR;
}

bool leer_elementos(void *elemento, void *contador)
{
	if (!elemento)
		return false;

	(*(size_t *)contador)++;
	return true;
}

void pruebas_de_creacion_y_destruccion()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear una lista correctamente");

	pa2m_afirmar(!lista_tamanio(lista) && !lista_primero(lista) &&
			     !lista_ultimo(lista) && lista_vacia(lista),
		     "La lista esta vacia");

	lista_destruir(lista);
}

void pruebas_insertar_y_destruir()
{
	lista_t *lista = lista_crear();

	char a = 'a';

	pa2m_afirmar(lista_insertar(lista, &a) != NULL,
		     "Se puede insertar al final de una lista vacia");

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "Se puede insertar NULL al final de la lista");

	lista_destruir(lista);
}

void pruebas_leer_lista()
{
	lista_t *lista = lista_crear();

	char a = 'a', b = 'b';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");

	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "Se insertan 2 elementos, y el tamanio es 2");

	pa2m_afirmar(lista_primero(lista) == &a,
		     "Se puede leer el primer elemento de la lista");

	pa2m_afirmar(lista_ultimo(lista) == &b,
		     "Se puede leer el ultimo elemento de la lista");

	lista_destruir(lista);
}

void pruebas_insertar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

	//Primera insercion
	pa2m_afirmar(lista_insertar_en_posicion(lista, &b, 0) != NULL,
		     "Se puede insertar un elemento en una lista vacia");

	pa2m_afirmar(lista_primero(lista) == &b, "El primer elemento es b");
	pa2m_afirmar(lista_ultimo(lista) == &b, "El ultimo elemento es b");

	//Segunda insercion
	pa2m_afirmar(lista_insertar_en_posicion(lista, &a, 0) != NULL,
		     "Se puede insertar un elemento en la primera posicion");

	pa2m_afirmar(lista_primero(lista) == &a,
		     "El primer elemento ahora es a");

	//Tercera insercion
	pa2m_afirmar(lista_insertar_en_posicion(lista, &c, 1) != NULL,
		     "Se puede insertar un elemento al medio de la lista");

	//Cuarta insercion
	pa2m_afirmar(lista_insertar_en_posicion(lista, &d, 3) != NULL,
		     "Se puede insertar un elemento en la ultima posicion");

	pa2m_afirmar(lista_ultimo(lista) == &d,
		     "El ultimo elemento ahora es d");

	//Quinta y ultima insercion
	pa2m_afirmar(lista_insertar_en_posicion(lista, &e, 100) != NULL,
		     "Se puede insertar en una posicion inexistente");

	pa2m_afirmar(lista_primero(lista) == &a && lista_ultimo(lista) == &e,
		     "Se puede obtener el inicio y el fin de la lista");

	pa2m_afirmar(!lista_vacia(lista) && lista_tamanio(lista) == 5,
		     "Se insertaron 5 elementos y el tamanio es 5");

	lista_destruir(lista);
}

void pruebas_quitar_al_final()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar(lista),
		     "No se pueden quitar elementos de una lista vacia");

	char a = 'a', b = 'b';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	pa2m_afirmar(lista_quitar(lista) == &b,
		     "Se pueden quitar elementos del final de la lista");

	pa2m_afirmar(lista_ultimo(lista) == &a && lista_tamanio(lista) == 1,
		     "Se reajusta bien la lista");

	pa2m_afirmar(lista_quitar(lista) == &a,
		     "Se puede quitar el unico elemento de la lista");

	pa2m_afirmar(!lista_tamanio(lista) && lista_vacia(lista) &&
			     !lista_primero(lista) && !lista_ultimo(lista),
		     "La lista queda vacia y reajustada");

	lista_destruir(lista);
}

void pruebas_quitar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar_de_posicion(lista, 0),
		     "No se pueden quitar elementos de una lista vacia");

	int numeros[] = { 1, 2, 3, 4, 5 };

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar(lista, &numeros[i]);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &numeros[0],
		     "Se puede quitar el primer elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 1) == &numeros[2],
		     "Se pueden quitar elementos del medio de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &numeros[4],
		     "Se puede quitar el ultimo elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 100) == &numeros[3],
		     "Se pueden quitar elementos de posiciones inexistentes");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &numeros[1],
		     "Se puede quitar el unico elemento de la lista");

	pa2m_afirmar(!lista_tamanio(lista) && lista_vacia(lista) &&
			     !lista_primero(lista) && !lista_ultimo(lista),
		     "La lista queda vacia y reajustada");

	lista_destruir(lista);
}

void pruebas_buscar_por_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "No se pueden buscar elementos de una lista vacia");

	int numeros[] = { 1, 2, 3 };

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar_en_posicion(lista, &numeros[i], i);

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &numeros[0],
		     "Se puede encontrar el primer elemento de la lista");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &numeros[1],
		     "Se pueden encontrar elementos en el medio de la lista");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &numeros[2],
		     "Se puede encontrar el ultimo elemento de la lista");

	lista_destruir(lista);
}

void pruebas_buscar_por_condicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_buscar_elemento(lista, comparador, NULL),
		     "No se pueden buscar elementos de una lista vacia");

	int numeros[] = { 1, 2, 3 };

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar(lista, &numeros[i]);

	void *elemento_buscado =
		lista_buscar_elemento(lista, comparador, &numeros[2]);
	pa2m_afirmar(elemento_buscado == &numeros[2],
		     "Se puede buscar un elemento con cualquier condicion");

	pa2m_afirmar(!lista_buscar_elemento(lista, comparador, NULL),
		     "No encontrar el elemento devuelve NULL");

	lista_destruir(lista);
}

void pruebas_del_iterador_interno()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_con_cada_elemento(lista, leer_elementos, NULL),
		     "Iterar una lista vacia devuelve 0 elementos iterados");

	int numeros[] = { 1, 2, 3, 0, 4 };
	size_t contador = 0;

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar(lista, &numeros[i]);

	size_t iterados = lista_con_cada_elemento(lista, leer_elementos,
						  (void *)&contador);
	pa2m_afirmar(iterados == contador,
		     "Se pueden leer los elementos con el iterador interno");

	lista_destruir(lista);
}

void pruebas_destruir_todos_los_elementos()
{
	lista_t *lista = lista_crear();

	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(float)));
	lista_insertar(lista, malloc(sizeof(long)));
	lista_insertar(lista, malloc(sizeof(char)));
	lista_insertar(lista, malloc(sizeof(pkm_para_destruir_t)));

	lista_destruir_todo(lista, free);
	printf("Destruir la lista con exito no debe perder memoria\n");

	return;
}

void pruebas_de_lista_con_parametros_invalidos()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_insertar(NULL, NULL),
		     "Insertar elementos a una lista que no existe da error");

	pa2m_afirmar(!lista_insertar_en_posicion(NULL, NULL, 0),
		     "Insertar al inicio a una lista que no existe da error");

	pa2m_afirmar(!lista_quitar(NULL),
		     "Quitar elementos de una lista que no existe da error");

	pa2m_afirmar(!lista_quitar_de_posicion(NULL, 0),
		     "Quitar al inicio de una lista que no existe da error");

	pa2m_afirmar(!lista_elemento_en_posicion(NULL, 0),
		     "Buscar por posicion en listas que no existen da error");

	pa2m_afirmar(!lista_buscar_elemento(NULL, comparador, NULL),
		     "Buscar por contexto en listas que no existen da error");

	pa2m_afirmar(!lista_buscar_elemento(lista, NULL, NULL),
		     "Buscar con funcion comparadora nula da error");

	pa2m_afirmar(!lista_con_cada_elemento(NULL, leer_elementos, NULL),
		     "Iterar elementos en una lista que no existe da error");

	pa2m_afirmar(!lista_con_cada_elemento(lista, NULL, NULL),
		     "Iterar elementos con una funcion nula da error");

	lista_destruir(lista);
}

void pruebas_del_tda_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_de_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR Y DESTRUIR ELEMENTOS");
	pruebas_insertar_y_destruir();

	pa2m_nuevo_grupo("PRUEBAS DE LEER UNA LISTA");
	pruebas_leer_lista();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR EN CUALQUIER POSICION");
	pruebas_insertar_en_cualquier_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR Y DESTRUIR ELEMENTOS");
	pruebas_quitar_al_final();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR ELEMENTOS EN CUALQUIER POSICION");
	pruebas_quitar_en_cualquier_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR ELEMENTOS POR POSICION");
	pruebas_buscar_por_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR ELEMENTOS POR CONDICION");
	pruebas_buscar_por_condicion();

	pa2m_nuevo_grupo("PRUEBAS DEL ITERADOR INTERNO");
	pruebas_del_iterador_interno();

	pa2m_nuevo_grupo("PRUEBAS DE DESTRUIR TODOS LOS ELEMENTOS");
	pruebas_destruir_todos_los_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE PARAMETROS INVALIDOS");
	pruebas_de_lista_con_parametros_invalidos();
}

/*
-----------------------------------------------------------------------------
*/

void pruebas_de_creacion_y_destruccion_del_iterador_externo()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL, "Se puede crear el iterador");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
	printf("Destruir el iterador con exito no debe perder memoria\n");
}

void pruebas_del_iterador_externo_con_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
		     "No se encuentra elemento siguiente en una lista vacia");

	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "No se puede iterar una lista vacia");

	pa2m_afirmar(!lista_iterador_elemento_actual(iterador),
		     "No se encuentran elementos en una lista vacia");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void pruebas_de_avanzar_el_iterador_externo()
{
	lista_t *lista = lista_crear();
	int numeros[] = { 1, 2 };

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar(lista, &numeros[i]);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),
		     "Se encuentra el siguiente nodo a iterar");

	pa2m_afirmar(lista_iterador_avanzar(iterador),
		     "Se puede iterar al siguiente nodo");

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),
		     "Se encuentra otro nodo mas a iterar");

	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "Se puede iterar el nodo, y no hay mas nodos a iterar");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
		     "No se encuentran mas nodos para iterar");

	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "No se pueden iterar nodos que no existen");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void pruebas_de_mostrar_elementos_iterados()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = NULL;
	int numeros[] = { 1, 2, 3 };
	size_t i;

	for (i = 0; i < sizeof(numeros) / sizeof(int); i++)
		lista_insertar(lista, &numeros[i]);

	i = 0;
	for (iterador = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		void *elemento = lista_iterador_elemento_actual(iterador);
		pa2m_afirmar(elemento == &numeros[i],
			     "Se puede encontrar el elemento iterado");
		i++;
	}

	pa2m_afirmar(!lista_iterador_elemento_actual(iterador),
		     "No se encuentran elementos que no existen");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void pruebas_del_iterador_externo_de_la_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREAR Y DESTRUIR UN ITERADOR EXTERNO");
	pruebas_de_creacion_y_destruccion_del_iterador_externo();

	pa2m_nuevo_grupo("PRUEBAS DEL ITERADOR EXTERNO CON UNA LISTA VACIA");
	pruebas_del_iterador_externo_con_lista_vacia();

	pa2m_nuevo_grupo("PRUEBAS DE AVANZAR ELEMENTOS CON EL ITERADOR");
	pruebas_de_avanzar_el_iterador_externo();

	pa2m_nuevo_grupo("PRUEBAS DE MOSTRAR ELEMENTOS CON EL ITERADOR");
	pruebas_de_mostrar_elementos_iterados();
}

/*
-----------------------------------------------------------------------------
*/

void pruebas_operaciones_cola()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "Se pudo crear una cola");

	pa2m_afirmar(cola_vacia(cola) && !cola_tamanio(cola),
		     "La cola esta vacia");

	pa2m_afirmar(!cola_frente(cola), "La cola esta bien inicializada");

	int numeros[] = { 1, 2, 3, 4 };

	printf("\nEncolo los numeros:\n");
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		pa2m_afirmar(cola_encolar(cola, &numeros[i]) != NULL,
			     "Se pudo encolar un elemento");
		pa2m_afirmar(cola_tamanio(cola) == i + 1,
			     "La cola actualizo su tamanio correctamente");
	}

	pa2m_afirmar(!cola_vacia(cola) && cola_frente(cola) == &numeros[0],
		     "Se puede encontrar el primer elemento de la cola");

	printf("\nDesencolo los numeros y los muestro:\n");
	while (!cola_vacia(cola))
		pa2m_afirmar(cola_desencolar(cola) != NULL,
			     "Se pudo desencolar");

	printf("\n");

	pa2m_afirmar(cola_vacia(cola) && !cola_frente(cola),
		     "La cola quedo vacia");

	pa2m_afirmar(!cola_desencolar(cola),
		     "No se pueden desencolar elementos de una cola vacia");

	cola_destruir(cola);
}

void pruebas_de_cola_con_parametros_NULL()
{
	char a = 'a';

	pa2m_afirmar(!cola_encolar(NULL, &a),
		     "No se puede encolar en una cola inexistente");

	pa2m_afirmar(!cola_desencolar(NULL),
		     "No se puede desencolar de una cola inexistente");

	pa2m_afirmar(!cola_frente(NULL),
		     "No se puede leer el inicio de una cola inexistente");

	pa2m_afirmar(!cola_tamanio(NULL),
		     "El tamanio de una cola inexistente es 0");

	pa2m_afirmar(cola_vacia(NULL),
		     "Una cola inexistente es una cola vacia");
}

void pruebas_del_tda_cola()
{
	pa2m_nuevo_grupo("PRUEBAS DE LAS OPERACIONES DE UNA COLA");
	pruebas_operaciones_cola();

	pa2m_nuevo_grupo("PRUEBAS DE COLA CON PARAMETROS NULL");
	pruebas_de_cola_con_parametros_NULL();
}

/*
-----------------------------------------------------------------------------
*/

void pruebas_operaciones_pila()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "Se pudo crear una pila");

	pa2m_afirmar(pila_vacia(pila) && !pila_tamanio(pila),
		     "La pila esta vacia");

	pa2m_afirmar(!pila_tope(pila), "La pila esta bien inicializada");

	char *algo = "2ogla";

	int i;
	printf("\nApilo los elementos:\n");
	for (i = 0; algo[i] != 0; i++) {
		pa2m_afirmar(pila_apilar(pila, &algo[i]) != NULL,
			     "Se pudo encolar un elemento");
		pa2m_afirmar(pila_tamanio(pila) == i + 1,
			     "La pila actualizo su tamanio correctamente");
	}

	pa2m_afirmar(!pila_vacia(pila) && pila_tope(pila) == &algo[i - 1],
		     "Se puede encontrar el tope de la pila");

	printf("\nDesapilo y muestro los elementos apilados:\n");
	while (!pila_vacia(pila))
		pa2m_afirmar(pila_desapilar(pila) != NULL, "Se pudo desapilar");

	printf("\n");

	pa2m_afirmar(pila_vacia(pila) && !pila_tope(pila),
		     "La pila quedo vacia");

	pa2m_afirmar(!pila_desapilar(pila),
		     "No se pueden desapilar elementos de una pila vacia");

	pila_destruir(pila);
}

void pruebas_de_pila_con_parametros_NULL()
{
	char a = 'a';

	pa2m_afirmar(!pila_apilar(NULL, &a),
		     "No se puede apilar en una pila inexistente");

	pa2m_afirmar(!pila_desapilar(NULL),
		     "No se puede desapilar de una pila inexistente");

	pa2m_afirmar(!pila_tope(NULL),
		     "No se puede leer el tope de una pila inexistente");

	pa2m_afirmar(!pila_tamanio(NULL),
		     "El tamanio de una pila inexistente es 0");

	pa2m_afirmar(pila_vacia(NULL),
		     "Una pila inexistente es una pila vacia");
}

void pruebas_del_tda_pila()
{
	pa2m_nuevo_grupo("PRUEBAS DE LAS OPERACIONES DE UNA PILA");
	pruebas_operaciones_pila();

	pa2m_nuevo_grupo("PRUEBAS DE PILA CON PARAMETROS NULL");
	pruebas_de_pila_con_parametros_NULL();
}

/*
-----------------------------------------------------------------------------
*/

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	pruebas_del_tda_lista();
	printf("\n");

	pa2m_nuevo_grupo("---PRUEBAS DEL ITERADOR EXTERNO");
	pruebas_del_iterador_externo_de_la_lista();
	printf("\n");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-COLA ---");
	pruebas_del_tda_cola();
	printf("\n");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-PILA ---");
	pruebas_del_tda_pila();

	return pa2m_mostrar_reporte();
}