#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad_nodos;
	//algo mas?
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;

	if (lista->cantidad_nodos == 0)
		lista->nodo_inicio = nodo;
	else
		lista->nodo_fin->siguiente = nodo;

	lista->nodo_fin = nodo;
	lista->cantidad_nodos++;

	nodo->elemento = elemento;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;

	if (posicion == 0) {
		nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo;
	} else if (posicion < lista->cantidad_nodos) {
		nodo->siguiente = lista->nodo_inicio->siguiente;
		lista->nodo_inicio->siguiente = nodo;
	} else 
		lista->nodo_fin->siguiente = nodo;

	if (!nodo->siguiente)
		lista->nodo_fin = nodo;

	lista->cantidad_nodos++;

	nodo->elemento = elemento;

	return lista;
}

nodo_t *buscar_nodo_anterior_a_quitar(nodo_t *nodo, size_t posicion_en_lista,
				      size_t posicion_buscada)
{
	if (posicion_buscada != posicion_en_lista)
		nodo = buscar_nodo_anterior_a_quitar(nodo->siguiente,
			 posicion_en_lista++, posicion_buscada);

	return nodo;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_vacia(lista))
		return NULL;
	
	nodo_t *nodo = lista->nodo_fin;;

	if (lista->nodo_inicio == lista->nodo_fin) {
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	} else {
		nodo_t *nuevo_ultimo_nodo = 
			buscar_nodo_anterior_a_quitar(lista->nodo_inicio,
			 0, lista->cantidad_nodos - 2);
		lista->nodo_fin = nuevo_ultimo_nodo;
		nuevo_ultimo_nodo->siguiente = NULL;
	}
	lista->cantidad_nodos--;
	return nodo; 
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	nodo_t *nodo = NULL;
	if (lista->nodo_inicio == lista->nodo_fin ||	//Unico elemento en la lista o ultima posicion
		 posicion >= (lista->cantidad_nodos - 1)) 
		nodo = lista_quitar(lista);
	else if (posicion == 0) {			//Primera posicion
		nodo = lista->nodo_inicio;
		lista->nodo_inicio = nodo->siguiente;
	} else {
		nodo_t *nodo_anterior_a_quitar =	//Todas las posiciones restantes
		 buscar_nodo_anterior_a_quitar(lista->nodo_inicio, 0, posicion--);
		nodo = nodo_anterior_a_quitar->siguiente;
		nodo_anterior_a_quitar->siguiente = nodo->siguiente;
	}

	lista->cantidad_nodos--;

	return nodo;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista) //Comprobar posicion
		return NULL;

	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador || !contexto)
		return NULL;

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista || lista->cantidad_nodos == 0)
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || lista->cantidad_nodos == 0)
		return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (!lista || lista->cantidad_nodos == 0)
		return true;

	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;

	return lista->cantidad_nodos;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	while (lista->cantidad_nodos != 0) {
		nodo_t *nodo_aux = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
		lista->cantidad_nodos--;
	}

	free(lista);

	return;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista || !funcion)
		return;

	while (lista->cantidad_nodos != 0) {
		nodo_t *nodo_aux = lista->nodo_inicio->siguiente;
		funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
		lista->cantidad_nodos--;
	}

	free(lista);

	return;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;

	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador)
		return NULL;

	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return;

	return;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista  || !funcion || !contexto)
		return 0;

	return 0;
}
