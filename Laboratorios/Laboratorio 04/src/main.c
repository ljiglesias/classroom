/*
Name: Simon SEP

Author: Felipe Sanchez

Referencias:
    Interfaz basado en Juego Tic Tac Toe, Tutorial GTK 3 Programming with C and Glade
    https://www.youtube.com/watch?v=reQ4CeeEBYM&list=PLaybP4QvyRH1obigtMQwhB2DWhPKg32_T&index=21

    Basado en Juego SIMON, creado originalmente por 
    BAER RALPH H [US]; MORRISON HOWARD J [US]

    B. Ralph H and M. Howard J, "Microcomputer controlled game";
    U.S. Patent US4207087A, June 10, 1980. 
    
*/

#include <gtk/gtk.h>
#include "game_logic.h"
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

// Required for use in Windows. For user in Linux/MAC it isn't necessary

G_MODULE_EXPORT void on_btn_0_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_1_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_2_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_3_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_4_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_5_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_6_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_btn_7_clicked(GtkButton *button, app_widgets *app_wdgts);

G_MODULE_EXPORT void on_new_game_btn_clicked(GtkButton *button, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_rb_0_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_rb_1_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts);
G_MODULE_EXPORT void on_rb_2_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts);

gboolean timer_handler_1(app_widgets *app_wdgts);
gboolean timer_handler_2(app_widgets *app_wdgts);
gboolean update_score(app_widgets *app_wdgts, gint value);
gboolean update_max_score(app_widgets *app_wdgts, gint value);
void set_text_end_game(app_widgets *app_wdgts);

int main(int argc, char *argv[]){

    GtkBuilder      *builder; 
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);
    gchar           str_img[] = "img_0";    // For accessing images from Glade file

    // Initialize variables of game
    widgets->turn = TRUE;                   // O turn (FALSE is X turn)
    widgets->gm_state = GM_INIT;            // Game state is initially busy
    widgets->gm_mode = GM_LinBuff;
    widgets->value = 0;
    widgets->max_value = 0;
    widgets->show_value = 0;
    widgets->timeout_img = 35;

    // Serie pseudoaleatoria inicial
    g_snprintf(widgets->game_show,10, "%s", "023130132");

    gtk_init(&argc, &argv);

    // Initialize window created with glade
    builder = gtk_builder_new_from_file("glade/main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    // Close the program when X is pressed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Get a pointer to each image
    for (gint i = 0; i < 4; i++) {
        str_img[4] = i + '0';
        widgets->w_img[i] = GTK_WIDGET(gtk_builder_get_object(builder, str_img));
        // Reset game board
        widgets->game_board[i] = 'x';
        widgets->game_board_timeout[i] = 0;
    }
    // Get a pointer to the status label
    widgets->w_lbl_status = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status"));
    // Get a pointer to the score label
    widgets->w_lbl_score = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_score"));
    // Get a pointer to the max score label
    widgets->w_lbl_max_score = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_score_max"));
    // Get a pointer to the choice label
    widgets->w_lbl_choice = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_choice"));


    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    // Timer that checks every 800 ms to reset the game images
    // Emulate the turn on off 
    gint timer_1 = g_timeout_add_full(G_PRIORITY_HIGH, 800, (GSourceFunc)timer_handler_1, widgets, NULL);
    // Timer that execute every 10 ms a request to a function
    gint timer_2 = g_timeout_add(10, (GSourceFunc)timer_handler_2, widgets);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
    g_source_remove (timer_1);
    g_source_remove (timer_2);


    return 0;
}


// Button clicked handler function shared by all buttons in grid
void on_btn_0_clicked(GtkButton *button, app_widgets *app_wdgts)
{

    player_round(app_wdgts, 0);
    update_score(app_wdgts, app_wdgts->value);

}

void on_btn_1_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    player_round(app_wdgts, 1);
    update_score(app_wdgts, app_wdgts->value);
}

void on_btn_2_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    player_round(app_wdgts, 2);
    update_score(app_wdgts, app_wdgts->value);

}



void on_btn_3_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    player_round(app_wdgts, 3);
    update_score(app_wdgts, app_wdgts->value);

}

void on_new_game_btn_clicked(GtkButton *button, app_widgets *app_wdgts){
    printf("New game btn clicked\n");

    // Se apagan todas las imagenes y se guarda el valor como apagado
    gchar       str_img[] = "res/0.png";
    for (gint i = 0; i < 4; i++){
        str_img[4] = i + '0';
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[i]), str_img);
        app_wdgts->game_board[i] = 'x';
    }

    /*
    Se considera new game como el ultimo valor de value obtenido
    Aqui se deberia hacer un control para determinar si el valor 
    de max_score debe ser actualizado o no.
    */

    app_wdgts->max_value = app_wdgts->value;

    // Actualiza el max score
    update_max_score(app_wdgts, app_wdgts->max_value);

    // Reset all values
    app_wdgts->value = 0;
    app_wdgts->gm_state = GM_SHOW;
    update_score(app_wdgts, app_wdgts->value);

    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "El juego ha comenzado");


    // Deberia modificarse si se desean agregar nuevas opciones


}

void set_text_end_game(app_widgets *app_wdgts){
	// Ejemplo Funcion para cambiar el nombre del status a perdido

	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "Has perdido :(");
}


gboolean timer_handler_1(app_widgets *app_wdgts){
    // Timer 1 funciona a 2 Hz para actualizar info
    if (app_wdgts->gm_state == GM_SHOW){
        show_mem_function(app_wdgts->game_show, app_wdgts);
    }
    else{
        g_print("Aun no es tiempo\n");
    }
    return TRUE;
}

gboolean timer_handler_2(app_widgets *app_wdgts){

    // Revisa la iluminación de las imágenes
    gchar       str_img[] = "res/0.png";
    for (gint i = 0; i < 4; i++){
        if (app_wdgts->game_board_timeout[i] > 0){
            app_wdgts->game_board_timeout[i]--;
            printf("Time out img_%d is %d\n",i,app_wdgts->game_board_timeout[i]);
        }
        else{
            str_img[4] = i + '0';
            if (app_wdgts->game_board[i] == 'o'){
                gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[i]), str_img);
                app_wdgts->game_board[i] = 'x';
            }
        }
    }
    return TRUE;
}

gboolean update_score(app_widgets *app_wdgts, gint value){
    gchar update_value[10];
    g_snprintf(update_value,8, "%d", value);
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_score), update_value);
}

gboolean update_max_score(app_widgets *app_wdgts, gint value){
    gchar update_value[10];
    g_snprintf(update_value,8, "%d", value);
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_max_score), update_value);
}

// Botones que permiten escoger el modo de juego.
void on_rb_0_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts)
{
    g_print("Button 1 Toggled\n");       // print to command line
    app_wdgts->gm_mode = GM_LinBuff;
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_choice), "Linear Buffer");
}

void on_rb_1_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts)
{
    g_print("Button 2 Toggled\n");
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_choice), "Ring Buffer");
    app_wdgts->gm_mode = GM_RingBuff;
}

void on_rb_2_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts)
{
    g_print("Button 3 Toggled\n");
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_choice), "Linked List");
    app_wdgts->gm_mode = GM_LinkList;
}

// Los siguientes son botones en caso que estime conveniente usarlos

void on_btn_4_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    // Rellenar con funciones 

    /* 
    En este instante, este boton es para efectos de debugueo.
    Imprime en consola que estado se encuentra el buffer.

    */
       g_print("Button 4 Toggled\n");

    // Funcion de prueba de game_mode

       switch (app_wdgts->gm_mode){
        case GM_LinBuff:
            g_print("Modo de juego LinBuff\n");
            break;
        case GM_RingBuff:
            g_print("Modo de juego Ring Buffer\n");
            break;
        case GM_LinkList:
            g_print("Modo de juego Link List\n");
            break;

        default:
            g_print("Modo de juego LinBuff\n");
    }


}

void on_btn_5_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    // Rellenar con funciones 
    /*
    En estos momentos la funcion muestra cual es la serie a mostrar 
    que se encuentra guardada en app_wdgts->game_show
    */
    g_print("Button 5 Toggled\n");
    g_print("Series %s\n", app_wdgts->game_show);
}

void on_btn_6_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    // Rellenar con funciones 
    g_print("Button 6 Toggled\n");
    /*
    En estos momentos la funcion esta para debuggeo en un modo "manual"
    de mostrar los cuadros, es por eso que llama a la funcion show_mem_function
    */
    show_mem_function(app_wdgts->game_show, app_wdgts);

}

void on_btn_7_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    // Rellenar con funciones 
    g_print("Button 7 Toggled\n");

    /*
    Actualmente, es una forma manual de iniciar un modo de muestra de imagenes
    */
    app_wdgts->gm_state = GM_SHOW;

}