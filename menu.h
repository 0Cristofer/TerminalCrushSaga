/*Arquivo header de menu.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef MENU
#define MENU

#include "util.h"

int mainMenu();

void leDados(game *jogo);
void printCab();
void printTopo();
void printLado(int n);
void printLogo();
void printTer();
void moveCursor(int x, int y);
void printJogo(game *jogo);

#endif
