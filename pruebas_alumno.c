#include "pa2m.h"

#include "src/lista.h"

#include <stdio.h>
#include <stdlib.h>

void pruebas_creacion_y_destruccion()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear una lista correctamente");

	pa2m_afirmar(lista_tamanio(lista) == 0 &&
	 	     lista_primero(lista) == NULL &&
	 	     lista_ultimo(lista) == NULL,
	  	     "La lista esta vacia");

	lista_destruir(lista);

	return;
}

void pruebas_insertar_y_quitar_elementos()
{
	lista_t *lista = lista_crear();
	void *elemento = (void*)0x1234;

	pa2m_afirmar(lista_insertar(lista, elemento) != NULL,
		     "Se puede insertar un elemento al final de la lista");

	pa2m_afirmar(lista_insertar(NULL, elemento) == NULL,
		     "No se puede insertar un elemento a una lista que no existe");

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "Se puede insertar NULL al final de la lista");

	//pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 0) != NULL,
	//	     "Se puede insertar NULL al final de la lista");

	lista_destruir(lista);

	return;
}

void pruebas_de_la_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR Y QUITAR ELEMENTOS");
	pruebas_insertar_y_quitar_elementos();

	return;
}

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	pruebas_de_la_lista();

	return pa2m_mostrar_reporte();
}
