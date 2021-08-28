#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>
#include "colors.h"

#define COL 7
#define ROW 7
/* GIOCATORI */
#define PLAYER1 1
#define PLAYER2 2

struct sus {
    int baci;
};

enum colori {
    NULLA = -1,
    VUOTO = 0,
    BIANCO = 1,
    NERO = 2
};

typedef char color_t;
typedef int type_t;

typedef struct {
    int row;
    int col;
} coordinates_t;

typedef struct{
    color_t color;
    bool isPromoted;
} hostage_t;

typedef struct  {
    bool is_promoted;
    color_t colore;
    type_t livello;
    hostage_t hostage[2];
    bool forced;
    bool checked;
} piece_t;


void board_default(piece_t pieces[7][7], int len);

void print_board_colors(piece_t board[7][7]);

void print_piece(select_color x);

void print_promoted_piece(select_color x);

void print_victory(select_color color);

void print_defeat();

void print_Welcome();

void init_game(piece_t pieces[7][7]);

void print_ped_av(piece_t *ped, int turno);

void print_Pedine_Mangiabili(piece_t* ped, int turno);

void init_campo(piece_t* ped, int row, int col);

void print_coordinates(coordinates_t s, coordinates_t copy);

void printTurno(int turno);

#endif
