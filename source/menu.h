/*Arquivo header de menu.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef MENU
#define MENU

//Nossas bibliotecas
#include "util.h"
#include "saga.h"

int printJogo(game_t *jogo, int op);
int confirma(int x, int y);
int mainMenu();

void leDados(game_t *jogo);
void printBoard(game_t *jogo);
void printaPorcetagens(game_t *jogo);
void leCoord(int h, coord_t *a, coord_t *b);
void printLado(int n);
void moveCursor(int x, int y);
void printCab();
void printTopo();
void printLogo();
void printTer();

#endif
