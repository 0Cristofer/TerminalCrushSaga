/*Contém a lógica principal do Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "saga.h"
#include "util.h"

void mainGame(game *jogo){

	novoJogo(jogo);
}

void novoJogo(game *jogo){
	int i, j;
	srand(time(NULL));

	jogo->board = malloc(sizeof(int**) * jogo->h);
	for(i = 0; i < jogo->h; i++){
		jogo->board[i] = malloc(sizeof(int) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j] = rand() % jogo->n_sym + 1;
		}
	}

	printJogo(jogo);
}

void printJogo(game *jogo){
	int i, j;

	system(CLS);

	for(i = 0; i < jogo->h; i++){
		printf("\t\t\t\t\t\t\t");
		for(j = 0; j < jogo->w; j++){
			printf("%d  ", jogo->board[i][j]);
		}
		printf("\n");
	}
}
