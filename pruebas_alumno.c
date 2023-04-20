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

int comparador(void *elemento, void*contexto)
{
	if (elemento == contexto)
		return 0;

	return ERROR;
}

void pruebas_creacion_y_destruccion()
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

	void *elemento1 = (void*)0x1234;

	pa2m_afirmar(lista_insertar(lista, elemento1) != NULL,
		     "Se puede insertar un elemento al final de la lista");

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "Se puede insertar NULL al final de la lista");

	lista_destruir(lista);
}

void pruebas_leer_lista()
{
	lista_t *lista = lista_crear();

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);

	pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");

	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "Se insertan 2 elementos, y el tamanio es 2");

	pa2m_afirmar(lista_primero(lista) == elemento1,
		     "Se puede leer el primer elemento de la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento2,
		     "Se puede leer el ultimo elemento de la lista");

	lista_destruir(lista);
}

void pruebas_insertar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd', w = 'w';
	char *valor;

	pa2m_afirmar(lista_insertar_en_posicion(lista, &a, 0) != NULL,
		     "Se inserta el primer elemento");

	pa2m_afirmar(!lista_vacia(lista) && lista_tamanio(lista) == 1,
		     "Se inserto 1 elemento");

	valor = lista_primero(lista);
	printf("El primer elemento es %c\n", *valor);
	pa2m_afirmar(lista_primero(lista) == &a, "El primer elemento es a");

	valor = lista_ultimo(lista);
	printf("El ultimo elemento es %c\n", *valor);
	pa2m_afirmar(lista_ultimo(lista) == &a, "El ultimo elemento es a");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &a,
		     "Se puede buscar el primer elemento, es a");


	printf("\n\n\n");

	
	pa2m_afirmar(lista_insertar_en_posicion(lista, &b, 100) != NULL,
		     "Se inserta segundo elemento en posicion inexistente");

	pa2m_afirmar(!lista_vacia(lista) && lista_tamanio(lista) == 2,
		     "Se insertaron 2 elementos");

	valor = lista_primero(lista);
	printf("El primer elemento es %c\n", *valor);
	pa2m_afirmar(lista_primero(lista) == &a, "El primer elemento es a");

	valor = lista_ultimo(lista);
	printf("El ultimo elemento es %c\n", *valor);
	pa2m_afirmar(lista_ultimo(lista) == &b, "El ultimo elemento es b");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &b,
		     "Se puede buscar el segundo elemento, es b");


	printf("\n\n\n");

	
	pa2m_afirmar(lista_insertar_en_posicion(lista, &c, 1) != NULL,
		     "Se inserta tercer elemento en ultima posicion");

	pa2m_afirmar(!lista_vacia(lista) && lista_tamanio(lista) == 3,
		     "Se insertaron 3 elementos");

	valor = lista_primero(lista);
	printf("El primer elemento es %c\n", *valor);
	pa2m_afirmar(lista_primero(lista) == &a, "El primer elemento es a");

	valor = lista_ultimo(lista);
	printf("El ultimo elemento es %c\n", *valor);
	pa2m_afirmar(lista_ultimo(lista) == &b, "El ultimo elemento es b");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &c,
		     "Se puede buscar el segundo elemento, ahora es c");





	

	lista_insertar_en_posicion(lista, &d, 3);
	lista_insertar_en_posicion(lista, &w, 4);

	lista_destruir(lista);
}

void pruebas_quitar_al_final()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar(lista),
		     "No se pueden quitar elementos de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);

	pa2m_afirmar(lista_quitar(lista) == elemento2,
		     "Se pueden quitar elementos del final de la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento1 &&
		     lista_tamanio(lista) == 1, "Se reajusta bien la lista");


	pa2m_afirmar(lista_quitar(lista) == elemento1,
		     "Se pueden quitar elementos de una lista con un solo elemento");

	pa2m_afirmar(!lista_tamanio(lista) && lista_vacia(lista),
		     "Se eliminan todos los elementos y la lista queda vacia");

	pa2m_afirmar(!lista_primero(lista) && !lista_ultimo(lista),
		     "Se reajusta bien la lista vacia");

	lista_destruir(lista);
}

void pruebas_quitar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar_de_posicion(lista, 0),
		     "No se pueden quitar elementos de cualquier posicion de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;
	void *elemento3 = (void*)0x1234;
	void *elemento4 = (void*)0x4321;
	void *elemento5 = (void*)0x4321;

	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);
	lista_insertar(lista, elemento3);
	lista_insertar(lista, elemento4);
	lista_insertar(lista, elemento5);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == elemento1,
		     "Se puede quitar el primer elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 1) == elemento3,
		     "Se pueden quitar elementos del medio de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == elemento5,
		     "Se puede quitar el ultimo elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 100) == elemento4,
		     "Se pueden quitar elementos de una posicion inexistente");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == elemento2,
		     "Se puede quitar el unico elemento de la lista");


	pa2m_afirmar(!lista_tamanio(lista) && lista_vacia(lista),
		     "Se eliminan todos los elementos y la lista queda vacia");

	pa2m_afirmar(!lista_primero(lista) && !lista_ultimo(lista),
		     "Se reajusta bien la lista vacia");

	lista_destruir(lista);
}

void pruebas_buscar_por_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "No se pueden buscar elementos de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;
	void *elemento3 = (void*)0x1234;

	lista_insertar_en_posicion(lista, elemento1, 0);
	lista_insertar_en_posicion(lista, elemento2, 1);
	lista_insertar_en_posicion(lista, elemento3, 2);

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == elemento1,
		     "Se puede encontrar el primer elemento de la lista");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == elemento2,
		     "Se pueden encontrar elementos en el medio de la lista");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == elemento3,
		     "Se puede encontrar el ultimo elemento de la lista");

	lista_destruir(lista);
}

void pruebas_buscar_por_condicion()
{
	lista_t *lista = lista_crear();

	void *contexto = (void*)0x4321;

	pa2m_afirmar(!lista_buscar_elemento(lista, comparador, contexto),
		     "No se puede buscar un elemento con cualquier condicion de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;
	void *elemento3 = (void*)0x1234;

	lista_insertar_en_posicion(lista, elemento1, 0);
	lista_insertar_en_posicion(lista, elemento2, 1);
	lista_insertar_en_posicion(lista, elemento3, 2);

	pa2m_afirmar(lista_buscar_elemento(lista, comparador, contexto) == elemento2,
		     "Se puede buscar un elemento con cualquier condicion de una lista");

	pa2m_afirmar(lista_buscar_elemento(lista, comparador, NULL) == NULL,
		     "No encontrar el elemento devuelve NULL");

	lista_destruir(lista);
}
/*
void pruebas_destruir_todos_los_elementos()
{
	lista_t *lista = lista_crear();

	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(float)));
	lista_insertar(lista, malloc(sizeof(long)));
	lista_insertar(lista, malloc(sizeof(char)));
	lista_insertar(lista, malloc(sizeof(pkm_para_destruir_t)));

	lista_destruir_todo(lista, free);

	return;
}
*/
void pruebas_de_lista_con_parametros_invalidos()
{
	lista_t *lista = lista_crear();

	void *elemento = (void*)0x1234;
	void *contexto = (void*)0x4321;

	pa2m_afirmar(!lista_insertar(NULL, elemento),
		     "No se puede insertar un elemento a una lista que no existe");

	pa2m_afirmar(!lista_insertar_en_posicion(NULL, elemento, 0),
		     "No se puede insertar un elemento en cualquier posicion a una lista que no existe");

	pa2m_afirmar(!lista_quitar(NULL),
		     "No se puede quitar un elemento de una lista que no existe");

	pa2m_afirmar(!lista_quitar_de_posicion(NULL, 0),
		     "No se puede quitar un elemento de cualquier posicion de una lista que no existe");

	pa2m_afirmar(!lista_elemento_en_posicion(NULL, 0),
		     "No se puede buscar un elemento de cualquier posicion de una lista que no existe");

	pa2m_afirmar(!lista_buscar_elemento(NULL, comparador, contexto),
		     "No se puede buscar un elemento con cualquier condicion de una lista que no existe");

	pa2m_afirmar(!lista_buscar_elemento(lista, NULL, elemento),
		     "No se puede buscar un elemento de una lista con una funcion comparador que no existe");

	lista_destruir(lista);
}

void pruebas_del_tda_lista()
{/*
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR Y DESTRUIR ELEMENTOS");
	pruebas_insertar_y_destruir();

	pa2m_nuevo_grupo("PRUEBAS DE LEER UNA LISTA");
	pruebas_leer_lista();
*/
	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR EN CUALQUIER POSICION");
	pruebas_insertar_en_cualquier_posicion();
/*
	pa2m_nuevo_grupo("PRUEBAS DE QUITAR Y DESTRUIR ELEMENTOS");
	pruebas_quitar_al_final();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR ELEMENTOS EN CUALQUIER POSICION");
	pruebas_quitar_en_cualquier_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR ELEMENTOS POR POSICION");
	pruebas_buscar_por_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR ELEMENTOS POR CONDICION");
	pruebas_buscar_por_condicion();

	//pa2m_nuevo_grupo("PRUEBAS DE DESTRUIR TODOS LOS ELEMENTOS");
	//pruebas_destruir_todos_los_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE PARAMETROS INVALIDOS");
	pruebas_de_lista_con_parametros_invalidos();
*/
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
		pa2m_afirmar(pila_desapilar(pila) != NULL,
			     "Se pudo desapilar");

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

void pruebas_del_iterador_externo_de_la_lista()
{
	lista_t * lista = lista_crear();	
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL, "Se puede crear el iterador");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
	             "No se encuentran elementos a iterar en una lista vacia");

	pa2m_afirmar(!lista_iterador_avanzar(iterador),
	             "No se puede iterar una lista vacia");

	pa2m_afirmar(!lista_iterador_elemento_actual(iterador),
	             "No se encuentran elementos en una lista vacia");

	//char a = 'a', b = 'b', c = 'c', d = 'd', w = 'w';
	//char *valor;	

	lista_iterador_destruir(iterador);
}

/*
-----------------------------------------------------------------------------
*/

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	//pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	//pruebas_del_tda_lista();
	//printf("\n");

	pa2m_nuevo_grupo("---PRUEBAS DEL ITERADOR EXTERNO");
	pruebas_del_iterador_externo_de_la_lista();
	printf("/n");
/*
	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-COLA ---");
	pruebas_del_tda_cola();
	printf("\n");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-PILA ---");
	pruebas_del_tda_pila();
*/
	return pa2m_mostrar_reporte();
}

/*
pa2m_afirmar(lista_insertar_en_posicion(lista, elemento1, 0) != NULL,
		     "Se puede insertar al principio de una lista vacia");

	pa2m_afirmar(lista_primero(lista) == elemento1,
		     "El elemento ingresado es el primero en la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento1,
		      "El elemento ingresado es el ultimo en la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento2, 1) != NULL,
		     "Se puede insertar a continuacion del primer elemento");

	pa2m_afirmar(lista_ultimo(lista) == elemento2,
		      "Ahora el segundo elemento ingresado es el ultimo de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento2, 0) != NULL,
		     "Se puede insertar otra vez al principio de la lista");

	pa2m_afirmar(lista_primero(lista) == elemento2,
		     "Ahora el tercer elemento ingresado es el primero de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento1, 100) != NULL,
		     "Se puede insertar un elemento en una posicion inexistente");

	pa2m_afirmar(lista_ultimo(lista) == elemento1,
		      "El elemento ingresado ahora es el ultimo de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 2) != NULL,
		     "Se puede insertar NULL cualquier posicion");
	
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se insertaron 5 elementos, y el tamanio es 5");
*/