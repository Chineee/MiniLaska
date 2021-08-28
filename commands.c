#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "board.h"
#include <unistd.h>

char NAME1[20];
char NAME2[20];



int check_if_command(const command_t * commands,char* uInput){
    int i;
    for(i=0;i<9;i++){
        if (!strcmp(commands[i].command,uInput)) {
            return i;
        }
    }
    return -1;
}


int count_saves(){
    FILE * p = NULL;
    int counter = 0;
    if((p = fopen("sv1.bin","rb")) != NULL){
        counter++;
        fclose(p);
    }
    if((p = fopen("sv2.bin","rb")) != NULL){
        counter++;
        fclose(p);
    }
    if((p = fopen("sv3.bin","rb"))!= NULL){
        counter++;
        fclose(p);
    }

    return counter;
}


void command_save(piece_t board[7][7],int* turn, int* modalita){
    if(*turn == 0)
        return;
    else {
        FILE *saves = NULL;
        int sv_count, sv_choice;
        char input[10];
        char *remaining;
        sv_count = count_saves();
        if (sv_count == 0)
            saves = fopen("sv1.bin", "wb");
        else if (sv_count == 1)
            saves = fopen("sv2.bin", "wb");
        else if (sv_count == 2)
            saves = fopen("sv3.bin", "wb");
        else if (sv_count == 3) {
            cprint(yellow,"There are no empty slots available, would you like to rewrite one? Y/N:\n");
            scanf("%s", input);
            if (input[0] == 'y' || input[0] == 'Y') {
                cprint(yellow,"You can rewrite the slots: \n");
                cprint(green,"slot1 slot2 slot3\n");
                cprint(yellow,"Chose the number of the slot you would like to rewrite:\n");
                scanf("%s", input);
                sv_choice = strtol(input, &remaining, 10);
                if (strlen(remaining) != 0) {
                    cprint(red,"Invalid input format! Failed to save the game!\n");
                    return;
                }
                if (sv_choice > 3 || sv_choice < 1) {
                    clear_screen();
                    print_board_colors(board);
                    cprint(red,"The chosen slot doesn't exist! Failed to save the game!\n");
                    return;
                } else if (sv_choice == 1) {
                    cprint(green,"Rewriting slot 1\n");
                    saves = fopen("sv1.bin", "wb");
                } else if (sv_choice == 2) {
                    cprint(green,"Rewriting slot 2\n");
                    saves = fopen("sv2.bin", "wb");
                } else if (sv_choice == 3) {
                    cprint(green,"Rewriting slot 3\n");
                    saves = fopen("sv3.bin", "wb");
                }
                sleep(2);
            } else {
                clear_screen();
                print_board_colors(board);
                cprint(red,"The game has not been saved!\n");
                return;
            }
        }
        if (saves != NULL) {
            unsigned int len1 = strlen(NAME1) + 1,
                    len2 = strlen(NAME2) + 1;
            clear_screen();
            print_board_colors(board);
            fwrite(board, sizeof(piece_t), 49, saves);
            fwrite(turn, sizeof(int), 1, saves);
            fwrite(&len1,sizeof(int),1,saves);
            fwrite(NAME1,sizeof(char),len1,saves);
            fwrite(&len2,sizeof(int),1,saves);
            fwrite(NAME2,sizeof(char),len2,saves);
            fwrite(modalita,sizeof(int),1,saves);
            change_fg_color(yellow);
            if(sv_count < 3) {
                printf("Game has been successfully saved under slot %d!\n", sv_count + 1);
            }
            else printf("Game has been succesfully saved under slot %d!\n",sv_choice);
            reset_color();
        }
        fclose(saves);
    }
}

bool command_load(piece_t board[7][7],int* turn, int* modalita){
    FILE * saves = NULL;
    int av_slot, slot;
    int i;
    unsigned len1,len2;
    char input[10];
    char *remaining = NULL;
    av_slot = count_saves();
    if(av_slot == 0){
        cprint(red,"There are no available saves!\n");
        return false;
    }
    change_fg_color(yellow);
    printf("Available slots are:\n");
    change_fg_color(green);
    for(i = 1; i <= av_slot; i++)
        printf("slot %d  ",i);
    cprint(yellow,"\nInsert the number of the slot to load:\n");
    scanf("%s",input);
    slot = strtol(input,&remaining,10);
    if(strlen(remaining) != 0){
        cprint(red,"Wrong input format, failed to load game!\n");
        return false;
    }
    if(slot > 3 || slot < 1 || av_slot < slot){
        change_fg_color(red);
        printf("No save found in slot %d! Failed to load save!\n",slot);
        reset_color();
        return false;
    }
    else if(slot == 1){
        saves = fopen("sv1.bin", "rb");
    }
    else if(slot == 2){
        saves = fopen("sv2.bin", "rb");
    }
    else if(slot == 3){
        saves = fopen("sv3.bin", "rb");
    }
    if(saves == NULL){
        cprint(red,"Failed to load the save!\n");
        return false;
    }
    fread(board,sizeof(piece_t),49,saves);
    fread(turn,sizeof(int),1,saves);
    fread(&len1,sizeof(int),1,saves);
    fread(NAME1,sizeof(char),len1,saves);
    fread(&len2,sizeof(int),1,saves);
    fread(NAME2,sizeof(char),len2,saves);
    fread(modalita,sizeof(int),1,saves);
    fclose(saves);
    return true;
}

void command_clear(piece_t board[7][7], bool isGame){
    if(isGame) {
        clear_screen();
        print_board_colors(board);
    }
    else {
        clear_screen();
        print_Welcome();
    }
}

void commands_show(bool isGame,piece_t board[7][7]){
    char buf[10], *expect = "!back";
    clear_screen();
    cprint(yellow,"Here is a list of available commands: \n\n\n");
    cprint(green,"!start ");
    printf("- starts a new game. This one was obvious anyway.\n");
    cprint(green,"!rules ");
    printf("- shows a small how to play guide.\n");
    cprint(green,"!restart ");
    printf("- restarts the game. The turn will be changed from the initial one in pvp.\n");
    cprint(green,"!ff ");
    printf("- forfeits the game. For when you've just had enough.\n");
    cprint(green,"!clear ");
    printf("- clears the screen of your input. For those who just can't type it right.\n");
    cprint(green,"!save ");
    printf("- saves the game. Don't worry, your failures will be forgotten.\n");
    cprint(green,"!load ");
    printf("- loads a previously saved game. You probably forgot about it already.\n");
    cprint(green,"!exit ");
    printf("- exits the game. Don't forget to save before.\n\n\n\n");
    printf("Type !back to return.\n");
    while(strcmp(buf,expect) != 0)
        scanf("%s",buf);
    clear_screen();
    if(isGame)
        print_board_colors(board);
    else
        print_Welcome();
}


void command_get_names(int modalita){
    if(modalita == 1) {
        printf("Insert ");
        cprint(blue,"PLAYER1 ");
        printf("name:");
        scanf("%s",NAME1);
        printf("Insert ");
        cprint(red,"PLAYER2 ");
        printf("name:");
        scanf("%s", NAME2);
    }
    else {
        printf("Insert ");
        cprint(red,"PLAYER ");
        printf("name:");
        scanf("%s", NAME2);
        NAME1[0] = 'C';
        NAME1[1] = 'P';
        NAME1[2] = 'U';
        NAME1[3] = '\0';
    }
}


void command_restart(piece_t board[7][7], int *turn){
    char s[5];
    cprint(yellow,"Are you sure you want to restart the game? Y/N\n");
    scanf("%s",s);
    if(*s == 'y' || *s == 'Y'){
    init_game(board);
        *turn = -1;
    }
}

void command_exit(){
    cprint(green,"Thank you for playing MINI-LASKA!\n");
    sleep(2);
    exit(EXIT_SUCCESS);
}

void _print_laska_rules(){
    cprint(green,"Welcome to MINI-LASKA!\n\n");
    printf("There are 4 types of pieces:\n\n");
    print_piece(blue);
    printf(" - blue piece.                           ");
    print_piece(red);
    printf(" - red piece.\n\n");
    print_promoted_piece(blue);
    printf(" - promoted blue piece.                  ");
    print_promoted_piece(red);
    printf(" - promoted red piece.\n\n");
    printf("Mini Laska is a turn by turn game, with the goal of leaving your opponent without\n"
           "pieces or without any possible moves, if you succeed in doing so, you win the game!\n\n"
           "Simple pieces: ");
    print_piece(blue);
    print_piece(red);
    printf(" can only move and capture forward, while promoted \npieces: ");
    print_promoted_piece(blue);
    print_promoted_piece(red);
    printf(" can move and capture both forward and backwards!\n\n");
    printf("You can promote your piece by reaching the opposite end of the board, but so can your opponent,\n"
           "so be careful.\n When there is a capturing move available, the players are force to do it.\n"
           "This can lead to interesting tactics, so use it to your advantage.\n\n");
    printf("When captured, your piece will become the hostage of the enemy. You can free the hostage\n"
           "by capturing the piece holding hostage your pieces. Doing so will free your piece and leave\n"
           "it in the same place, while taking forward the enemy piece as a hostage! Capturing an enemy\n");
    printf( "piece that holds captive two of your pieces will free both of them, leaving a two levels piece\n"
           "behind! The enemy cannot capture both of your pieces at the same time, so when captured, the two\n"
           "level piece will leave one of your pieces standing.\n");
    printf("You can build up to three pieces one on top of another, if you keep capturing enemy pieces with a\n"
           "three levels piece, the newly captured enemy piece will be removed from the board.\n\n");
    print_promoted_piece(blue);
    printf(" - promoted piece.\n");
    print_promoted_piece(red);
    printf(" - promoted piece that was captured.\n");
    print_piece(red);
    printf(" - piece that was captured.\n");
    printf("\nAbove you see an example of a hostage situation. The promoted blue piece has taken hostage the\n"
           "promoted red piece and the simple red piece. Freeing them will leave behind the two level piece.\n");
    print_promoted_piece(red);
    printf(" - promoted red piece.\n");
    print_piece(red);
    printf(" - simple red piece.\n"
           "And produce the following two level piece:\n");
    print_piece(red);
    printf(" - simple red piece.\n");
    print_promoted_piece(blue);
    printf(" - promoted blue piece as a hostage.\n\n");

    cprint(green,"Good luck!\n\n\n\n");
}

void command_rules(bool game,piece_t board[7][7]){
    /* remove all the fucking exclamation marks and explain promoted pieces and explain that you can free hostages with promoted pieces as well
     * explain the forced capture, removal of pieces
     * every input from new line*/
    char buf[10], *expect = "!back";
    clear_screen();
    _print_laska_rules();
    printf("Type !back to return.\n");
    while(strcmp(buf,expect) != 0) {
        scanf("%s", buf);
    }
    if(game){
        clear_screen();
        print_board_colors(board);
    }
    else {
        clear_screen();
        print_Welcome();
    }

}

void command_ff(int *turn,piece_t board[7][7],int modalita){
    char s[10];
    if(modalita == 1) {
        if (*turn == 1) {
            cprint(yellow, "Are you sure you want to forfeit the match,");
            cprint(red, NAME2);
            cprint(yellow, "? Y/N:\n");
            scanf("%s", s);
            if (*s == 'y' || *s == 'Y') {
                print_victory(blue);
                cprint(blue, NAME1);
                printf(" has won the match!!!\n");
                *turn = 0;
                init_game(board);
            }
        }
        if (*turn == 2) {
            cprint(yellow, "Are you sure you want to forfeit the match,");
            cprint(blue, NAME1);
            cprint(yellow, "? Y/N:\n");
            scanf("%s", s);
            if (*s == 'y' || *s == 'Y') {
                print_victory(red);
                cprint(red, NAME2);
                printf(" has won the match!!!\n");
                *turn = 0;
                init_game(board);
            }
        }
    }
    else{
        cprint(yellow, "Are you sure you want to forfeit the match,");
        cprint(red, NAME2);
        cprint(yellow, "? Y/N:\n");
        scanf("%s", s);
        if (*s == 'y' || *s == 'Y') {
            print_victory(1);
            cprint(blue, NAME1);
            printf(" has won the match!!!\n");
            *turn = 0;
            init_game(board);
        }
        print_defeat();
        printf("The CPU has won the match!\n");
        *turn = 0;
        init_game(board);
    }
}

bool command_exec(piece_t board[7][7],command_t *commands,int* turn, int index, bool isGame, int* modalita){
   if(commands[index].duringGame == -1 && isGame == true) {

       cprint(red,"You cannot use this command while in a game!!");
       printf("\n");
       return isGame;
   }
   if(commands[index].duringGame == 1 && isGame == false){
       cprint(red,"You cannot use this command while not in a game!!");
       printf("\n");
       return isGame;
   }

   if (index == 0) {
       return true;
   }
   if (index == 1){
       command_ff(turn,board,*modalita);
       }
   if (index == 2) {
       command_rules(isGame, board);
   }
   if (index == 3)
       command_exit();
   if (index == 4) {
       commands_show(isGame, board);
   }
   if (index == 5){
       command_restart(board, turn);
       }
   if (index == 6)
       command_save(board, turn, modalita);
   if (index == 7) {
       bool temp = command_load(board, turn, modalita);
       return temp;
   }
   if (index == 8){
       command_clear(board, isGame);
   }
   return isGame;
}

void command_init(command_t* commands){
    /* command[i].duringGame determines if a command can be used during a game or not
     * -1 for not available during game!
     * 0 for available during both game and no game
     * 1 available only during game */
    commands[0].command = "!start";
    commands[0].duringGame = -1;
    commands[1].command = "!ff";
    commands[1].duringGame = 1;
    commands[2].command = "!rules";
    commands[2].duringGame = 0;
    commands[3].command = "!exit";
    commands[3].duringGame = 0;
    commands[4].command = "!commands";
    commands[4].duringGame = 0;
    commands[5].command = "!restart";
    commands[5].duringGame = 1;
    commands[6].command = "!save";
    commands[6].duringGame = 1;
    commands[7].command = "!load";
    commands[7].duringGame = 0;
    commands[8].command = "!clear";
    commands[8].duringGame = 0;
}

