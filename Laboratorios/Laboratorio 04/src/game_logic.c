#include <gtk/gtk.h>
#include "game_logic.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LARGO 20
gchar game_input[LARGO];



// Returns the state of the game as either busy
game_state get_game_state(app_widgets *app_wdgts, gchar button)
{
    // Determina si el estado debe cambiar de BUSY -> SHOW -> END
}

void player_round(app_widgets *app_wdgts, gint img_index){
	/*
	Recibe como parametro la estructura app_widgets con el puntero *app_wdts
	img es el número de imagen a modificar.
	*/

	// Las siguientes lineas son para cambiar de imagen al presionar
	if (app_wdgts->gm_state == GM_BUSY){

		press_img_x(app_wdgts, img_index);
		printf("Imagen presionada %d \n", img_index);

	}
	else{
		printf("Aun no ha comenzado el juego\n");
	}

	/* 
	En este espacio, se debería implementar la logica del juego  
	*/ 

	// El siguiente valor solo aumenta el contador de cuantas veces fue presionado
	app_wdgts->value++;


}


void press_img_x(app_widgets *app_wdgts, gint img_index){
	/* 
	Funcion que controla que imagen fue presionada y realiza la animacion
	correspondiente, recibe como parametros una estructra e indices.
	*/

	gchar       str_img[] = "res/0_on.png";
	// Cambio del nombre de string (sumar 0 es una conversion de int a char)
	str_img[4] = img_index + '0';
	// Actualizacion del estado de la imagen
    app_wdgts->game_board[img_index] = 'o';
    // timeout_img es el tiempo por el que la imagen se mantendra "encendida"
    app_wdgts->game_board_timeout[img_index] = app_wdgts->timeout_img;
    // Actualizacion de imagen
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[img_index]), str_img);


}


void show_mem_function(gchar *array, app_widgets *app_wdgts){
	/* Prototipo de funcion para mostrar los cambios.
	En esta debería estar implementado que muestre los valores dependiendo 
	del tipo de buffer que fue utilizado
	*/
	if (app_wdgts->gm_state == GM_SHOW){
		printf("%d\n",app_wdgts->show_value);
		printf("siguiente: %c\n",array[app_wdgts->show_value]);
		
		press_img_x(app_wdgts, array[app_wdgts->show_value] - '0');


		app_wdgts->show_value++;
		if (app_wdgts->show_value > 8){
			app_wdgts->show_value = 0;
			app_wdgts->gm_state = GM_BUSY;
			printf("Ciclo terminado\n");
		}
	}
	else{
		printf("No es el momento de mostrar\n");
	}

}