/*Arquivo header de menu.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef MENU
#define MENU

//Nossas bibliotecas
#include "util.h"
#include "saga.h"

int confirma(int x, int y);
int printJogo(int op);
int mainMenu();

void leCoord(int h, coord_t *a, coord_t *b);
void printCombo(int tam, int combo);
void moveCursor(int x, int y);
void printLado(int n);
void printaPorcetagens();
void printBoard();
void printTopo();
void printLogo();
void printCab();
void printTer();
void leDados();

#endif
