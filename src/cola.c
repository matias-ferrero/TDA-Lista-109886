#include "cola.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct _cola_t {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad_nodos;
};


cola_t *cola_crear()
{
	return calloc(1, sizeof(cola_t));
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola)
		return NULL;

	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;

	if (cola_vacia(cola))
		cola->nodo_inicio = nodo;
	else
		cola->nodo_fin->siguiente = nodo;

	cola->nodo_fin = nodo;
	cola->cantidad_nodos++;
	nodo->elemento = elemento;

	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola || cola_vacia(cola))
		return NULL;

	nodo_t *nodo_a_desencolar = cola->nodo_inicio;
	void *elemento = cola->nodo_inicio->elemento;

	if (cola_tamanio(cola) == 1) {
		cola->nodo_inicio = NULL;
		cola->nodo_fin = NULL;
	} else
		cola->nodo_inicio = nodo_a_desencolar->siguiente;
	
	free(nodo_a_desencolar);
	cola->cantidad_nodos--;

	return elemento;
}

void *cola_frente(cola_t *cola)
{
	if (!cola)
		return NULL;

	return cola->nodo_inicio;
}

size_t cola_tamanio(cola_t *cola)
{
	if (!cola)
		return 0;

	return cola->cantidad_nodos;
}

bool cola_vacia(cola_t *cola)
{
	if (!cola || !cola_tamanio(cola))
		return true;

	return false;
}

void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;

	while (cola_tamanio(cola) != 0) {
		nodo_t *nodo_a_destruir = cola->nodo_inicio;
		cola->nodo_inicio = nodo_a_destruir->siguiente;
		free(nodo_a_destruir);
		cola->cantidad_nodos--;
	}

	free(cola);

	return;
}
