/*Contém a lógica principal do Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Nossos includes
#include "saga.h"
#include "util.h"
#include "menu.h"

//Função que controla o fluxo do jogo
void mainGame(game *jogo){
	int opt;

	novoJogo(jogo);

	do{
		opt = printBoard(jogo);

		switch (opt) {
			case 1:
				jogada(jogo);
				break;

			case 2:
				//Shuffle
				break;

			case 3:
				break;

			default:
				printf("Opção inválida!");
				break;
		}
	} while (opt !=3);
}

//Cria o tabuleiro com peças aleatórias
void novoJogo(game *jogo){
	int i, j;
	srand(time(NULL));

	jogo->board = malloc(sizeof(pedra**) * jogo->h);
	for(i = 0; i < jogo->h; i++){
		jogo->board[i] = malloc(sizeof(pedra) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].type =  rand() % jogo->n_sym + 1;
		}
	}
}

void jogada(game *jogo){
		coord a,b;
		printf(TAB);
		scanf(" %d %d", &a.x, &a.y);
		printf(TAB);
		scanf(" %d %d", &b.x, &b.y);
		//TODO ANTI-TROLL SYSTEM




}
