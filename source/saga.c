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
	int controle = FALSE;
	coord a, b;

	while(controle == FALSE){
		leCoord(jogo->h, &a, &b);
		if(verifica(jogo, a, b)){
			if(testaJogada(jogo, a, b)){
				//VAI SER LOCO
				controle = TRUE;
			}
			else{
				//PRINTA QUE DEU ERRADO
			}
		}
		else{
			//PRINTA QUE NAO PODE
		}
	}
}

int verifica(game *jogo, coord a, coord b){
	if(
	   ((a.x < jogo->w) && (a.x >= 0) && (a.y < jogo->h) && (a.y >= 0) &&	//Verifica limites em altura e largura
            (b.x < jogo->w) && (b.x >= 0) && (b.y < jogo->h) && (b.y >= 0)) && 	// ||       ||
	   (!((a.x == b.x) && (a.y == b.y)))&& 					//Verifica se as coordenadas não são iguais
	   (
	     ( (a.x == b.x) && ( (a.y == (b.y - 1)) || (a.y == (b.y + 1)) ) ) ||//Verifica se as coordenadas são adjacentes
	     ( (a.y == b.y) && ( (a.x == (b.x - 1)) || (a.x == (b.x + 1)) ) ) ) // ||       ||
	   ){
		return TRUE;
	}
	return FALSE;
}

int testaJogada(game *jogo, coord a, coord b){
}
