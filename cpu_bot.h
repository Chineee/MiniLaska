

#ifndef MINILASKA_PROJECT_CPU_BOT_H
#define MINILASKA_PROJECT_CPU_BOT_H

void print_cpu_coordinates(coordinates_t coor_first, coordinates_t to_coor);

void findMoveEasy(piece_t *ped, int turno, coordinates_t *coor, coordinates_t *to_coor);

piece_t *cpu_play(piece_t *board, coordinates_t *coor, coordinates_t *to_coor, int turno);

void search_Ped(piece_t *ped, int turno, coordinates_t *coor_first, coordinates_t *coor_second);

bool player_vs_cpu(piece_t ped[7][7], int* turno, int* modalita);

#endif
