#include <stdio.h>
#include "pvp.h"
#include "cpu_bot.h"
#include "commands.h"

extern char NAME2[20];
extern char NAME1[20];
extern command_t commands[10];


int main() {
    int modalita = 0,
            turno = 0,
            com_index = -1;
    bool game = false;
    piece_t ped[7][7];
    char user_input[15];
    command_init(commands);
    setupConsole();
    print_Welcome();
    init_game(ped);


    while (!game) {
        cprint(yellow,"Type ");
        cprint(green,"!start ");
        cprint(yellow, "to start a new game or ");
        cprint(green, "!commands ");
        cprint(yellow,"to see the available commands!\n");
        scanf("%s", user_input);
        com_index = check_if_command(commands, user_input);
        if(com_index >= 0){
            game = command_exec(ped,commands,&turno, com_index,game,&modalita);
        }

        else {
            cprint(red,"Error, the inserted input is not a commands!\n");
        }
    }

    while (game) {
        if(modalita == 0) {
            while(1) {
                cprint(yellow,"Choose the game mode:\n");
                printf("1 for PvP!\n2 for PvE!\n");
                scanf("%s", user_input);
                if(user_input[0] == '1') {
                    modalita = 1;
                    break;
                }
                if(user_input[0] == '2'){
                    modalita = 2;
                    break;
                }
                else {
                 cprint(red,"The chosen mode doesn't exist!\n");
                }
            }

        }
        if (modalita == 1) {
            if(turno == 0) {
                cprint(yellow,"You have chosen:Player vs Player!!\n");
                command_get_names(modalita);
            }
            game = player_vs_player(ped, &modalita, &turno);
        }
        else if (modalita == 2) {
            if(turno == 0) {
                cprint(yellow,"You have chosen: Player vs Environment\n");
                command_get_names(modalita);
            }
            turno = 1;
            game = player_vs_cpu(ped,&turno,&modalita);
        }
    }
    return 0;
}


