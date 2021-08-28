#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function_pvp.h"
#include "pvp.h"
#include "commands.h"


command_t commands[10];

/**
 * La funziona ritorna un numero casuale da 0 a 1, in base a cosa l'utente ha scelto, verrà assegnato il primo turno ad uno dei due giocatori.
 * @return ( rand() % 2);
 */

char head_or_tails() {

    srand(time(NULL)); /*Inizializziamo il seme che deciderà la sequenza dei numeri casuali, in questo caso impostiamo la differenza in secondi dal 1/1/1970 ad oggi */
    return ( rand() % 2) + 1; /*La sequenza non è casuale, ma viene determinata da una piccola sequenza di valori iniziali e da un singolo valore davvero casuale, ovvero il seme che andiamo ad impostare */
    /* SENZA IL SEME, IL PROGRAMMA ESTRAREBBE SEMPRE GLI STESSI NUMERI CASUALI */
}

/**
 * La funzione player_vs_player gestisce tutti i comandi per permettere a due giocatori di giocare uno contro l'altro
 * Utilizza tutte le funzioni necessarie per permettere al gioco di continuare
 * @param ped
 * @param turno
 * @return
 */

bool player_vs_player(piece_t ped[7][7],int* modalita, int *turno) {

    char heota;
    char game[2];
    int turnBK;
    bool isGame = true;
    cprint(yellow,"Heads or tails? ( H / T )\n");

    while (*turno == 0) {
        scanf("%s", &heota);
        if ( heota != 'H' && heota != 'T' && heota != 't' && heota != 'h') {
           cprint(red,"Error! Incorrect input!\n");
           cprint(green,"Please choose H for heads or T for tails!\n");
        }
        else {
            heota = head_or_tails();
            if (heota == 1)
                *turno = PLAYER1;
            else if(heota == 2) *turno = PLAYER2;
        }
    }
    turnBK = *turno;
    clear_screen();
    print_board_colors(ped);

    while (true) {
        coordinates_t coordinates_first;
        coordinates_t coordinates_second;
        char coordinate[10];
        int command_index = -1;
        printTurno(*turno);
        if (check_Pedine_Mangiabili(&(ped[0][0]), *turno) == 1)
            print_Pedine_Mangiabili(&(ped[0][0]), *turno);
        else print_ped_av(&(ped[0][0]), *turno);
        printf("\nChoose the row and column: ( 0 - 6 ) - ( 0 - 6 )\n");
        scanf("%s", coordinate);
        command_index = check_if_command(commands,coordinate);
        if(command_index >= 0){
            bool temp = command_exec(ped,commands,turno,command_index,isGame,modalita);
            if(command_index == 7 && temp == true)
                return true;
            if (*turno < 1)
                break;
            else continue;
        }
        if (check_input(coordinate, *turno) == 0)
            continue;
        coordinates_first = string_to_int(coordinate, *turno);
        coordinates_second = string_to_int(coordinate+3, *turno);
        if (checkCells(&(ped[0][0]), coordinates_second, coordinates_first, *turno) == 0) {
            cprint(red,"This is not an available move!!\n");
            continue;
        }
        sposta_Pedina(&(ped[0][0]), coordinates_first, coordinates_second, *turno); /* TODO*/
        check_Promotion(&(ped[0][0]), *turno);
        clear_screen();
        print_board_colors(ped);
        swapTurn(turno);
        if (checkWin(&(ped[0][0]), *turno, *modalita) == 0) {
            *turno = 0;
            break;
        }
    }
    if(*turno == 0) {
        cprint(green,"Thank you for playing MINI-LASKA!!\n"
                     "Would you like to play again? ( y / n )\n");
        scanf("%s", game);
        *modalita = 0;
        if (game[0] == 'y' || game[0] == 'Y') return true;
        else return false;
    }
    if(*turno < 0){
        *turno = turnBK;
        swapTurn(turno);
        return true;
    }
    return false;
}
