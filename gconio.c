#include "gconio.h"

#ifdef _WIN32
// --- Definições para Windows ---
WORD __gconio_h_ansi_fg = WHITE;
WORD __gconio_h_ansi_bg = BLACK << 4;

void delay(unsigned long milliseconds) {
    Sleep(milliseconds);
}

void gotoxy(short int x, short int y) {
    COORD cxy = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy);
}

void textcolor(int newcolor) {
    __gconio_h_ansi_fg = newcolor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(__gconio_h_ansi_fg | __gconio_h_ansi_bg));
}

void textbackground(int newcolor) {
    __gconio_h_ansi_bg = newcolor << 4;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(__gconio_h_ansi_fg | __gconio_h_ansi_bg));
}

int wherex(void) {
    CONSOLE_SCREEN_BUFFER_INFO conScrBufInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conScrBufInfo);
    return conScrBufInfo.dwCursorPosition.X;
}

int wherey(void) {
    CONSOLE_SCREEN_BUFFER_INFO conScrBufInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conScrBufInfo);
    return conScrBufInfo.dwCursorPosition.Y;
}
#endif // Fim das definições para Windows

// --- Definições Comuns ---
void clrscr(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
