#include "pa2m.h"

#include "src/lista.h"

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

	return;
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

	return;
}

void pruebas_insertar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

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

	lista_destruir(lista);

	return;
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

	return;
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

	return;
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

	return;
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

	return;
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
void pruebas_parametros_invalidos()
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

	return;
}

void pruebas_de_la_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_creacion_y_destruccion();

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

	//pa2m_nuevo_grupo("PRUEBAS DE DESTRUIR TODOS LOS ELEMENTOS");
	//pruebas_destruir_todos_los_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE PARAMETROS INVALIDOS");
	pruebas_parametros_invalidos();

	return;
}

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	pruebas_de_la_lista();

	return pa2m_mostrar_reporte();
}
