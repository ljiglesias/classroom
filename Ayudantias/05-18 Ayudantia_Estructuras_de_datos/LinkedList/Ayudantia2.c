//**************************************************************//
/* *****************
* Ayudantia 2 
* Linked list
* Uso basico
*
* Autor: Camila Turrieta
* 
*/
//**************************************************************//

// Librerias 

#include <stdio.h>  // Libreria standar
#include <string.h> //Libreria de strings 
#include <stdlib.h> // Libreria standar


	struct Nodo
	{
		int dato;
		struct nodo *next;
		
	};

	void NuevoDato(int NewDato, struct Nodo * NoditoHead);
	void LinkedList_print(struct Nodo * Nodito);

void main()
{
	// Creamos el primer nodo
	struct Nodo * Nodo1 = NULL;
	// Asignamos espacio en la ram
	Nodo1 = malloc(sizeof(struct Nodo));
	// Definimos el primer valor
	Nodo1->dato =  1;

	Nodo1->next =  NULL;


	// Anexamos un nuevo dato
	NuevoDato(5,Nodo1);

	// Mas ejemplo
	NuevoDato(6,Nodo1);
	NuevoDato(7,Nodo1);
	NuevoDato(8,Nodo1);
	NuevoDato(9,Nodo1);

	// Print - recorro la linked list
	LinkedList_print(Nodo1);

}



void NuevoDato(int NewDato, struct Nodo * NoditoHead)
{
	// Creamos nuevo nodo
	struct Nodo * NodoNew  =  NULL;
	NodoNew = malloc(sizeof(struct Nodo));

	// Asignamos el valor
	NodoNew->dato = NewDato;

	// Nodo auxiliar 
	struct Nodo * auxiliar = NULL;
	// ram
	auxiliar = malloc(sizeof(struct Nodo));

	auxiliar = NoditoHead;

	while (auxiliar->next != NULL){
		auxiliar = auxiliar->next;
	}

	// Linkear
	auxiliar->next = NodoNew;

	// Nuevo final
	NodoNew->next =  NULL;

	// Eliminar 
	auxiliar = NULL;

	free(auxiliar);


}

void LinkedList_print(struct Nodo * Nodito)
{
	// Nodo temporal auxiliar
	struct Nodo * aux = NULL;
	aux = malloc(sizeof(struct Nodo));

	aux = Nodito;

	// Print hasta el ultimo nodo
	while (aux != NULL){
		printf("\n Nodo dato = %i ",aux->dato);
		aux = aux->next;
	}
	printf("\n \n");

	// Eliminar nodo auxiliar
	free(aux);
}