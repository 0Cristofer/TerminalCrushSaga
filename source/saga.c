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

		ctr_jogada = FALSE;
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
			jogo->board[i][j].mark = FALSE;

		}
	}

	menor = jogo->h > jogo->w ? jogo->w : jogo->h ;
	for(i = 0; i < menor; i++){
		jogo->board[i][i].type = rand() % jogo->n_sym;
	}
	printJogo(jogo, FALSE);
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
	*tam = 1;
	fila_t *fila, *fila_aux;
	pedra_t *pedra;

	fila = malloc(sizeof(fila_t));
	fila_aux = malloc(sizeof(fila_t));
	pedra = malloc(sizeof(pedra_t));

	//printf("coordenadas recebidas X - %d Y - %d\n",z.x, z.y);

	jogo->board[z.x][z.y].mark = TRUE;

	inicializaFila(fila);
	insereFila(fila, jogo->board[z.x][z.y]);

	inicializaFila(fila_aux);
	insereFila(fila_aux, jogo->board[z.x][z.y]);

	while(!filaVazia(fila)){
		removeFila(fila,pedra);
		//printf("Pedra sendo olhada: X - %d Y - %d Tipo =%d\n", pedra->coord.x, pedra->coord.y , pedra->type + 1);

		/* UP check*/
		if(!((pedra->coord.x - 1) < 0)){
			//printf("Entrou UP check\n");
			if (jogo->board[pedra->coord.x - 1][pedra->coord.y].mark != TRUE){
				//printf("Entrou UP mark\n");
				jogo->board[pedra->coord.x - 1][pedra->coord.y].mark = TRUE;

				if (jogo->board[pedra->coord.x - 1][pedra->coord.y].type == pedra->type){
					//printf("Entrou UP fila\n");
					insereFila(fila, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		/* RIGHT check*/
		if(!((pedra->coord.y + 1) >= jogo->w)){
			//printf("Entrou RIGHT check\n");
			if (jogo->board[pedra->coord.x][pedra->coord.y + 1].mark != TRUE){
				//printf("Entrou RIGHT mark\n");
				jogo->board[pedra->coord.x][pedra->coord.y + 1].mark = TRUE;

				if (jogo->board[pedra->coord.x][pedra->coord.y + 1].type == pedra->type){
					//printf("Entrou RIGHT fila\n");
					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					*tam = *tam + 1;
				}
			}
		}

		/* DOWN check*/
		if(!((pedra->coord.x + 1) >= jogo->h)){
			//printf("Entrou DOWN check\n");
			if (jogo->board[pedra->coord.x + 1][pedra->coord.y].mark!= TRUE){
				//printf("Entrou DOWN mark\n");
				jogo->board[pedra->coord.x + 1][pedra->coord.y].mark = TRUE;

				if (jogo->board[pedra->coord.x + 1][pedra->coord.y].type == pedra->type){
					//printf("Entrou DOWN fila\n");

					insereFila(fila, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		/*LEFT check */
		if(!((pedra->coord.y - 1)  < 0)){
			//printf("Entrou LEFT check\n");

			if (jogo->board[pedra->coord.x][pedra->coord.y - 1].mark!= TRUE){
				//printf("Entrou LEFT mark\n");
				jogo->board[pedra->coord.x][pedra->coord.y - 1].mark = TRUE;

				if (jogo->board[pedra->coord.x][pedra->coord.y - 1].type == pedra->type){
				//	printf("Entrou LEFT fila\n");

					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					*tam = *tam + 1;
				}
			}
		}
	}
	//getchar();
	//getchar();
	return fila_aux;
}

int testaJogada(game_t *jogo, coord_t a, coord_t b){
	//game_t* copia;
	int tam_a, tam_b, i, retorno;
	fila_t *fila_a, *fila_b;
	coord_t *explode_a, *explode_b, aux;
	pedra_t *pedra;

	retorno = FALSE;

	fila_a = malloc(sizeof(fila_t));
	fila_b = malloc(sizeof(fila_t));

	inicializaFila(fila_a);
	inicializaFila(fila_b);

	pedra = malloc(sizeof(pedra_t));

	/* Troca as pedras na board */
	*pedra = jogo->board[a.x][a.y];
	jogo->board[a.x][a.y] = jogo->board[b.x][b.y];
	jogo->board[b.x][b.y] = *pedra;

	aux = a;
	a = b;
	b = aux;

	jogo->board[a.x][a.y].coord = a;
	jogo->board[b.x][b.y].coord = b;


	printJogo(jogo,FALSE);

	/*Calcula os match3 */
	fila_a = match3(jogo, a, &tam_a);
	limpaMark(jogo);
	fila_b = match3(jogo, b, &tam_b);

	/* Destroca as pedras caso não houve um match3 */
	if(!((tam_a >= 3) || (tam_b >= 3))){
		*pedra = jogo->board[b.x][b.y];
		jogo->board[b.x][b.y] = jogo->board[a.x][a.y];
		jogo->board[a.x][a.y] = *pedra;

		jogo->board[a.x][a.y].coord = b;
		jogo->board[b.x][b.y].coord = a;
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
			system(SLEEP " 0.5");

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
			system(SLEEP " 0.5");
		}
		//Calcula e Printa score pela jogada?
	}

	/* Chama o preencheBoard */
	if(retorno){
		getchar();
		getchar();
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
	fila = malloc(sizeof(fila_t));
	fila_pop = malloc(sizeof(fila_t));

	for(i = 0; i < jogo->w; i++){
		for(j = 0; j < jogo->h; j++){
			if (jogo->board[j][i].type == -1){
				array[i]++;
			}
		}
	}


	for(i = 0; i < jogo->w; i++){
		if(array[i] > 0){ //tem estourados nessa coluna
			inicializaFila(fila); //free?
			inicializaFila(fila_pop); //free

			for(j = jogo->h - 1; j >= 0; j--){
				if (jogo->board[j][i].type != -1) {
					insereFila(fila, jogo->board[j][i]);
				} else{
					insereFila(fila_pop, jogo->board[j][i]);
				}
			}

			/* Para o numero de pedras estouradas de cada coluna, gera novas pedras */
			for(j = 0; j < array[i]; j++){
				removeFila(fila_pop, pedra);
				pedra->type = escolhePedra(jogo, pedra->coord);
				insereFila(fila, *pedra);
			}

			/* Re-insere essa coluna no board */
			for(j = jogo->h - 1; j >= 0; j--){
				removeFila(fila, pedra);
				pedra->coord.x = j;
				pedra->coord.y = i;
				jogo->board[j][i] = *pedra;
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
