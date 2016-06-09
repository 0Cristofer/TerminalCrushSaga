/*Contém a lógica principal do Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Nossos includes
#include "saga.h"
#include "util.h"
#include "menu.h"
#include "fila_lista_ligada/fila.h"

//Função que controla o fluxo do jogo
void mainGame(game_t *jogo){
	int opt, opt2;
	int ctr_jogada = FALSE;
	int ctr_game_t = TRUE;

	novoJogo(jogo);

	while(ctr_game_t){

		while(!ctr_jogada){
			opt = printJogo(jogo,TRUE);

			switch (opt) {
				case 1:
					ctr_jogada = jogada(jogo);
					break;

				case 2:
				//Shuffle
					break;

				case 3:
					opt2 = confirma(jogo->h + 18, 26);
					if (opt2){
						ctr_jogada = TRUE;
						ctr_game_t = FALSE;
					}
					break;

				default:
				moveCursor((jogo->h + 17), 26);
				printf("Opção inválida!");
				getchar();
				getchar();
				break;
			}
		}
		moveCursor((jogo->h + 17), 26);
		printf("CARALHO MANO NEM ACREDITO QUE ISSO RODOU!\n");
	}

}

//Cria o tabuleiro com peças aleatórias
void novoJogo(game_t *jogo){
	int i, j;
	srand(time(NULL));

	jogo->board = malloc(sizeof(pedra_t**) * jogo->h);
	for(i = 0; i < jogo->h; i++){
		jogo->board[i] = malloc(sizeof(pedra_t) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].type =  rand() % jogo->n_sym;
			jogo->board[i][j].coord.x = i;
			jogo->board[i][j].coord.y = j;
			jogo->board[i][j].mark = FALSE;

		}
	}
}

//Controla a jogada
int jogada(game_t *jogo){
	int controle = FALSE;
	coord_t a, b;
	leCoord(jogo->h, &a, &b);
	if(verifica(jogo, a, b)){
		//printf("VERIFIQUEI");
		if(testaJogada(jogo, a, b)){
			controle = TRUE;
		}
		else{
			moveCursor(jogo->h + 18, 35);
			printf("Jogada impossível, não gera um match 3!");
			fflush(stdout);
			system(SLEEP " 3");
		}
	}
	else{
		moveCursor(jogo->h + 18, 35);
		printf("Jogada impossível, as pedras não são adjacentes ou não existem!");
		fflush(stdout);
		system(SLEEP " 3");

	}
	return controle;
}

int verifica(game_t *jogo, coord_t a, coord_t b){
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

fila_t* match3(game_t *jogo, coord_t z, int* tam){
	*tam = 0;
	fila_t *fila, *fila_aux;
	pedra_t *pedra;

	fila = malloc(sizeof(fila_t));
	fila_aux = malloc(sizeof(fila_t));
	pedra = malloc(sizeof(pedra_t));

	inicializaFila(fila);
	insereFila(fila, jogo->board[z.x][z.y]);

	inicializaFila(fila_aux);
	insereFila(fila_aux, jogo->board[z.x][z.y]);

	while(!filaVazia(fila)){
		removeFila(fila,pedra);
		printf("Um while\n");

		/* UP check*/
		if(!(pedra->coord.y + 1 > jogo->h)){
			printf("Entrou UP check\n");
			if (pedra->mark != TRUE){
				printf("Entrou UP mark\n");

				jogo->board[pedra->coord.x][pedra->coord.y + 1].mark = TRUE;

				if (jogo->board[pedra->coord.x][pedra->coord.y + 1].type == pedra->type){
					printf("Entrou UP fila\n");
					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					*tam = *tam + 1;
				}
			}
		}

		/* RIGHT check*/
		if(!(pedra->coord.x + 1 > jogo->w)){
			printf("Entrou RIGHT check\n");
			if (pedra->mark != TRUE){
				printf("Entrou RIGHT mark\n");

				jogo->board[pedra->coord.x+1][pedra->coord.y].mark = TRUE;

				if (jogo->board[pedra->coord.x + 1][pedra->coord.y].type == pedra->type){
					printf("Entrou RIGHT fila\n");
					insereFila(fila, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		/* DOWN check*/
		if(!(pedra->coord.y - 1 < 0)){
			printf("Entrou DOWN check\n");
			if (pedra->mark != TRUE){
				printf("Entrou DOWN mark\n");

				jogo->board[pedra->coord.x][pedra->coord.y - 1].mark = TRUE;

				if (jogo->board[pedra->coord.x][pedra->coord.y - 1].type == pedra->type){
					printf("Entrou DOWN fila\n");

					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					*tam = *tam + 1;
				}
			}
		}

		/*LEFT check */
		if(!(pedra->coord.x - 1  < 0)){
			printf("Entrou LEFT check\n");

			if (pedra->mark != TRUE){
				printf("Entrou LEFT mark\n");

				jogo->board[pedra->coord.x - 1][pedra->coord.y].mark = TRUE;

				if (jogo->board[pedra->coord.x - 1][pedra->coord.y].type == pedra->type){
					printf("Entrou LEFT fila\n");

					insereFila(fila, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		pedra->mark = TRUE;
	}

	return fila_aux;
}

int testaJogada(game_t *jogo, coord_t a, coord_t b){
	//game_t* copia;
	int tam_a, tam_b, i, retorno;
	fila_t* fila_a, *fila_b;
	coord_t* explode_a, *explode_b;
	pedra_t *pedra;

	retorno = FALSE;

	fila_a = malloc(sizeof(fila_t));
	fila_b = malloc(sizeof(fila_t));


	inicializaFila(fila_a);
	inicializaFila(fila_b);

	pedra = malloc(sizeof(pedra_t));

	//printf("Antes do memcpy\n");
	//memcpy(copia, &jogo, sizeof(game_t));
	//printf("DEPOIS do memcpy\n");

	/* Troca as pedras na board */
	*pedra = jogo->board[a.x][a.y];
	jogo->board[a.x][a.y] = jogo->board[b.x][b.y];
	jogo->board[b.x][b.y] = *pedra;

	/*Calcula os match3 */
	fila_a = match3(jogo, a, &tam_a);
	limpaMark(jogo);
	fila_b = match3(jogo, b, &tam_b);

	/* Destroca as pedras caso não houve um match3 */
	if(!(tam_a >= 3 || tam_b >= 3)){
		*pedra = jogo->board[b.x][b.y];
		jogo->board[b.x][b.y] = jogo->board[a.x][a.y];
		jogo->board[a.x][a.y] = *pedra;
	}

	if(tam_a >= 3){
		retorno = TRUE;
		explode_a = malloc(sizeof(coord_t) * tam_a);
		i = 0;

		while(!filaVazia(fila_a)){
			removeFila(fila_a,pedra);
			explode_a[i] = pedra->coord;
			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;

			printJogo(jogo,FALSE);
			system(SLEEP " 1");

		}

		//Calcula e Printa score pela jogada?
	}

	if(tam_b >= 3){
		retorno = TRUE;
		explode_b = malloc(sizeof(coord_t) * tam_b);
		i = 0;

		while(!filaVazia(fila_b)){
			removeFila(fila_b,pedra);
			explode_b[i] = pedra->coord;
			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;

			printJogo(jogo,FALSE);
			system(SLEEP " 1");
		}
		//Calcula e Printa score pela jogada?
	}

	/* Chama o preencheBoard */
	if(retorno){
		preencheBoard(jogo);
	}

	return retorno;
}

int preencheBoard(game_t *jogo){
	fila_t* fila, *fila_pop;
	int i,j;
	int* array; //Guarda quantas pedras estouradas em cada coluna
	pedra_t* pedra;

	array = malloc(sizeof(int) * jogo->w);
	pedra = malloc(sizeof(pedra_t));


	for(i = 0; i < jogo->h; i++){
		for(j = 0; j < jogo->w; j++){
			if (jogo->board[i][j].type == -1){
				array[j]++;
			}
		}
	}

	for(j = 0; j < jogo->w; j++){
		if(array[j] > 0){ //tem estourados nessa coluna
			inicializaFila(fila); //free?
			inicializaFila(fila_pop); //free?

			for(i = 0; i < jogo->h; i++){
				if (jogo->board[i][j].type != -1) {
				insereFila(fila, jogo->board[i][j]);
				} else{
					insereFila(fila_pop, jogo->board[i][j]);
				}
			}

			for(i = array[j] + 1 ; i < jogo->h; i++){
				removeFila(fila_pop, pedra);
				pedra->type = rand() % jogo->n_sym; //escolhePedra(jogo, pedra->coord);
				insereFila(fila, *pedra);
			}

			/* Re-insere essa coluna no board */
			for(i = 0; i < jogo->h; i++){
				removeFila(fila, pedra);
				pedra->coord.x = j;
				pedra->coord.y = i;
				jogo->board[i][j] = *pedra;
			}
		}
	}

}

void limpaMark(game_t *jogo){
	int i,j;
	for(i = 0; i < jogo->h; i++){
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].mark = FALSE;
		}
	}
}
