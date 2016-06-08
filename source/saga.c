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
	
	
	void inGame(){
		opt = printJogo(jogo);

		switch (opt) {
			case 1:
				jogada(jogo);
				inGame();
				break;

			case 2:
				//Shuffle
				inGame();
				break;

			case 3:
				break;

			default:
				moveCursor((jogo->h + 16), 26);
				printf("Opção inválida!");
				getchar();
				getchar();
				inGame();
				break;
		}
	}

	inGame();
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

//Controla a jogada
void jogada(game *jogo){
		coord a, b;

		moveCursor((jogo->h + 16), 26);
		printf(" , | , ");
		moveCursor((jogo->h + 16), 26);
		scanf(" %d", &a.x);
		moveCursor((jogo->h + 16), 28);
		scanf(" %d", &a.y);
		moveCursor((jogo->h + 16), 30);
                scanf(" %d", &b.x);
                moveCursor((jogo->h + 16), 32);
                scanf(" %d", &b.y);
		//TODO ANTI-TROLL SYSTEM




}
