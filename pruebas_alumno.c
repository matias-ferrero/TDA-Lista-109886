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
	 	     lista_ultimo(lista) == NULL &&
		     lista_vacia(lista) == true,
	  	     "La lista esta vacia");

	lista_destruir(lista);

	return;
}

void pruebas_parametros_invalidos()
{
	void *elemento = (void*)0x1234;

	pa2m_afirmar(lista_insertar(NULL, elemento) == NULL,
		     "No se puede insertar un elemento a una lista que no existe");

	pa2m_afirmar(lista_insertar_en_posicion(NULL, elemento, 0) == NULL,
		     "No se puede insertar en cualquier posicion a una lista que no existe");
}

void pruebas_insertar_al_final()
{
	lista_t *lista = lista_crear();
	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	pa2m_afirmar(lista_insertar(lista, elemento1) != NULL,
		     "Se puede insertar un elemento al final de la lista");

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "Se puede insertar NULL al final de la lista");

	lista_insertar(lista, elemento2);

	pa2m_afirmar(lista_primero(lista) == elemento1,
		     "El primer elemento ingresado es el primero en la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento2,
		      "El ultimo elemento ingresado es el ultimo en la lista");

	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "Se insertaron 3 elementos, y el tamanio es 3");

	lista_destruir(lista);
}

void pruebas_insertar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();
	void *elemento = (void*)0x1234;

	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 0) != NULL,
		     "Se puede insertar un elemento al principio de la lista");

	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 1) != NULL,
		     "Se puede insertar un elemento a continuacion del primero");

	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 2) != NULL,
		     "Se puede insertar NULL cualquier posicion");

	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento, 100) != NULL,
		     "Se puede insertar un elemento en una posicion inexistente");

	lista_destruir(lista);

	return;
}

void pruebas_de_la_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE PARAMETROS INVALIDOS");
	pruebas_parametros_invalidos();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR AL FINAL");
	pruebas_insertar_al_final();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR EN CUALQUIER POSICION");
	pruebas_insertar_en_cualquier_posicion();

	return;
}

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	pruebas_de_la_lista();

	return pa2m_mostrar_reporte();
}
