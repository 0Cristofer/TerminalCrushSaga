/*Contém a lógica principal do Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer e Bruno*/

//Nossas bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Nossos includes
#include "util.h"
#include "saga.h"
#include "menu.h"
#include "fila_lista_ligada/fila.h"

/* Função que controla o fluxo do jogo */
void mainGame(game_t *jogo){
	int opt, opt2;
	int ctr_jogada = FALSE;
	int ctr_game_t = TRUE;

	novoJogo(jogo);

	while(ctr_game_t){ //Enquanto há jogo

		while(!ctr_jogada){ //Enquanto não for ecolhida jogada válida
			opt = printJogo(jogo, TRUE);

			switch (opt) {
				case 1: //Jogar
					ctr_jogada = jogada(jogo);
					break;

				case 2: //Shuffle
					opt2 = confirma(jogo->h + 18, 26);
					if(opt2){
						novoJogo(jogo);
					}
					break;

				case 3: //Sair
					opt2 = confirma(jogo->h + 18, 26);
					if(opt2){
						ctr_jogada = TRUE;
						ctr_game_t = FALSE;
					}
					break;

				default:
					moveCursor((jogo->h + 17), 26);
					printf("Opção inválida!");
					espera();
					break;
			}
		}

		ctr_jogada = FALSE;
	}

}

/* Cria o tabuleiro inicial */
void novoJogo(game_t *jogo){
	int i, j, menor;
	srand(time(NULL));

	jogo->board = malloc(sizeof(pedra_t*) * jogo->h);

	for(i = 0; i < jogo->h; i++){ //Preenche o tabuleiro com os dados iniciais
		jogo->board[i] = malloc(sizeof(pedra_t) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].type = -1;
			jogo->board[i][j].coord.x = i;
			jogo->board[i][j].coord.y = j;
			jogo->board[i][j].mark = FALSE;
			jogo->board[i][j].mark2 = FALSE; //testando implementação com duas marcas
		}
	}

	menor = jogo->h > jogo->w ? jogo->w : jogo->h; //Verifica qual dos lados é maior

	for(i = 0; i < menor; i++){ //Preenche a diagonal principal com peças aleatórias
		jogo->board[i][i].type = rand() % jogo->n_sym;
	}

	for(i = 0; i < jogo->h; i++){ //Preenche o resto do tabuleiro com peças escolhidas pelo escolhePedra
		for(j = 0;j < jogo->w; j++){
			jogo->board[i][j].type = i == j ? jogo->board[i][j].type : escolhePedra(jogo, jogo->board[i][j].coord);
		}
	}

	jogo->score = 0;

}

/* Escolhe uma pedra a partir dos dados da linha e coluna de sua coordenada */
int escolhePedra(game_t *jogo, coord_t a){
	int i, j;
	int menor = 0;
	int n_0 = 1;
	int *ordem;
	double p, resto, r;
	double soma = 0;
	double *percents, *n_percents;

	percents = malloc(jogo->n_sym * sizeof(double));

	for(i = 0; i < jogo->n_sym; i++){
		percents[i] = 0;
	}

	for(i = 0; i < jogo->h; i++){ //Calcula a quantidade de peças de cada tipo na coluna do elemento
		if(jogo->board[i][a.y].type != -1){
			percents[jogo->board[i][a.y].type]++;
		}
	}

	for(i = 0; i < jogo->w; i++){ //Calcula a quantidade de peças de cada tipo na linha do elemento
		if(jogo->board[a.x][i].type != -1){
			percents[jogo->board[a.x][i].type]++;
		}
	}

	for(i = 0; i < jogo->n_sym; i++){ //Calcula a porcentagem de cada tipo
		percents[i] = percents[i]/(jogo->w + jogo->h - 1);
	}

	for(i = 1; i < jogo->n_sym; i++){ //Verifica qual a menor porcentagem
		if(percents[i] == percents[menor]){ //Se hover iguais, ramdomiza sua colocação
			r = rand() % 2;
			if(r){
				menor = i;
			}
		}
		else if(percents[i] < percents[menor]){
			menor = i;
		}
	}

	p = 100 - percents[menor]; //Inverte a porcentagem do menor
	p = p > 70 ? 70 : p; //Caso for maior que 70, diminui ela para 70
	resto = 100 - p; //Para distribuição entre os outros elementos

	for(i = 0; i < jogo->n_sym; i++){ //Calcula quantos elementos do tipos não-menor há
		soma = i == menor ? soma : soma + percents[i];
	}

	for(i = 0; i < jogo->n_sym; i++){ //Cuida do caso de haver zeros
		n_0 = i == menor ? n_0 : percents[i] == 0 ? n_0 + 1 : n_0;
	}

	for(i = 0; i < jogo->n_sym; i++){ //Calcula quantos porcento cada tipo não-menor representa entre eles
		percents[i] = i == menor ? p/n_0 : percents[i] == 0 ? p/n_0 : (percents[i] / soma) * resto;
	}

	soma = 0;
	r = rand() % 100 + 1; //Aleatoriza um número de 1 a 100
	ordem = ordena(percents, jogo->n_sym); //Recebe a ordem das porcentagens

	n_percents = malloc(jogo->n_sym * sizeof(double));

	for(i = 0; i < jogo->n_sym; i++){ //Preenche uma lista com as porcentagens ordenadas
		n_percents[ordem[i]] = percents[i];
	}

	for(i = 0; i < jogo->n_sym; i++){
		soma += n_percents[i];

		if(r <= soma){ //Se a soma das porcentagens até o momento chegarem no numero gerado
			for(j = 0; j < jogo->n_sym; j++){ //Procura qual dos tipos ele representa
				if(ordem[j] == i){
					return j;
				}
			}
		}
	}

}

/* Retorna uma lista com a posição correta de cada elemento */
int *ordena(double *vet, int tam){
	int i, j;
	int *aux;

	aux = malloc(tam * sizeof(int));

	for(i = 0; i < tam; i++){ //Inicializa com a lista com todos os elementos estando em "último"
		aux[i] = (tam - 1);
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(i != j){
				if(vet[i] > vet[j]){ //Se o elemento for maior, diminui em 1 a posição dele
					aux[i] = aux[i] - 1;
				}
				else if(vet[i] == vet[j]){ //Se eles forem iguais, prioriza o elemento da esquerda
					if(i < j){
						aux[i] = aux[i] - 1;
					}
				}
			}
		}
	}

	return aux;
}

/* Controla a jogada */
int jogada(game_t *jogo){
	int controle = FALSE;
	int score = 0;
	coord_t a, b;

	leCoord(jogo->h, &a, &b);

	if(verifica(jogo, a, b)){
		if(testaJogada(jogo, a, b, &score)){
			controle = TRUE;
			while (controle){
				printJogo(jogo, FALSE);
				fflush(stdout);
				system(SLEEP " 1.5");
				controle = verificaBoard(jogo, &score);
			}
			controle = TRUE;
		}
		else{
			moveCursor(jogo->h + 18, 55);
			printf("Jogada impossível, não gera um match 3!");
			fflush(stdout);
			system(SLEEP " 2");
		}
	}
	else{
		moveCursor(jogo->h + 18, 35);
		printf("Jogada impossível, as pedras não são adjacentes ou não existem!");
		fflush(stdout);
		system(SLEEP " 2");
	}

	jogo->score += score;

	return controle;
}

/* Verifica se é possível fazer a jogada (as pedras são adjacentes e são coordenadas válidas) */
int verifica(game_t *jogo, coord_t a, coord_t b){
	if(
	   ((a.x < jogo->h) && (a.x >= 0) && (a.y < jogo->w) && (a.y >= 0) &&	//Verifica limites em altura e largura
            (b.x < jogo->h) && (b.x >= 0) && (b.y < jogo->w) && (b.y >= 0)) && 	// ||       ||
	   (!((a.x == b.x) && (a.y == b.y))) && 														//Verifica se as coordenadas não são iguais
	   (
	     ( (a.x == b.x) && ( (a.y == (b.y - 1)) || (a.y == (b.y + 1)) ) ) ||//Verifica se as coordenadas são adjacentes
	     ( (a.y == b.y) && ( (a.x == (b.x - 1)) || (a.x == (b.x + 1)) ) ) ) // ||       ||
	   ){
		return TRUE;
	}
	return FALSE;
}

/* Lê o tabuleiro procurando matchs */
int verificaBoard(game_t *jogo, int *score){
	int i, j;
	int retorno = FALSE;
	int tam = 1;
	int combo = 0;
	pedra_t *pedra;
	fila_t *fila;

	pedra = malloc(sizeof(pedra_t));
	fila = malloc(sizeof(fila_t));

	inicializaFila(fila);

	for(i = 0; i < jogo->h; i++){ //Passa pelo tabuleiro testando se há novos matchs
		for(j = 0; j < jogo->w; j++){
			if(jogo->board[i][j].mark2 != TRUE){
				fila = match3(jogo, jogo->board[i][j].coord, &tam);
				limpaMark(jogo, 1);
			}

			while(!filaVazia(fila)){
				removeFila(fila, pedra);
				jogo->board[pedra->coord.x][pedra->coord.y].mark2 = TRUE; //Marca o elemento para ele não ser testado novamente

				if(tam >= 3){
					retorno = TRUE;
					jogo->board[pedra->coord.x][pedra->coord.y].type = -1;
					printJogo(jogo, FALSE);
					fflush(stdout);
					system(SLEEP " 0.3");

				}
			}

			if(tam >= 3){
				combo++;
				*score += calcScore(jogo , tam, combo);
			}

		tam = 1;
		}
	}
	limpaMark(jogo, 2);

	free(pedra);
	free(fila);

	if(retorno){
		system(SLEEP " 0.5");
		preencheBoard(jogo);
	}

	return retorno;
}

/* Algoritmo de procura em largura para match3 */
fila_t *match3(game_t *jogo, coord_t z, int *tam){
	*tam = 1; //Quantidade de elementos na fila
	fila_t *fila, *fila_aux;
	pedra_t *pedra;

	pedra = malloc(sizeof(pedra_t));
	fila = malloc(sizeof(fila_t));
	fila_aux = malloc(sizeof(fila_t));

	jogo->board[z.x][z.y].mark = TRUE; //Marca a primeira pedra como visistada

	inicializaFila(fila);
	insereFila(fila, jogo->board[z.x][z.y]);

	inicializaFila(fila_aux);
	insereFila(fila_aux, jogo->board[z.x][z.y]);

	//Preenche e esvazia a fila principal conforme acha pedras do mesmo tipo
	while(!filaVazia(fila)){
		removeFila(fila, pedra);

		/* UP check*/
		if(!((pedra->coord.x - 1) < 0)){
			//printf("Entrou UP check\n");
			if (jogo->board[pedra->coord.x - 1][pedra->coord.y].mark != TRUE){
				//printf("Entrou UP mark\n");
				jogo->board[pedra->coord.x - 1][pedra->coord.y].mark = TRUE;

				if (jogo->board[pedra->coord.x - 1][pedra->coord.y].type == pedra->type){ //Se não estiver marcada e for do mesmo tipo, coloca na fila
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
					//printf("Entrou LEFT fila\n");

					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					*tam = *tam + 1;
				}
			}
		}
	}

	free(pedra);
	free(fila);

	return fila_aux;
}

//Recebe as duas coordenadas da jogada e verifica se fazem match3
int testaJogada(game_t *jogo, coord_t a, coord_t b, int *score){
	int i, tam_a, tam_b, retorno;
	coord_t aux;
	fila_t *fila_a, *fila_b;
	pedra_t *pedra;

	score = malloc(sizeof(int));

	retorno = FALSE;

	pedra = malloc(sizeof(pedra_t));
	fila_a = malloc(sizeof(fila_t));
	fila_b = malloc(sizeof(fila_t));

	inicializaFila(fila_a);
	inicializaFila(fila_b);


	/* Troca as pedras no board */
	*pedra = jogo->board[a.x][a.y];
	jogo->board[a.x][a.y] = jogo->board[b.x][b.y];
	jogo->board[b.x][b.y] = *pedra;

	//Troca as coordenadas
	aux = a;
	a = b;
	b = aux;
	jogo->board[a.x][a.y].coord = a;
	jogo->board[b.x][b.y].coord = b;

	printJogo(jogo, FALSE); //firulas
	fflush(stdout);
	system(SLEEP " 0.7");

	/*Calcula os match3 */
	fila_a = match3(jogo, a, &tam_a);
	limpaMark(jogo, 1);
	fila_b = match3(jogo, b, &tam_b);
	limpaMark(jogo, 1);

	/* Destroca as pedras caso não houve um match3 */
	if(!((tam_a >= 3) || (tam_b >= 3))){
		*pedra = jogo->board[b.x][b.y];
		jogo->board[b.x][b.y] = jogo->board[a.x][a.y];
		jogo->board[a.x][a.y] = *pedra;

		jogo->board[a.x][a.y].coord = a;
		jogo->board[b.x][b.y].coord = b;
	}
	else{
		retorno = TRUE;
	}

	/* Esvazia a primeira fila, se a fila for maior que 3 (formou match), atribui seu tipo para -1 ("vazio") e escreve na tela */
	while(!filaVazia(fila_a)){
		removeFila(fila_a, pedra);

		if(tam_a >= 3){
			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;
			printJogo(jogo, FALSE);
			fflush(stdout);
			system(SLEEP " 0.3");
		}

	}

	if (tam_a >= 3 ) *score += calcScore(jogo, tam_a, 0);

	printf("valor score ate aqui %d\n", *score);

	/* Mesmo para a segunda fila */
	while(!filaVazia(fila_b)){
		removeFila(fila_b, pedra);

		if(tam_b >= 3){
			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;
			printJogo(jogo,FALSE);
			fflush(stdout);
			system(SLEEP " 0.3");
		}

	}
	if (tam_b >= 3 ) *score += calcScore(jogo, tam_b, 0);


	free(pedra);
	free(fila_a);
	free(fila_b);

	/* Se formou match, repreenche o tabuleiro */
	if(retorno){
		//espera();
		preencheBoard(jogo);
	}

	return retorno;
}

/* Re-preenche o tabuleiro com novas pedras */
void preencheBoard(game_t *jogo){
	int i, j;
	pedra_t* pedra;
	int* array; //Guarda quantas pedras estouradas em cada coluna
	fila_t *fila, *fila_pop;

	array = malloc(sizeof(int) * jogo->w);
	pedra = malloc(sizeof(pedra_t));
	fila = malloc(sizeof(fila_t));
	fila_pop = malloc(sizeof(fila_t));

	for(i = 0; i < jogo->w; i++){
		array[i] = 0;
	}

	for(i = 0; i < jogo->w; i++){ //Anda na largura contando quantas pedras estouradas houve em sua respectiva coluna
		for(j = 0; j < jogo->h; j++){
			if (jogo->board[j][i].type == -1){
				array[i]++;
			}
		}
	}


	for(i = 0; i < jogo->w; i++){ //Anda na largura preenchendo
		if(array[i] > 0){ //Se há estourados nessa coluna
			inicializaFila(fila);
			inicializaFila(fila_pop);

			for(j = jogo->h - 1; j >= 0; j--){ //Itera de baixo para cima colocando as peças na fila
				if (jogo->board[j][i].type != -1) { //Se a pedra já existe coloca na fila principal, se não na secundária
					insereFila(fila, jogo->board[j][i]);
				} else{
					insereFila(fila_pop, jogo->board[j][i]);
				}
			}

			/* Para o numero de pedras estouradas de cada coluna, gera novas pedras e insere na fila principal */
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

	free(pedra);
	free(array);
	free(fila);
	free(fila_pop);
}

//Passa no tabuleiro desmarcando as peças
void limpaMark(game_t *jogo, int type){
	int i, j;

	for(i = 0; i < jogo->h; i++){
		for(j = 0; j < jogo->w; j++){
			if(type == 1){
				jogo->board[i][j].mark = FALSE;
			}
			else{
				jogo->board[i][j].mark2 = FALSE;
			}
		}
	}

}

void espera(){
	getchar();
	getchar();
}
