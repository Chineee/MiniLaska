#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include "colors.h"
#include <stdlib.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }

    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;

    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }
}

void clear_screen() {
    system("cls");
}


void change_bg_color(select_color x){
    if (x == red)
        printf("\x1b[41m");
    if (x == blue)
        printf("\x1b[44m");
    if (x == white)
        printf("\x1b[107m");
}

void reset_color(){
    printf("\x1b[40m\x1b[97m");
}

void change_fg_color(select_color x){
    if(x == red)
        printf("\x1b[31m");
    if(x == blue)
        printf("\x1b[34m");
    if(x == black)
        printf("\x1b[30m");
    if(x == yellow)
        printf("\x1b[33m");
    if(x == green)
        printf("\x1b[92m");

}

void cprint(select_color x,char buffer[200]){
    change_fg_color(x);
    printf("%s",buffer);
    reset_color();
}

#else
#include <stdio.h>
#include "colors.h"
#include <stdlib.h>

void setupConsole(){

  }
  void change_bg_color(select_color x){
    if (x == red)
        printf("\x1b[41m");
    if (x == blue)
        printf("\x1b[44m");
    if (x == white)
        printf("\x1b[107m");
}

void reset_color(){
        printf("\x1b[40m\x1b[97m");
}

void change_fg_color(select_color x){
    if (x == red)
        printf("\x1b[31m");
    if (x == blue)
        printf("\x1b[34m");
    if (x == black)
        printf("\x1b[30m");
    if (x == yellow)
        printf("\x1b[33m");

}

void clear_screen() {
    system("clear");
}

void cprint(select_color x,char buffer[200]){
    change_fg_color(x);
    printf("%s",buffer);
    reset_color();
}

#endif
