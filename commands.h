#ifndef COMMANDS_H
#define COMMANDS_H
#include "board.h"

typedef struct{
    char* command;
    int duringGame;
} command_t;

int check_if_command(const command_t *commands,char* uInput);

bool command_exec(piece_t board[7][7],command_t *commands,int* turn, int n, bool isGame,int* modalita);

void command_init(command_t* list);

void command_get_names(int modalita);

#endif

