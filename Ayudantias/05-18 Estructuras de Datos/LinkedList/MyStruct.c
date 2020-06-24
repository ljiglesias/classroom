//**************************************************************//
/* *****************
* Ayudantia 2 
* Estructuras
* Ejemplo basico
* 
*
* Autor: Camila Turrieta 
* Referencia: 
* https://es.wikibooks.org/wiki/Programación_en_C/Estructuras_y_Uniones
*/
//**************************************************************//

// Librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Libreria standar

// Estructuras

	// Definición
	struct mystruct
	{
		//Atributos
		int int_member;
		double double_member;
		char string_member[25];
		int otro_int;
	};

	struct persona
	{
		char name[10];
		int edad;
	};

void main (void)
{

//**************************************************************//
// Trabajando con estructuras

	// Definicion
	struct mystruct struct1;

	// Asigno valores
	struct1.int_member = 1;
	struct1.double_member = 2.5;
	strcpy(struct1.string_member, "Juanito");

	// Print - llamar valores
	printf("\n La estructura \n");
	printf("\n Primer elemento: %i", struct1.int_member);
	printf("\n Segundo elemento: %d", struct1.double_member);
	printf("\n Tercer elemento: %s",struct1.string_member);
	printf("\n \n");

	// Definicion
	struct persona persona1;
	// Asigno valores
	strcpy(persona1.name,"Jorge");
	persona1.edad = 10;
	// Print
	printf("\n Estructura persona \n");
	printf("\n Persona: %s", persona1.name);
	
}
