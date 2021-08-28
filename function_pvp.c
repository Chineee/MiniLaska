
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function_pvp.h"
#include "board.h"
#include <unistd.h>

char NAME1[20];
char NAME2[20];

coordinates_t _GeneratePoint(unsigned int x, unsigned int y) {

    coordinates_t coordinate;

    coordinate.row = x;
    coordinate.col = y;

    return coordinate;

}

coordinates_t movePoint(coordinates_t coord, unsigned int dx, unsigned int dy) {
    return _GeneratePoint(coord.row + dx, coord.col + dy);
}


/**
 * La funzione sposta_Pedina scambia il contenuto di due celle di memoria, che rappresentano la posizione della pediina nella scacchiera
 *
 * @param ped
 * @param coor
 * @param to_coor
 * @param turno
 */
void sposta_Pedina (piece_t *ped, coordinates_t coor, coordinates_t to_coor, int turno) {
    piece_t copy;

    copy = ped[COL * coor.row + coor.col];
    ped[COL * coor.row + coor.col] = ped[COL * to_coor.row + to_coor.col];
    ped[COL * to_coor.row + to_coor.col] = copy;
}

/**
 * La funzione reset_pedine, viene chiamata all'inizio di ogni turno, essa andrà a settare tutti i campi di "is_forced" della pedina a 0
 * @param ped
 * @param turno
 */

void _reset_pedine(piece_t *ped, int turno) {
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            ped[COL*i + j].forced = 0;
        }
    }
}

/**
 *
 */

void check_Promotion(piece_t *ped, int turno) {
    int i;
    int j;

    for (i = 0; i < COL; i++) {
        for (j = 0; j < ROW; j++) {
            if ( (COL* i + j) < 7) {
                if (ped[COL * i + j].colore == NERO) {
                    ped[COL * i + j].is_promoted = 1;
                }
            } else if ( (COL*i + j) >= 42) {
                if (ped[COL * i + j].colore == BIANCO) {
                    ped[COL * i + j].is_promoted = 1;
                }
            }
        }
    }
}

/**
 * La funzione mangia_piece_t prende in input tutte le coordinate neccessarie, essa esegue degli scambi del contenuto delle pedine,
 * al fine di permettere una corretta mangiata.
 * @param ped
 * @param row
 * @param col
 * @param to_row
 * @param to_col
 * @param turno
 * @return
 */
int mangia_piece_t(piece_t *ped, int row, int col, int to_row, int to_col, int turno) {

    piece_t *pedina_mangiata = ped;

    if (turno == PLAYER1) {
        if (pedina_mangiata[COL*to_row+to_col].colore == BIANCO || pedina_mangiata[COL*to_row+to_col].colore == VUOTO)
            return 0;
    } else if (turno == PLAYER2) {
        if (pedina_mangiata[COL * to_row + to_col].colore == NERO || pedina_mangiata[COL*to_row+to_col].colore == VUOTO)
            return 0;
    }

    if (pedina_mangiata[COL * to_row + to_col].livello > 1)
        pedina_mangiata[COL * to_row + to_col].livello--;

    if (ped[COL*row+col].livello == 1) {
        ped[COL*row+col].livello++;
        ped[ROW*row+col].hostage[0].color = pedina_mangiata[COL * to_row + to_col].colore;
        ped[ROW*row+col].hostage[0].isPromoted = pedina_mangiata[COL * to_row + to_col].is_promoted;
        pedina_mangiata[COL * to_row + to_col].colore = pedina_mangiata[COL * to_row + to_col].hostage[0].color;
        pedina_mangiata[COL * to_row + to_col].is_promoted = pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[0].color = pedina_mangiata[COL * to_row + to_col].hostage[1].color;
        pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted = pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[1].color = VUOTO;
        pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted = false;
    } else if (ped[COL*row+col].livello == 2) {
        ped[COL*row+col].livello++;
        ped[ROW*row+col].hostage[1].color = pedina_mangiata[COL * to_row + to_col].colore;
        ped[ROW*row+col].hostage[1].isPromoted = pedina_mangiata[COL * to_row + to_col].is_promoted;
        pedina_mangiata[COL * to_row + to_col].colore = pedina_mangiata[COL * to_row + to_col].hostage[0].color;
        pedina_mangiata[COL * to_row + to_col].is_promoted = pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[0].color = pedina_mangiata[COL * to_row + to_col].hostage[1].color;
        pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted = pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[1].color = VUOTO;
        pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted = false;
    } else if (ped[COL*row+col].livello == 3) {
        pedina_mangiata[COL * to_row + to_col].colore = pedina_mangiata[COL * to_row + to_col].hostage[0].color;
        pedina_mangiata[COL * to_row + to_col].is_promoted = pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[0].color = pedina_mangiata[COL * to_row + to_col].hostage[1].color;
        pedina_mangiata[COL * to_row + to_col].hostage[0].isPromoted = pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted;
        pedina_mangiata[COL * to_row + to_col].hostage[1].color = VUOTO;
        pedina_mangiata[COL * to_row + to_col].hostage[1].isPromoted = false;
    }
    return 1;
}

/* QUA CI STA L'INIT DEL CAMPO */

/* PRINT PEDINE MANGIABILI */

/**
 * check_Pedine_Mangiabili controlla TUTTE le pedine NON vuote all'interno dell'array, e le confronta con quelle nelle posizioni successive.
 * Se rivela almeno una pedina che è in grado di mangiare, viene attivato un flag che viene settato ad 1. Alla pedina in grado di mangiare
 * verrà settato il campo is_forced a true
 *
 * @param ped
 * @param turno
 * @return flag (true or false)
 */

bool _out_of_board(int row, int col) {

    if (row > 6 || col > 6)
        return false;
    else if (row < 0 || col < 0)
        return false;
    else return true;
}

bool check_Pedine_Mangiabili(piece_t* ped, int turno) {

    int i, j;
    int flag = 0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (turno == PLAYER1) {
                if (ped[COL * i + j].colore == BIANCO) {
                    if (ped[COL * i + j].is_promoted == 0) {
                        if ((ped[COL * (i + 1) + (j + 1)].colore == NERO) && (ped[COL * (i + 2) + (j + 2)].colore == VUOTO) && _out_of_board(i+2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i + 1) + (j - 1)].colore == NERO) && (ped[COL * (i + 2) + (j - 2)].colore == VUOTO) && _out_of_board(i+2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                    } else {
                        if ((ped[COL * (i + 1) + (j + 1)].colore == NERO) && (ped[COL * (i + 2) + (j + 2)].colore == VUOTO) && _out_of_board(i+2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i + 1) + (j - 1)].colore == NERO) && (ped[COL * (i + 2) + (j - 2)].colore == VUOTO) && _out_of_board(i+2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i - 1) + (j - 1)].colore == NERO) && (ped[COL * (i - 2) + (j - 2)].colore == VUOTO) && _out_of_board(i-2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i - 1) + (j + 1)].colore == NERO) && (ped[COL * (i - 2) + (j + 2)].colore == VUOTO) && _out_of_board(i-2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                    }
                }
            } else {
                if (ped[COL * i + j].colore == NERO) {
                    if (ped[COL * i + j].is_promoted == 0) {
                        if ((ped[COL * (i - 1) + (j + 1)].colore == BIANCO) && (ped[COL * (i - 2) + (j + 2)].colore == VUOTO) && _out_of_board(i-2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i - 1) + (j - 1)].colore == BIANCO) && (ped[COL * (i - 2) + (j - 2)].colore == VUOTO) && _out_of_board(i-2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                    } else {
                        if ((ped[COL * (i - 1) + (j + 1)].colore == BIANCO) && (ped[COL * (i - 2) + (j + 2)].colore == VUOTO) && _out_of_board(i-2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i - 1) + (j - 1)].colore == BIANCO) && (ped[COL * (i - 2) + (j - 2)].colore == VUOTO) && _out_of_board(i-2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i + 1) + (j - 1)].colore == BIANCO) && (ped[COL * (i + 2) + (j - 2)].colore == VUOTO) && _out_of_board(i+2, j-2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                        if ((ped[COL * (i + 1) + (j + 1)].colore == BIANCO) && (ped[COL * (i + 2) + (j + 2)].colore == VUOTO) && _out_of_board(i+2, j+2)) {
                            ped[COL * i + j].forced = 1;
                            flag = 1;
                        }
                    }
                }
            }
        }
    }
    return flag;
}

bool checkCells(piece_t* ped, coordinates_t to_coor, coordinates_t coor, int turno) {

    if ((to_coor.row + to_coor.col) % 2 == 0) {
        if (ped[COL * to_coor.row + to_coor.col].colore == VUOTO) {
            if (to_coor.row > 6 || to_coor.col > 6 || to_coor.row < 0 || to_coor.col < 0) return 0;
            else {
                if (turno == PLAYER1) {
                    if (ped[COL * coor.row + coor.col].colore == BIANCO) {
                        if (check_Pedine_Mangiabili(ped, turno) == 1) {
                            if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                                if (ped[COL * coor.row + coor.col].forced == 1) {
                                    if (to_coor.row == coor.row + 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col - 1, turno);
                                    } else if (to_coor.row == coor.row + 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col + 1, turno);
                                    } else return 0;
                                } else return 0;
                            } else {
                                if (ped[COL * coor.row + coor.col].forced == 1) {
                                    if (to_coor.row == coor.row - 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col - 1, turno);
                                    } else if (to_coor.row == coor.row - 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col + 1, turno);
                                    } else if (to_coor.row == coor.row + 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col - 1, turno);
                                    } else if (to_coor.row == coor.row + 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col + 1, turno);
                                    } else return 0;
                                } else return 0;
                            }
                        } else if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                            if (to_coor.row == coor.row + 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else if (to_coor.row == coor.row + 1 && to_coor.col == coor.col + 1) {
                                return 1;
                            } else return 0;
                        } else {
                            if (to_coor.row == coor.row - 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else if (to_coor.row == coor.row - 1 && to_coor.col == coor.col + 1)
                                return 1;
                            else if (to_coor.row == coor.row + 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else if (to_coor.row == coor.row + 1 && to_coor.col == coor.col + 1)
                                return 1;
                            else return 0;
                        }
                    } else return 0;
                } else {
                    if (ped[COL * coor.row + coor.col].colore == NERO) {
                        if (check_Pedine_Mangiabili(ped, turno) == 1) {
                            if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                                if (ped[COL * coor.row + coor.col].forced == 1) {
                                    if (to_coor.row == coor.row - 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col + 1, turno);
                                    } else if (to_coor.row == coor.row - 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col - 1, turno);
                                    } else return 0;
                                } else return 0;
                            } else {
                                if (ped[COL * coor.row + coor.col].forced == 1) {
                                    if (to_coor.row == coor.row - 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col + 1, turno);
                                    } else if (to_coor.row == coor.row - 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row - 1, coor.col - 1, turno);
                                    } else if (to_coor.row == coor.row + 2 && to_coor.col == coor.col + 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col + 1, turno);
                                    } else if (to_coor.row == coor.row + 2 && to_coor.col == coor.col - 2) {
                                        return mangia_piece_t(ped, coor.row, coor.col, coor.row + 1, coor.col - 1, turno);
                                    } else return 0;
                                } else return 0;
                            }
                        } else if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                            if (to_coor.row == coor.row - 1 && to_coor.col == coor.col + 1)
                                return 1;
                            else if (to_coor.row == coor.row - 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else return 0;
                        } else {
                            if (to_coor.row == coor.row - 1 && to_coor.col == coor.col + 1)
                                return 1;
                            else if (to_coor.row == coor.row - 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else if (to_coor.row == coor.row + 1 && to_coor.col == coor.col + 1)
                                return 1;
                            else if (to_coor.row == coor.row + 1 && to_coor.col == coor.col - 1)
                                return 1;
                            else return 0;
                        }
                    } else return 0;
                }
            }
        }
    } else return 0;
    return 0;
}

bool checkPed_Selected(piece_t* ped, coordinates_t coor, int turno) {


    if (turno == PLAYER1) {
        if (((coor.row + coor.col) % 2 != 0) || (ped[coor.col * coor.row + coor.col].colore == VUOTO) || (ped[COL * coor.row+ coor.col].colore == NERO)) {
            return 0;
        } else if (check_Pedine_Mangiabili(ped, turno) == 1){
            if (ped[coor.col*coor.row+ coor.col].forced == 1) return 1;
            else return 0;
        }
        else if (ped[COL * coor.row + coor.col].colore == BIANCO) {
            if (ped[COL * coor.row + coor.col].is_promoted == 1) {
                if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, 1, -1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, -1, 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1)
                    return 1;
                else return 0;
            } else {
                if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, 1, -1), coor, turno) == 1)
                    return 1;
                else return 0;
            }
        } else return 0;
    } else {
        if (((coor.row+ coor.col) % 2 != 0) || (ped[COL * coor.row+ coor.col].colore == VUOTO) || (ped[COL * coor.row+ coor.col].colore == BIANCO))
            return 0;
        else if (check_Pedine_Mangiabili(ped, turno) == 1) {
            if (ped[COL * coor.row+ coor.col].forced == 1) return 1;
            else return 0;
        }
        else if (ped[COL * coor.row+ coor.col].colore == NERO) {
            if (ped[COL * coor.row+ coor.col].is_promoted == 1) {
                if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, 1, -1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, -1 , 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1)
                    return 1;
                else return 0;
            } else {
                if (checkCells(ped, movePoint(coor, -1, 1), coor, turno) == 1)
                    return 1;
                else if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1)
                    return 1;
                else return 0;
            }
        } else return 0;
    }
    return 1;
}

bool check_ped_av(piece_t *ped, int turno) {

    coordinates_t coord;
    int flag = 0;

    for (coord.row = 0; coord.row < ROW; coord.row++) {
        for (coord.col = 0; coord.col < COL; coord.col++) {
            if ( ( coord.row + coord.col ) % 2 == 0) {
                if (turno == PLAYER1) {
                    if (ped[COL * coord.row + coord.col].colore == BIANCO) {
                        if (ped[COL * coord.row + coord.col].is_promoted == 1) {
                            if (checkCells(ped, movePoint(coord, 1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, 1, -1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, -1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, -1, -1), coord, turno) == 1)
                                flag = 1;
                        } else {
                            if (checkCells(ped, movePoint(coord, 1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, 1, -1), coord, turno) == 1)
                                flag = 1;
                        }
                    }
                } else {
                    if (ped[COL * coord.row + coord.col].colore == NERO) {
                        if (ped[COL * coord.row + coord.col].is_promoted == 1) {
                            if (checkCells(ped, movePoint(coord, 1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, 1, -1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, -1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, -1, -1), coord, turno) == 1)
                                flag = 1;
                        } else {
                            if (checkCells(ped, movePoint(coord, -1, 1), coord, turno) == 1)
                                flag = 1;
                            else if (checkCells(ped, movePoint(coord, -1, -1), coord, turno) == 1)
                                flag = 1;
                        }
                    }
                }
            }
        }
    }
    return flag;
}

bool checkWin(piece_t* ped, int turno,int modalita) {
    if (check_ped_av(ped, turno) == 0 && check_Pedine_Mangiabili(ped, turno) == 0) {
        if (modalita == 1) {
            sleep(3);
            if (turno == PLAYER1) {
                print_victory(blue);
                cprint(blue, NAME1);
                cprint(green, "has won the game!\n");
            } else {
                print_victory(red);
                cprint(red, NAME2);
                cprint(green, "has won the game!\n");
            }
        }
        else if(modalita == 2) {
            if (turno == PLAYER1) {
                print_victory(green);
                cprint(blue, NAME1);
                cprint(green, "has won the game!\n");
            } else {
                print_defeat();
                printf("The CPU has won the match!\n");

            }
        }
        return false;
    }
    else {
        _reset_pedine(ped, turno);
        return true;
    }
}

coordinates_t string_to_int(char *uInput, int turno){
    coordinates_t new;
    new.col = uInput[0]-97;              /* transforms a - g into 0-6        */
    new.row = (uInput[1]-(49+6))*-1;    /* Reverses the inputs 7-1 to 0 - 6 */
    /*
     *
     * if uInput[1] is 55 (7 char) the formula will do 55 - 55 * -1 = 0
     * if uInput[1] is 54 (6 char) the formula will do 54 - 55 * -1 = 1
     *
     * */
    return new;

}

char* int_to_string(coordinates_t coordinate, coordinates_t destinationCoordinate) {

    char *stringCoordinates = (char*) malloc(6 * sizeof (coordinates_t));

    stringCoordinates[0] = coordinate.col + 97;
    stringCoordinates[1] = coordinate.row * -1 + 55;
    stringCoordinates[2] = '-';
    stringCoordinates[3] = destinationCoordinate.col + 97;
    stringCoordinates[4] = destinationCoordinate.row * -1 + 55;
    stringCoordinates[5] = '\0';

    return stringCoordinates;
}

bool check_input(char *uInput, int turno){
    /* function checks if the input of the user is in the bounds of our board */
    if (strlen(uInput) < 4) {
        cprint(red,"Error!!! Expected input in format <Letter> <number>!!!\n");
        return 0;
    }
    if(uInput[0] < 'a' || uInput [0] > 'g' || uInput[1] < '1' || uInput[1] > '7' ){
        cprint(red,"Error!!! Expected letter <a to g> number <1 to 7>!!!\n");
        return 0;
    }
    else
        return 1;
}

void swapTurn(int *turno) {
    if (*turno == PLAYER1) *turno = PLAYER2;
    else *turno = PLAYER1;
}
