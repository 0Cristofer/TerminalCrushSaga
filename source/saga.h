/*Arquivo header de saga.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef SAGA
#define SAGA

#include "util.h"

typedef struct{
    int type;
    int mark;
} pedra;

typedef struct{
    pedra **board;
	int w;
	int h;
	int n_sym;
} game;

void mainGame(game *jogo);
void novoJogo(game *jogo);
void jogada(game *jogo);


#endif
