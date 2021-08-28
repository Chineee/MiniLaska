#include <stdio.h>
#include "board.h"
#include <stdbool.h>
#include "function_pvp.h"
#include <stdlib.h>


char NAME1[20];
char NAME2[20];

const piece_t PIECES1 = {false, BIANCO, 1, { {VUOTO, false}, {VUOTO, false} }, false, false};
const piece_t PIECES2 = {false, NERO, 1, { {VUOTO, false}, {VUOTO, false} }, false, false};
const piece_t EMPTY_CELL = {false, VUOTO, 1, { {VUOTO, false}, {VUOTO, false} }, false, false};


void print_emptyw(){
    int i;
    change_bg_color(white);
    for(i = 0; i < 10; i++)
        printf(" ");
    reset_color();
}

void print_emptyb(){
    int i;
    for(i = 0; i < 10; i++)
        printf(" ");
}

void print_piece(select_color x){
    int i;
    change_bg_color(white);
    printf(" ");
    if(x == red){
        change_bg_color(red);
    }
    else if(x == blue){
        change_bg_color(blue);
    }
    change_fg_color(yellow);
    for(i = 0; i < 8; i++)
        printf("_");
    change_bg_color(white);
    printf(" ");
    reset_color();
}

void print_promoted_piece(select_color x){
    int i;
    change_bg_color(white);
    printf(" ");
    if(x == red)
        change_bg_color(red);
    else change_bg_color(blue);
    change_fg_color(yellow);
    for(i = 0; i < 7; ++i) {
        if (i == 3)
            printf("OO");
        else printf("_");
    }
    change_bg_color(white);
    printf(" ");
    reset_color();
}

void print_board_colors(piece_t board[7][7]){
    int row, col, row_mult;
    char a='a', count = 7;
    printf(" |");
    for (col = 0; col < 7 * 10; col++)
        printf("=");
    printf("|");
    cprint(red,NAME2);
    printf("\n |");

    for(row = 0; row < 7; row++){
        for(row_mult = 0; row_mult < 5; row_mult++){
            for(col = 0; col < 7; col++){
                if(board[row][col].is_promoted == false) {
                    if(board[row][col].colore == 1 && board[row][col].livello == 1 && row_mult == 2)
                        print_piece(red);
                    else if(board[row][col].colore == 2 && board[row][col].livello == 1 && row_mult == 2)
                        print_piece(blue);
                    else if(board[row][col].colore == 1 && board[row][col].livello > 1 && row_mult >= 1 && row_mult < 4){
                        if(row_mult == 1)
                            print_piece(red);
                        if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(blue);
                        else if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(blue);
                        else if((row + col) % 2 == 0 && row_mult == 3 && board[row][col].livello == 2) print_emptyw();
                        if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(blue);
                        else  if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(blue);
                    }
                    else if(board[row][col].colore == 2 && board[row][col].livello > 1 && row_mult >= 1 && row_mult < 4){
                        if(row_mult == 1)
                            print_piece(blue);
                        if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(blue);
                        else if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(blue);
                        else if((row + col) % 2 == 0 && row_mult == 3 && board[row][col].livello == 2)
                            print_emptyw();
                        if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(blue);
                        else  if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(blue);
                    }
                    else if ((row + col) % 2 == 1)
                        print_emptyb();
                    else print_emptyw();
                }
                if(board[row][col].is_promoted == true) {
                    if(board[row][col].colore == 1 && board[row][col].livello == 1 && row_mult == 2)
                        print_promoted_piece(red);
                    else if(board[row][col].colore == 2 && board[row][col].livello == 1 && row_mult == 2)
                        print_promoted_piece(blue);
                    else if(board[row][col].colore == 1 && board[row][col].livello > 1 && row_mult >= 1 && row_mult < 4){
                        if(row_mult == 1)
                            print_promoted_piece(red);
                        if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(blue);
                        else if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(blue);
                        if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(blue);
                        else  if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(blue);
                    }
                    else if(board[row][col].colore == 2 && board[row][col].livello > 1 && row_mult >= 1 && row_mult < 4){
                        if(row_mult == 1)
                            print_promoted_piece(blue);
                        if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 0)
                            print_piece(blue);
                        else if(board[row][col].hostage[0].color == 1 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(red);
                        else if(board[row][col].hostage[0].color == 2 && row_mult == 2 && board[row][col].hostage[0].isPromoted == 1)
                            print_promoted_piece(blue);
                        if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 0)
                            print_piece(blue);
                        else  if(board[row][col].hostage[1].color == 1 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(red);
                        else  if(board[row][col].hostage[1].color == 2 && row_mult == 3 && board[row][col].hostage[1].isPromoted == 1)
                            print_promoted_piece(blue);
                    }
                    else if ((row + col) % 2 == 1)
                        print_emptyb();
                    else print_emptyw();
                }
            }
            if(row_mult == 1)
                printf("|\n%d|",count--);
            else
                printf("|\n |");
        }
    }

    for (col = 0; col < 7 * 10; col++)
        printf("=");
    printf("|");
    cprint(blue,NAME1);
    printf("\n ");

    for (col = 0; col < 7 * 10; col++) {
        if ((col % 5) == 0 && col != 0 && col % 10 != 0)
            printf("%c", a++);
        else printf(" ");
    }
    printf("\n");
}


void print_victory(select_color color){
    clear_screen();
    change_fg_color(color);
    printf("             .#############. \n"
           "          .###################. \n"
           "       .####/####################.,:::;;;;;;;;;, \n"
           "      .####/###############\\######:::;;;;;;;;;;;;;, \n"
           "      ####&&&&################\\######:::;;;;;;;;@;;;;;;, \n"
           "      ####&&&&################&&#####:::;;;;;;;;;@;;;;;;, \n"
           "      ####&&&&################&&#####:::;;;;;;;;;@@;;;;;; \n"
           "      `####\\################&&#####:::;;;;;;;;;;@@;;;;;; \n"
           "        `###\\##############&&####:::;;;;;;;;;;;;@@;;;;;; \n"
           "           `#################'::&&&&&&&&&&&&;;;@;;;;;;' \n");
    printf("             `#############'.&&&&&&&&&&&&&&&&&&;;;;;' \n"
           "               `#########'&&&&#&&&&&&&&&&&&&&&&&&&&, \n"
           "                 `#####'.&&&&#&&&&&&&&&&&&&&#&&&&&, \n"
           "                   `##' &&&&##&&&&&&&&&&&&&&&##&&&&& \n"
           "                   ###  &&&&##&&&&&&&&&&&&&&&##&&&&& \n"
           "                    '   &&&&##&&&&&&&&&&&&&&&##&&&&& \n"
           "                   '    `&&&&#&&&&&&&&&&&&&&&#&&&&&' \n");
    printf("                  '       `&&&#&&&&&&&&&&&&&#&&&&' \n"
           "                  `         `&&&&&&&&&&&&&&&&&&' \n"
           "                   `          `&&&&&&&&&&&&&&' \n"
           "                    `           `&&&&&&&&&&'  ' \n"
           "                     '            `&&&&&&'   ' \n"
           "                    '              `&&&&'    ' \n"
           "                   '               .&&      ` \n"
           "                  `                &&&&      ' \n"
           "                   `                '       ' \n"
           "                    `              '      ' \n"
           "                    '            '      ' \n"
           "                   '           '       ` \n"
           "                  '           '        ' \n"
           "                              `       ' \n"
           "                               ' \n"
           "                              ' \n"
           "                             ' \n");
    reset_color();
}

void print_defeat(){
    clear_screen();
    change_fg_color(red);
    printf("               ...\n"
           "             ;::::;\n"
           "           ;::::; :;\n"
           "         ;:::::'   :;\n"
           "        ;:::::;     ;.\n"
           "       ,:::::'       ;           OOO\\\n"
           "       ::::::;       ;          OOOOO\\\n"
           "       ;:::::;       ;         OOOOOOOO\n"
           "      ,;::::::;     ;'         / OOOOOOO\n"
           "    ;:::::::::`. ,,,;.        /  / DOOOOOO\n");
    printf("  .';:::::::::::::::::;,     /  /     DOOOO\n"
           " ,::::::;::::::;;;;::::;,   /  /        DOOO\n"
           ";`::::::`'::::::;;;::::: ,#/  /          DOOO\n"
           ":`:::::::`;::::::;;::: ;::#  /            DOOO\n"
           "::`:::::::`;:::::::: ;::::# /              DOO\n"
           "`:`:::::::`;:::::: ;::::::#/               DOO\n"
           " :::`:::::::`;; ;:::::::::##                OO\n"
           " ::::`:::::::`;::::::::;:::#                OO\n"
           " `:::::`::::::::::::;'`:;::#                O\n"
           "  `:::::`::::::::;' /  / `:#\n"
           "   ::::::`:::::;'  /  /   `#\n"
           "\n");
    reset_color();
}

void print_Welcome() {
    int i,j,row_mult,col_mult;
    printf("|");
    for(i = 0; i < (13 * 7); i++)
        printf("=");
    printf("|\n|");
    for(i = 0; i < 2; i++){
        for(row_mult = 0; row_mult < 7; row_mult++) {
            for (j = 0; j < 7; j++) {
                for(col_mult = 0; col_mult < 13; col_mult++) {
                    if ((i + j) % 2 == 0) {
                        change_bg_color(white);
                        printf(" ");
                    }
                    else{
                        change_bg_color(black);
                        printf(" ");
                    }
                }
                reset_color();
            }
            printf("|\n|");
        }
    }
    printf(" $$\\      $$\\ $$$$$$\\ $$\\   $$\\ $$$$$$\\ $$\\        $$$$$$\\   $$$$$$\\  $$\\   $$\\  $$$$$$\\   |\n"
           "| $$$\\    $$$ |\\_$$  _|$$$\\  $$ |\\_$$  _|$$ |      $$  __$$\\ $$  __$$\\ $$ | $$  |$$  __$$\\  |\n"
           "| $$$$\\  $$$$ |  $$ |  $$$$\\ $$ |  $$ |  $$ |      $$ /  $$ |$$ /  \\__|$$ |$$  / $$ /  $$ | |\n"
           "| $$\\$$\\$$ $$ |  $$ |  $$ $$\\$$ |  $$ |  $$ |      $$$$$$$$ |\\$$$$$$\\  $$$$$  /  $$$$$$$$ | |\n" );
    printf(
            "| $$ \\$$$  $$ |  $$ |  $$ \\$$$$ |  $$ |  $$ |      $$  __$$ | \\____$$\\ $$  $$<   $$  __$$ | |\n"
            "| $$ |\\$  /$$ |  $$ |  $$ |\\$$$ |  $$ |  $$ |      $$ |  $$ |$$\\   $$ |$$ |\\$$\\  $$ |  $$ | |\n"
            "| $$ | \\_/ $$ |$$$$$$\\ $$ | \\$$ |$$$$$$\\ $$$$$$$$\\ $$ |  $$ |\\$$$$$$  |$$ | \\$$\\ $$ |  $$ | |\n"
            "| \\__|     \\__|\\______|\\__|  \\__|\\______|\\________|\\__|  \\__| \\______/ \\__|  \\__|\\__|  \\__| ");
    reset_color();
    printf("|\n|");
    for(i = 0; i < 2; i++){
        for(row_mult = 0; row_mult < 7; row_mult++) {
            for (j = 0; j < 7; j++) {
                for(col_mult = 0; col_mult < 13; col_mult++) {
                    if ((i + j) % 2 == 0) {
                        change_bg_color(white);
                        printf(" ");
                    }
                    else{
                        change_bg_color(black);
                        printf(" ");
                    }
                }
                reset_color();
            }
            printf("|\n|");
        }
    }
    for(i = 0; i < (13 * 7); i++)
        printf("=");
    printf("|\n\n");
}


void init_game(piece_t pieces[7][7]) {

    int i, j;

    for (j = 0; j < ROW; j++) {
        for (i = 0; i < COL; i++) {
            if ((i + j) % 2 == 0 && (j < 3)) {
                pieces[j][i] = PIECES1;
            }

            else if ((i + j) % 2 == 0 && (j > ROW - 4)) {

                pieces[j][i] = PIECES2;
            }

            else pieces[j][i] = EMPTY_CELL;
        }
    }
}


void print_coordinates(coordinates_t s, coordinates_t copy){

    char *stringCoord;
    stringCoord = int_to_string(s, copy);
    cprint(green, stringCoord);
    printf(" ");
    free(stringCoord);
}

bool __out_of_board(int row, int col) {

    if (row > 6 || col > 6)
        return false;
    else if (row < 0 || col < 0)
        return false;
    else return true;
}

void print_Pedine_Mangiabili(piece_t* ped, int turno) {
    coordinates_t coor;
    coordinates_t copy;

    printf("Available moves: ");
    change_fg_color(green);
    for (coor.row = 0; coor.row < ROW; coor.row++) {
        for (coor.col = 0; coor.col < COL; coor.col++) {
            if (turno == PLAYER1) {
                if (ped[COL * coor.row + coor.col].colore == BIANCO) {
                    if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                        if ((ped[COL * (coor.row + 1) + (coor.col + 1)].colore == NERO) && (ped[COL * (coor.row + 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row + 1) + (coor.col - 1)].colore == NERO) && (ped[COL * (coor.row + 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                    } else {
                        if ((ped[COL * (coor.row + 1) + (coor.col + 1)].colore == NERO) && (ped[COL * (coor.row + 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row + 1) + (coor.col - 1)].colore == NERO) && (ped[COL * (coor.row + 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row - 1) + (coor.col - 1)].colore == NERO) && (ped[COL * (coor.row - 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row - 1) + (coor.col + 1)].colore == NERO) && (ped[COL * (coor.row- 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                    }
                }
            } else {
                if (ped[COL * coor.row + coor.col].colore == NERO) {
                    if (ped[COL * coor.row + coor.col].is_promoted == 0) {
                        if ((ped[COL * (coor.row - 1) + (coor.col + 1)].colore == BIANCO) && (ped[COL * (coor.row - 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row - 1) + (coor.col - 1)].colore == BIANCO) && (ped[COL * (coor.row - 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                    } else {
                        if ((ped[COL * (coor.row - 1) + (coor.col + 1)].colore == BIANCO) && (ped[COL * (coor.row - 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row - 1) + (coor.col - 1)].colore == BIANCO) && (ped[COL * (coor.row - 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row-2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row -= 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row + 1) + (coor.col - 1)].colore == BIANCO) && (ped[COL * (coor.row + 2) + (coor.col - 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col-2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col -= 2;
                            print_coordinates(coor, copy);
                        }
                        if ((ped[COL * (coor.row + 1) + (coor.col + 1)].colore == BIANCO) && (ped[COL * (coor.row + 2) + (coor.col + 2)].colore == VUOTO) && __out_of_board(coor.row+2, coor.col+2)) {
                            ped[COL * coor.row + coor.col].forced = 1;
                            copy = coor; copy.row += 2; copy.col += 2;
                            print_coordinates(coor, copy);
                        }
                    }
                }
            }
        }
    }
    reset_color();
    printf("\n");
}

void print_ped_av(piece_t *ped, int turno) {

    coordinates_t  coor;
    coordinates_t copy;

    printf("Available moves: ");
    change_fg_color(green);
    for (coor.row = 0; coor.row < ROW; coor.row++) {
        for (coor.col = 0; coor.col < COL; coor.col++) {
            if ( (coor.row+coor.col) % 2 == 0) {
                if (turno == PLAYER1) {
                    if (ped[COL * coor.row + coor.col].colore == BIANCO) {
                        if (ped[COL * coor.row + coor.col].is_promoted == 1) {
                            if (checkCells(ped,movePoint(coor, 1, -1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, -1, 1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                        } else {
                            if (checkCells(ped, movePoint(coor, 1, -1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                        }
                    }
                } else {
                    if (ped[COL * coor.row + coor.col].colore == NERO) {
                        if (ped[COL * coor.row + coor.col].is_promoted == 1) {
                            if (checkCells(ped, movePoint(coor, 1, 1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, 1, -1), coor, turno) == 1) {
                                copy = coor; copy.row += 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, -1, 1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                        } else {
                            if (checkCells(ped, movePoint(coor, -1, 1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col += 1;
                                print_coordinates(coor, copy);
                            }
                            if (checkCells(ped, movePoint(coor, -1, -1), coor, turno) == 1) {
                                copy = coor; copy.row -= 1; copy.col -= 1;
                                print_coordinates(coor, copy);
                            }
                        }
                    }
                }
            }
        }
    }
    reset_color();
}

void printTurno(int turno) {
    if (turno == PLAYER1) {
        printf("It's the turn of ");
        cprint(red,NAME2);
        printf("!!! \n");
    }
    else {
        printf("It's the turn of ");
        cprint(blue,NAME1);
        printf("!!! \n");
    }
}
