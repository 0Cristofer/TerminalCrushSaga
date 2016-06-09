/*Arquivo header de saga.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef SAGA
#define SAGA

#include "util.h"

//Struct que representa uma peça do tabuleiro
typedef struct{
	int type;
	int mark;
	coord_t coord;
}pedra_t;

//Representa os dados do jogo atual
typedef struct{
	pedra_t **board;
	int w;
	int h;
	int n_sym;
}game_t;

int verifica(game_t *jogo, coord_t a, coord_t b);
int testaJogada(game_t *jogo, coord_t a, coord_t b);
int jogada(game_t *jogo);
int preencheBoard(game_t *jogo);

void mainGame(game_t *jogo);
void novoJogo(game_t *jogo);
void limpaMark(game_t *jogo);

#endif
