#ifndef __GCONIO_H
#define __GCONIO_H

#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

// --- Definição das Cores ---
enum COLORS {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA,
    YELLOW, WHITE
};

#ifdef __cplusplus
extern "C" {
#endif

// --- Declaração de Variáveis Externas ---
// "extern" diz ao compilador: "esta variável existe, mas está noutro ficheiro"
#ifdef _WIN32
extern WORD __gconio_h_ansi_fg;
extern WORD __gconio_h_ansi_bg;
#else
extern int __gconio_h_ansi_fg;
extern int __gconio_h_ansi_bg;
#endif


void clrscr(void);
void delay(unsigned long milliseconds);
void gotoxy(short int x, short int y);
void textbackground(int newcolor);
void textcolor(int newcolor);


#ifdef _WIN32
int wherex(void);
int wherey(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
