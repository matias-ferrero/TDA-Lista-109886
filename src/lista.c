#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	//algo mas?
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if (!lista)
		return NULL;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista || !elemento)
		return NULL;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista || !elemento)
		return NULL;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista)
		return NULL;

	return;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista)
		return NULL;

	return;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista) //Comprobar posicion
		return NULL;

	return;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador || !contexto)
		return NULL;

	return;
}

void *lista_primero(lista_t *lista)
{
	if (!lista)
		return NULL;

	return;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista)
		return NULL;

	return;
}

bool lista_vacia(lista_t *lista)
{
	if (!lista)
		return true;

	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;

	return 0;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	free(lista);

	return;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista || !funcion)
		return;

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

	return;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return NULL;

	return;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista  || !funcion || !contexto)
		return 0;

	return 0;
}
