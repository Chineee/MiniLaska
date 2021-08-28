#ifndef COLORS_H
#define COLORS_H

enum colors {
    red,
    blue,
    black,
    white,
    yellow,
    green
};

typedef int select_color;

void setupConsole(void);

void change_bg_color(select_color x);

void reset_color();

void change_fg_color(select_color x);

void clear_screen();

void cprint(select_color x,char buffer[200]);
#endif
