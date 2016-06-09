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
#include "fila_lista_ligada/fila.h"

//Função que controla o fluxo do jogo
void mainGame(game_t *jogo){
	int opt, opt2;
	int ctr_jogada = FALSE;
	int ctr_game_t = TRUE;

	novoJogo(jogo);

	while(ctr_game_t){

		while(!ctr_jogada){
			opt = printJogo(jogo);

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
	}

}

//Cria o tabuleiro com peças aleatórias
void novoJogo(game_t *jogo){
	int i, j, menor;
	int *qt;
	srand(time(NULL));
	
	qt = malloc(jogo->n_sym*sizeof(int));
	for(i = 0; i < jogo->n_sym; i++){
		qt[i] = 0;
	}
	jogo->board = malloc(sizeof(pedra_t**) * jogo->h);
	for(i = 0; i < jogo->h; i++){
		jogo->board[i] = malloc(sizeof(pedra_t) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].type = -1;
			jogo->board[i][j].coord.x = i;
			jogo->board[i][j].coord.y = j;

		}
	}

	menor = jogo->h > jogo->w ? jogo->w : jogo->h ;
	for(i = 0; i < menor; i++){
		jogo->board[i][i].type = rand() % jogo->n_sym;
	}
	printJogo(jogo);
	for(i = 0; i < jogo->h; i++){
		for(j = 0;j < jogo->w; j++){
			jogo->board[i][j].type = i == j ? jogo->board[i][j].type : escolhePedra(jogo, jogo->board[i][j].coord);
			qt[jogo->board[i][j].type] += 1;
		}
	}
	for(i = 0; i < jogo->n_sym; i++){
			printf("\nsimbolo %d: %d vezes, %.2lf porcento \n", i, qt[i], ((qt[i]/(double)(jogo->h * jogo->w))*100) );
	}
	getchar();
	getchar();

}

int escolhePedra(game_t *jogo, coord_t a){
	int i, j, *ordem, menor = 0, n_0 = 1;
	double *percents, *n_percents, p, resto, soma = 0, r;

	percents = malloc(jogo->n_sym * sizeof(double));
	for(i = 0; i < jogo->n_sym; i++){
		percents[i] = 0;
	}

	for(i = 0; i < jogo->h; i++){
		if(jogo->board[i][a.y].type != -1){
			percents[jogo->board[i][a.y].type]++;
		}	
	}
	for(i = 0; i < jogo->w; i++){
		if(jogo->board[a.x][i].type != -1){
			percents[jogo->board[a.x][i].type]++;
		}
	}

	for(i = 0; i < jogo->n_sym; i++){
		percents[i] = percents[i]/(jogo->w + jogo->h - 1);
	}
	for(i = 1; i < jogo->n_sym; i++){
		if(percents[i] == percents[menor]){
			r = rand() % 2;
			if(r){
				menor = i;
			}
		}
		else if(percents[i] < percents[menor]){
			menor = i;
		}
	}

	p = 100 - percents[menor];
	p = p > 70 ? 70 : p;
	resto = 100 - p;

	for(i = 0; i < jogo->n_sym; i++){
		soma = i == menor ? soma : soma + percents[i];
	}
	for(i = 0; i < jogo->n_sym; i++){
		n_0 = i == menor ? n_0 : percents[i] == 0 ? n_0 + 1 : n_0;
	}
	for(i = 0; i < jogo->n_sym; i++){
		percents[i] = i == menor ? p/n_0 : percents[i] == 0 ? p/n_0 : (percents[i] / soma) * resto;
	}

	soma = 0;
	r = rand() % 100 + 1;
	ordem = ordena(percents, jogo->n_sym);
	n_percents = malloc(jogo->n_sym * sizeof(double));
	
	for(i = 0; i < jogo->n_sym; i++){
		n_percents[ordem[i]] = percents[i];
	}
	for(i = 0; i < jogo->n_sym; i++){
		soma += n_percents[i];
		if(r <= soma){
			for(j = 0; j < jogo->n_sym; j++){
				if(ordem[j] == i){
					return j;
				}
			}
		}
	}
}

//Controla a jogada
int jogada(game_t *jogo){
	int controle = FALSE;
	coord_t a, b;
	leCoord(jogo->h, &a, &b);
	if(verifica(jogo, a, b)){
		printf("VERIFIQUEI");
		if(testaJogada(jogo, a, b)){
			//VAI SER LOCO
			printf("FOI LOUCO, i mean vai ser");
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
		printf("Jogada impossível, as pedra_ts não são adjacentes ou não existem!");
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

fila_t* match3(game_t *jogo, coord_t z){
	int aux;
	fila_t* fila, fila_aux;
	/*pedra_t* pedra;

	pedra = malloc(sizeof(pedra_t));

	jogo->board[z.x][z.y].mark = TRUE;

	inicializaFila(fila);
	insereFila(fila, jogo->board[z.x][z.y]);

	inicializaFila(fila_aux);
	insereFila(fila_aux, jogo->board[z.x][z.y]);


	while(!filaVazia(fila)){
		aux = removeFila(fila,pedra);
		pedra->mark = TRUE;

		/* UP check
		if(!(pedra->coord.y + 1 > jogo->h)){
			if (pedra->mark != TRUE){
				jogo->board[pedra->coord.x][pedra->coord.y+1].mark = TRUE;

				if (jogo->board[pedra->coord.x][pedra->coord.y+1].type == pedra->type){
					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y+1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y+1]);
				}
			}
		}


		/* RIGHT check
		if(!(pedra->coord.x + 1 > jogo->w)){
			//RIGHT
		}

		/* DOWN check
		if(!(pedra->coord.y - 1 < 0)){
			//DOWN
		}

		/*LEFT check 
		if(!(pedra->coord.y - 1  < 0)){
			//LEFT
		}


	}*/return fila;
}

int testaJogada(game_t *jogo, coord_t a, coord_t b){
	/*game_t* copia;
	int type_aux;
	coord_t* lista_a, lista_b;

	memcpy(copia, jogo, sizeof(game_t));

	/* Troca as pedra_ts na board copiada 
	type_aux = copia->board[a.x][a.y].type;
	copia->board[a.x][a.y] = copia->board[b.x][b.y];
	copia->board[b.x][b.y].type = type_aux;

	lista_a = match3(copia,a);
	lista_b = match3(copia,b);

	//explode as listas
*/	return 0;
}

int *ordena(double *vet, int tam){
	int i, j;
	int *aux;
	aux = malloc(tam * sizeof(int));

	for(i = 0; i < tam; i++){
		aux[i] = (tam - 1);
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(i != j){
				if(vet[i] > vet[j]){
					aux[i] = aux[i] - 1;
				}
				else if(vet[i] == vet[j]){
					if(i < j){
						aux[i] = aux[i] - 1;
					}
				}
			}
		}
	}

	return aux;
}

