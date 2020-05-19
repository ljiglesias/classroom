//**************************************************************//
/* *****************
* Ayudantia 2 
* Punteros
* Ejemplo basico
* 
*
* Autor: Camila Turrieta
* 
*/
//**************************************************************//

#include <stdio.h>

int main()
{
    int i;    //definimos una variable tipo entero
    int *ptr; //definimos un puntero. Este apunta a un entero

    //vamos a hacer que el puntero apunte al valor de i
    ptr = &i; //de esta forma se guarda en el puntero la dirección 

    //ahora puedo asignar el valor de i de dos formar 
    i = 10; //forma directa y convencional 
    printf("vamos a llamar a i de manera directa: ");
    printf("%i",i);
    printf("\n");
    *ptr = 20; //forma indirecta
    printf("vamos a llamar a i de manera indirecta: ");
    printf("%i",i);
    printf("\n");
    printf("y la direccion almacenada de i en puntero es: ");
    printf("%p",ptr);
    printf("\n");



    //Ejemplo de recorrer una lista con punteros
    printf("\n------------------------------------------ \n");
    printf("Ejemplo: \n \n");

    char *string = "HOLA"; //Asignación de un arreglo de chars mediante punteros
    //Forma de recorrer esta lista
    while(*string != 0x00){
        printf("Direccion: %p\n", string);
        printf("Valor: %c\n", *string);
        string++;
    }

    //Ejemplo de recorrer un arreglo sin punteros
    printf("\n------------------------------------------ \n");
    printf("Ejemplo: \n \n");
    int numeros[8] = {0,1,2,3,4,5,6,7};
    int indice = 0;
    while(indice != 8){
        printf("Valor: %i\n", numeros[indice]);
        indice++;
    }
    return 0;
}