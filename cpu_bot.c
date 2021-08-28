#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "board.h"
#include "function_pvp.h"
#include "cpu_bot.h"
#include "commands.h"
#define Mosse_Avanti ( 4 )

#define Invalid_Move ( -20 )

typedef int point_t;

command_t commands[10];

void _check_and_reset_ped(piece_t *ped) {

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if ( (i + j) % 2 == 0) {
                ped[COL*i + j].checked = false;
            } else continue;
        }
    }
}

void print_cpu_coordinates(coordinates_t coor, coordinates_t to_coor) {

    printf("Ultima mossa della CPU:  ");
    print_coordinates(coor, to_coor);

}

void _copy_board(piece_t *copiedBoard, piece_t *board) {

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if ( ( i + j ) % 2 == 0) {
                board[COL * i + j].colore = copiedBoard[COL * i + j].colore;
                board[COL * i + j].is_promoted = copiedBoard[COL * i + j].is_promoted;
                board[COL * i + j].livello = copiedBoard[COL * i + j].livello;
                board[COL * i + j].hostage[0].color = copiedBoard[COL * i + j].hostage[0].color;
                board[COL * i + j].hostage[0].isPromoted = copiedBoard[COL * i + j].hostage[0].isPromoted;
                board[COL * i + j].hostage[1].color = copiedBoard[COL * i + j].hostage[1].color;
                board[COL * i + j].hostage[1].isPromoted = copiedBoard[COL * i + j].hostage[1].isPromoted;
            } else continue;
        }
    }
}

coordinates_t _copy_coordinate(coordinates_t copyed_coordinate) {

    coordinates_t copy_coord;

    copy_coord.row = copyed_coordinate.row;
    copy_coord.col = copyed_coordinate.col;

    return copy_coord;

}


bool _can_be_eaten(piece_t *board, int turno) {

    coordinates_t enemy_coordinate; /* COORDINATE DEL GIOCATORE UMANO */
    piece_t *board_copy = (piece_t*) malloc(49*sizeof (piece_t));

    _copy_board(board, board_copy);

    for (enemy_coordinate.row = 0; enemy_coordinate.row < ROW; enemy_coordinate.row++) {
        for (enemy_coordinate.col = 0; enemy_coordinate.col < COL; enemy_coordinate.col++) {
            if (turno == PLAYER1) {
                if (board[COL * enemy_coordinate.row + enemy_coordinate.col].colore == BIANCO) {
                    if (checkCells(board_copy, movePoint(enemy_coordinate, -2, -2), enemy_coordinate, turno) == 1)
                        return true;
                    else if (checkCells(board_copy, movePoint(enemy_coordinate, -2, 2), enemy_coordinate, turno) == 1)
                        return true;
                    else if (checkCells(board_copy, movePoint(enemy_coordinate, 2, -2), enemy_coordinate, turno) == 1)
                        return true;
                    else if (checkCells(board_copy, movePoint(enemy_coordinate, 2, 2), enemy_coordinate, turno) == 1)
                        return true;
                    else continue;
                } else {
                    if (board[COL * enemy_coordinate.row + enemy_coordinate.col].colore == NERO) {
                        if (checkCells(board_copy, movePoint(enemy_coordinate, -2, -2), enemy_coordinate, turno) == 1)
                            return true;
                        else if (checkCells(board_copy, movePoint(enemy_coordinate, -2, 2), enemy_coordinate, turno) == 1)
                            return true;
                        else if (checkCells(board_copy, movePoint(enemy_coordinate, 2, -2), enemy_coordinate, turno) == 1)
                            return true;
                        else if (checkCells(board_copy, movePoint(enemy_coordinate, 2, 2), enemy_coordinate, turno) == 1)
                            return true;
                        else continue;
                    }
                }
            }
        }
    }
    return false;
}

bool _canBePromoted(piece_t *ped, coordinates_t coor, coordinates_t to_coor) {

    int i, j;

    for(i = 0; i < ROW; i++) {
        if (ped[i].is_promoted == 1)
            continue;
        else {
            if (ped[i].colore == NERO)
                return 1;
        }
    }
    return 0;
}

point_t _findMove(piece_t *board, int turno, coordinates_t *coor, coordinates_t *to_coor,  point_t best_score) {


    coordinates_t coor_first = _copy_coordinate(*coor);
    point_t point = 0;
    piece_t *ped = (piece_t*) malloc(49*sizeof (piece_t));
    _copy_board(board, ped);

    if (checkPed_Selected(ped, coor_first, turno) == 0) return Invalid_Move;

    if (checkCells(ped, movePoint(coor_first, -2, -2), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, -2, -2), turno);
        point += 2;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, -2, -2)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }
        swapTurn(&turno);
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, -2, -2));
        }
        _copy_board(board, ped);
    }

    if (checkCells(ped, movePoint(coor_first, 2, -2), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, 2, -2), turno);
        point += 2;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, 2, -2)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }
        swapTurn(&turno);
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, 2, -2));
        }
        _copy_board(board, ped);
    }

    if (checkCells(ped, movePoint(coor_first, -2, 2), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, -2, 2), turno);
        point += 2;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, -2, 2)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }
        swapTurn(&turno);
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, -2, 2));
        }
        _copy_board(board, ped);
    }

    if (checkCells(ped, movePoint(coor_first, 2, 2), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, 2, 2), turno);
        point += 2;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, 2, 2)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }
        swapTurn(&turno);
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, 2, 2));
        }
        _copy_board(board, ped);
    }

    if (checkCells(ped, movePoint(coor_first, -1, 1), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, -1, 1), turno);
        point++;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, -1, 1)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }
        swapTurn(&turno);

        if (point == -1) {
            if (_can_be_eaten(ped, turno) == 1)
                point += 2;
        }
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, -1, 1));
        }
        _copy_board(board, ped);
    }
    if (checkCells(ped, movePoint(coor_first, -1, -1), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, -1, -1), turno);
        point++;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, -1, -1)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }

        swapTurn(&turno);

        if (point == -1) {
            if (_can_be_eaten(ped, turno) == 1)
                point += 2;
        }
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, -1, -1));
        }
        _copy_board(board, ped);
    }
    if (checkCells(ped, movePoint(coor_first, 1, -1), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, 1, -1), turno);
        point++;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, 1, -1)) == 1)
            point += 1;
        swapTurn(&turno);
        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }

        swapTurn(&turno);

        if (point == -1) {
            if (_can_be_eaten(ped, turno) == 1)
                point += 2;
        }

        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, 1, -1));
        }
        _copy_board(board, ped);
    }

    if (checkCells(ped, movePoint(coor_first, 1, 1), coor_first, turno) == 1) {
        point = 0;
        sposta_Pedina(ped, coor_first, movePoint(coor_first, 1, 1), turno);
        point++;
        if (_canBePromoted(ped, coor_first, movePoint(coor_first, 1, 1)) == 1)
            point += 1;
        swapTurn(&turno);

        if (_can_be_eaten(ped, turno) == 1) {
            point -= 1;
        }

        swapTurn(&turno);

        if (point == -1) {
            if (_can_be_eaten(ped, turno) == 1)
                point += 2;
        }
        if (point >= best_score) {
            best_score = point;
            *to_coor = _copy_coordinate(movePoint(coor_first, 1, 1));
        }
    }

    free(ped);

    return point;
}

piece_t *cpu_play(piece_t *board, coordinates_t *coor, coordinates_t *to_coor, int turno) {

    piece_t *board_copy = (piece_t *) malloc(49 * sizeof(piece_t));
    coordinates_t new_coordinate;
    coordinates_t new_coordinates_moves;
    point_t point = 0;
    point_t best = 0;
    _copy_board(board, board_copy);


    for (new_coordinate.row = 0; new_coordinate.row < ROW; new_coordinate.row++) {
        for (new_coordinate.col = 0; new_coordinate.col < COL; new_coordinate.col++) {
            point = 0;
            if (board_copy[COL * new_coordinate.row + new_coordinate.col].colore == NERO && turno == PLAYER2) {
                _copy_board(board, board_copy);
                point = _findMove(board_copy, turno, &new_coordinate, &new_coordinates_moves, best);
                if (point >= best) {
                    *coor = _copy_coordinate(new_coordinate);
                    *to_coor = _copy_coordinate(new_coordinates_moves);
                    best = point;
                }
            } else continue;
        }
    }


    _copy_board(board, board_copy);
    if (checkCells(board_copy, *to_coor, *coor, turno) == 1) {
        sposta_Pedina(board_copy, *coor, *to_coor, turno);
    } else sposta_Pedina(board_copy, *coor, *to_coor, turno);
    _copy_board(board_copy, board);
    free(board_copy);

    return board;
}

void search_Ped(piece_t *ped, int turno, coordinates_t *coor_first, coordinates_t *coor_second) {

        ped = cpu_play(ped, coor_first, coor_second, turno);

}

bool player_vs_cpu(piece_t ped[7][7], int* turno,int * modalita) {

    char game[5];
    bool isGame = true;
    clear_screen();
    print_board_colors(ped);

    while (true) {

        char uInput[10];

        coordinates_t coor_first;
        coordinates_t coor_second;

        if (*turno == PLAYER2) {
            check_Pedine_Mangiabili(*ped, *turno);
            search_Ped(&(ped[0][0]), *turno, &coor_first, &coor_second);
            check_Promotion(&(ped[0][0]), *turno);
            printf("The cpu is thinking!\n");
            sleep(2);
        } else {
            int com_index;
            printf("Please select the move!\n");
            if (check_Pedine_Mangiabili(&(ped[0][0]), *turno) == 1)
                print_Pedine_Mangiabili(&(ped[0][0]), *turno);
            else print_ped_av(&(ped[0][0]), *turno);
            printf("\n");
            scanf("%s", uInput);
            com_index = check_if_command(commands, uInput);
            if (com_index >= 0) {
                bool temp = command_exec(ped, commands, turno, com_index, isGame, modalita);
                if (com_index == 7 && temp == true)
                    return true;
                if (*turno < 1)
                    break;
                else continue;
            }
            if (check_input(uInput, *turno) == 0)
                continue;
            coor_first = string_to_int(uInput, *turno);
            coor_second = string_to_int(uInput + 3, *turno);
            if (checkCells(&(ped[0][0]), coor_second, coor_first, *turno) == 0) {
                cprint(red,"The selected cell is invalid !!\n");
                continue;
            }
            sposta_Pedina(&(ped[0][0]), coor_first, coor_second, *turno);
        }
        check_Promotion(&(ped[0][0]), *turno);
        swapTurn(turno);
        clear_screen();
        print_board_colors(ped);
        if (*turno == PLAYER1)
            print_cpu_coordinates(coor_first, coor_second);
        if (checkWin(&(ped[0][0]), *turno, *modalita) == 0) {
            *turno = 0;
            break;
        }

        printf("\n\n");
    }
    if(*turno == 0) {
        cprint(green,"Thank you for playing MINI-LASKA!!"
               "\nWould you like to play again? ( y / n )\n");
        scanf("%s", game);
        *modalita = 0;
        if (game[0] == 'y' || game[0] == 'Y') return true;
        else return false;
    }
    if(*turno < 0){
        *turno = 1;
        return true;
    }
    return false;
}
