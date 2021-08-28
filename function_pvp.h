

#ifndef MINILASKA_PROJECT_FUNCTION_PVP_H
#define MINILASKA_PROJECT_FUNCTION_PVP_H
#include "board.h"

coordinates_t  movePoint(coordinates_t coord, unsigned int dx, unsigned int dy);

void sposta_Pedina (piece_t *ped, coordinates_t coor, coordinates_t to_coor, int turno);

void check_Promotion(piece_t *ped, int turno);

int mangia_piece_t(piece_t *ped, int to_row, int to_col, int row, int col, int turno);

bool check_Pedine_Mangiabili(piece_t* ped, int turno);

bool checkCells(piece_t* ped, coordinates_t to_coor, coordinates_t coor, int turno);

bool checkPed_Selected(piece_t* ped, coordinates_t coor, int turno);

bool check_ped_av(piece_t *ped, int turno);

bool checkWin(piece_t* ped, int turno,int modalita);

coordinates_t string_to_int(char *uInput, int turno);

char* int_to_string(coordinates_t coordinate, coordinates_t destinationCoordinate);

bool check_input(char *uInput, int turno);

void swapTurn(int *turno);

#endif
