#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Game can be in one of 4 states:
// Init:	Initial condition of game
// Busy: 	game player is busy playing
// Show:	game show the sequence
// End: 	when the game has ended
typedef enum {GM_INIT, GM_BUSY, GM_SHOW, GM_END} game_state;

// 3 differents game mode with differents buffers
typedef enum {GM_LinBuff, GM_RingBuff, GM_LinkList} game_mode;

// Structure for pointer access to widgets and keep game variables
typedef struct {
    GtkWidget *w_img[4];        // Images in buttons
    GtkWidget *w_lbl_status;    // Status label
    GtkWidget *w_lbl_score;
    GtkWidget *w_lbl_max_score;
    GtkWidget *w_lbl_choice;

    /*
    Las siguientes 2 lineas son aquellas que deberían ser modificadas para utilizar un 
    Ring Buffer o Linked List para utilizar los datos del problema
    */ 
    gboolean turn;              // Keeps track of turns - TRUE = SHOW, FALSE = PLAYER
    ///////////////////
    gchar game_show[10];     // Tracks shown movements
    gchar game_input[10];    // Tracks user Inputs
    ///////////////////
    gchar game_board[4];        // 'o': On, 'x': Off
    gint game_board_timeout[4];
    game_state gm_state;        // Game state: init, busy, show, end
    game_mode gm_mode;
    gint value;                 // Cantidad de turno
    gint show_value;
    gint max_value;
    /////////////////// Control de velocidad de imagenes
    gint timeout_img;


} app_widgets;



game_state get_game_state(app_widgets *app_wdgts, gchar button);

void show_mem_function(gchar *array, app_widgets *app_wdgts);

void player_round(app_widgets *app_wdgts, gint img_index);

void press_img_x(app_widgets *app_wdgts, gint img_index);

#endif // GAME_LOGIC_H