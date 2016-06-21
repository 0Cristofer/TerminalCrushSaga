/*Contém a lógica principal do Terminal Crush Saga*/
/*Data: 31/05/2016 */
/*Autor: Cristofer e Bruno*/

/*Nossas bibliotecas*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/*Nossos includes*/
#include "util.h"
#include "saga.h"
#include "menu.h"
#include "fila_lista_ligada/fila.h"

/* Função que controla o fluxo do jogo */
void mainGame(){
	int opt, opt2;
	int ctr_jogada = FALSE;
	int ctr_game = TRUE;

	novoJogo(FALSE);

	while(ctr_game){ /*Enquanto há jogo*/

		while(!ctr_jogada){ /*Enquanto não for ecolhida jogada válida*/
			opt = printJogo(TRUE);

			switch (opt) {
				case 1: /*Jogar*/
					ctr_jogada = jogada();
					break;

				case 2: /*Shuffle*/
					opt2 = confirma(jogo->h + 18, 26);
					if(opt2){
						novoJogo(TRUE);
					}
					break;

				case 3: /*Sair*/
					opt2 = confirma(jogo->h + 18, 18);
					if(opt2){
						ctr_jogada = TRUE;
						ctr_game = FALSE;
					}
					break;

				default:
					moveCursor((jogo->h + 18), 18);
					printf("Opção inválida!");
					break;
			}
		}

		ctr_jogada = FALSE;
	}

}

/* Controla a jogada */
int jogada(){
	int controle = FALSE;
	coord_t a, b;

	leCoord(jogo->h, &a, &b);

	if(verifica(a, b)){ /*Se a jogada for possível*/
		if(testaJogada(a, b)){ /*Se houver match*/
			controle = TRUE;
			while (controle){ /*Verifica se há "combos" (novos matchs) e roda até não haver mais*/
				printJogo(FALSE);
				fflush(stdout);
				system(SLEEP " 2 >nul");
				controle = verificaBoard();
			}
			controle = TRUE;
		}
		else{
			moveCursor(jogo->h + 18, 47);
			printf("Jogada imposs�vel, n�o gera um match 3!");
			fflush(stdout);
			system(SLEEP " 2 >nul");
		}
	}
	else{
		moveCursor(jogo->h + 18, 27);
		printf("Jogada impossível, as pedras não são adjacentes ou não existem!");
		fflush(stdout);
		system(SLEEP " 2 >nul");
	}

	return controle;
}

/* Cria o tabuleiro inicial */
void novoJogo(int f){
	int i, j, menor;
	srand(time(NULL));

	if(f){
		for(i = 0; i < jogo->h; i++){
			free(jogo->board[i]);
		}
		free(jogo->board);
	}

	jogo->board = malloc(sizeof(pedra_t*) * jogo->h);

	for(i = 0; i < jogo->h; i++){ /*Preenche o tabuleiro com os dados iniciais*/
		jogo->board[i] = malloc(sizeof(pedra_t) * jogo->w);
		for(j = 0; j < jogo->w; j++){
			jogo->board[i][j].type = -1;
			jogo->board[i][j].coord.x = i;
			jogo->board[i][j].coord.y = j;
			jogo->board[i][j].mark = FALSE;
			jogo->board[i][j].mark2 = FALSE;
		}
	}

	menor = jogo->h > jogo->w ? jogo->w : jogo->h; /*Verifica qual dos lados é maior*/

	for(i = 0; i < menor; i++){ /*Preenche a diagonal principal com peças aleatórias*/
		jogo->board[i][i].type = rand() % jogo->n_sym;
	}

	for(i = 0; i < jogo->h; i++){ /*Preenche o resto do tabuleiro com peças escolhidas pelo escolhePedra*/
		for(j = 0;j < jogo->w; j++){
			if(i != j){
				escolhePedra(jogo->board[i][j].coord, 100, 70);
			}
		}
	}

	jogo->score = 0; /*Inicia o score em 0*/

}

/* Escolhe uma pedra a partir dos dados da linha e coluna de sua coordenada */
void escolhePedra(coord_t a, int change, int max){
	/*int change é a possibilidade (0 - 100) de, quanda a pedra escolhida gerar match, ela ser elimidada e a pedra reencolhida*/
	/*int max é a probabilidade maxima de uma pedra ser esolhida*/
	int i, j;
	int n_removidos = 0;
	int removidos[4];
	int somar = TRUE;
	int menor = 0;
	int n_0 = 1;
	int tam = 1;
	int escolhe = TRUE;
	int *ordem;
	double p, resto, r, c;
	double soma = 0;
	double soma_r = 0;
	double *percents, *n_percents;
	pedra_t *pedra;
	fila_t *fila;

	pedra = malloc(sizeof(pedra_t));
	percents = malloc(jogo->n_sym * sizeof(double));
	n_percents = malloc(jogo->n_sym * sizeof(double));

	for(i = 0; i < jogo->n_sym; i++){
		percents[i] = 0;
	}

	for(i = 0; i < jogo->h; i++){ /*Calcula a quantidade de peças de cada tipo na coluna do elemento*/
		if(jogo->board[i][a.y].type != -1){
			percents[jogo->board[i][a.y].type]++;
		}
	}

	for(i = 0; i < jogo->w; i++){ /*Calcula a quantidade de peças de cada tipo na linha do elemento*/
		if(jogo->board[a.x][i].type != -1){
			percents[jogo->board[a.x][i].type]++;
		}
	}

	for(i = 0; i < jogo->n_sym; i++){ /*Calcula a porcentagem de cada tipo*/
		percents[i] = percents[i]/(jogo->w + jogo->h - 1);
	}

	for(i = 1; i < jogo->n_sym; i++){ /*Verifica qual a menor porcentagem*/

		if(percents[i] == percents[menor]){ /*Se hover iguais, ramdomiza sua colocação*/
			r = rand() % 2;
			if(r){
				menor = i;
			}
		}
		else if(percents[i] < percents[menor]){
			menor = i;
		}
	}

	p = 100 - percents[menor]; /*Inverte a porcentagem do menor*/
	p = p > max ? max : p; /*Caso for maior que max, diminui ela para max*/
	resto = 100 - p; /*Para distribuição entre os outros elementos*/

	for(i = 0; i < jogo->n_sym; i++){ /*Calcula quantos elementos do tipos não-menor há*/
		soma = i == menor ? soma : soma + percents[i];
	}

	for(i = 0; i < jogo->n_sym; i++){ /*Cuida do caso de haver zeros*/
		n_0 = i == menor ? n_0 : percents[i] == 0 ? n_0 + 1 : n_0;
	}

	for(i = 0; i < jogo->n_sym; i++){ /*Calcula quantos porcento cada tipo não-menor representa entre eles*/
		percents[i] = i == menor ? p/n_0 : percents[i] == 0 ? p/n_0 : (percents[i] / soma) * resto;
	}

	ordem = ordena(percents, jogo->n_sym); /*Recebe a ordem das porcentagens*/

	for(i = 0; i < jogo->n_sym; i++){ /*Preenche uma lista com as porcentagens ordenadas*/
		n_percents[ordem[i]] = percents[i];
	}

	while(escolhe){ /*Enquanto tiver que escolher*/
		if(soma_r >= 99.9){ 							 /*Se a soma das porcentagens for maior ou igual a 100, significa que essa configuração é impossível*/
			if(change < 100){									 /*Se a possibilidade for menor que 100 (pode acontecer match), randomiza uma pedra*/
				jogo->board[a.x][a.y].type = rand() % jogo->n_sym;
				escolhe = FALSE;
			}
			else{													 /*Se for 100, quer dizer que não pode haver match, logo, o jogo não pode acontecer*/
				printf("Combina��o tamanho do tabuleiro/quantidade de peças impossível, abortando\n");
				exit(0);
			}
		}
		else{
			soma = 0;  /*Soma inicial para cada iteração é 0*/
			r = (rand() % (100 - (int)soma_r)) + 1; /*Aleatoriza um número de 1 a 100 menos as somas das porcentagens removidas*/

			for(i = 0; i < jogo->n_sym; i++){
				somar = TRUE;											/*Inicialmente a porcentagem deve ser somada*/

				for(j = 0; j < n_removidos; j++){ /*Verifica se o i está entre os removidos*/
					if(i == ordem[removidos[j]]){
						somar = FALSE;
						break;
					}
				}

				soma = somar == FALSE ? soma : soma + n_percents[i]; /*Se não estiver, soma o valor dele, se sim, não soma*/

				if(r <= soma){ /*Se a soma das porcentagens até o momento chegarem no numero gerado*/
					for(j = 0; j < jogo->n_sym; j++){ /*Procura qual dos tipos ele representa*/
						if(ordem[j] == i){
							jogo->board[a.x][a.y].type = j; /*Define o tipo da pedra esolhida*/
							fila = match3(a, &tam);         /*Verifica se com a nova pedra houve match*/

							while(!(filaVazia(fila))){ /*Esvazia a fila*/
								removeFila(fila, pedra);
							}

							if(tam >= 3){ /*Se houve match*/
								c = (rand() % 100) + 1;            /*Randomiza um valor*/
								if(c <= change){ 									 /*Se esse valor for menor que o passado por parâmetro, remove a chance desse tipo ser escolhido novamente*/
									jogo->board[a.x][a.y].type = -1; /*Redefine o tipo da pedra esolhida*/
									soma_r = soma_r + percents[j];   /*Remove a porcentagem referente a pedra*/
									removidos[n_removidos] = j; 		 /*Põe ela na lista das removidas*/
									n_removidos = n_removidos + 1;   /*Aumenta o número de removidos*/

								} /*Se não for maior, termina de escolher*/
								else{
									escolhe = FALSE;
								}
							} /*Se não houve, termina de escolher*/
							else{
								escolhe = FALSE;
							}
							break;
						}
					}
					break;
				}
			}
		}
	}

	free(fila);
	free(pedra);
	free(percents);
	free(n_percents);
	free(ordem);
}

/* Retorna uma lista com a posição correta de cada elemento */
int *ordena(double *vet, int tam){
	int i, j;
	int *aux;

	aux = malloc(tam * sizeof(int));

	for(i = 0; i < tam; i++){ /*Inicializa com a lista com todos os elementos estando em "último"*/
		aux[i] = (tam - 1);
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(i != j){
				if(vet[i] > vet[j]){ /*Se o elemento for maior, diminui em 1 a posição dele*/
					aux[i] = aux[i] - 1;
				}
				else if(vet[i] == vet[j]){ /*Se eles forem iguais, prioriza o elemento da esquerda*/
					if(i < j){
						aux[i] = aux[i] - 1;
					}
				}
			}
		}
	}

	return aux;
}


/* Verifica se é possível fazer a jogada (as pedras são adjacentes e são coordenadas válidas) */
int verifica(coord_t a, coord_t b){
	if(
	   ((a.x < jogo->h) && (a.x >= 0) && (a.y < jogo->w) && (a.y >= 0) &&	/*Verifica limites em altura e largura */
            (b.x < jogo->h) && (b.x >= 0) && (b.y < jogo->w) && (b.y >= 0)) && 	/* ||       ||					*/
	   (!((a.x == b.x) && (a.y == b.y))) && 														/*Verifica se as coordenadas não são iguais*/
	   (
	     ( (a.x == b.x) && ( (a.y == (b.y - 1)) || (a.y == (b.y + 1)) ) ) ||/*Verifica se as coordenadas são adjacentes*/
	     ( (a.y == b.y) && ( (a.x == (b.x - 1)) || (a.x == (b.x + 1)) ) ) ) /* ||       ||				*/
	   ){
		return TRUE;
	}
	return FALSE;
}

/* Lê o tabuleiro procurando matchs */
int verificaBoard(){
	int i, j;
	int retorno = FALSE;
	int tam = 1;
	int combo = 0;
	pedra_t *pedra;
	fila_t *fila_mark, *fila;

	pedra = malloc(sizeof(pedra_t));
	fila = malloc(sizeof(fila_t));
	fila_mark = malloc(sizeof(fila_t));

	inicializaFila(fila_mark);
	inicializaFila(fila);

	for(i = 0; i < jogo->h; i++){ /*Passa pelo tabuleiro testando se há novos matchs*/
		for(j = 0; j < jogo->w; j++){
			if(jogo->board[i][j].mark2 != TRUE){
				fila = match3(jogo->board[i][j].coord, &tam);
			}

			if(tam >= 3){ /*Se o tamanho for maior que 3, "estoura" as pedras e marca*/
				while(!filaVazia(fila)){
					removeFila(fila, pedra);

					jogo->board[pedra->coord.x][pedra->coord.y].mark2 = TRUE; /*Marca o elemento para ele não ser testado novamente*/
					insereFila(fila_mark, jogo->board[pedra->coord.x][pedra->coord.y]); /*Insere as pedras marcadas numa fila para depois serem desmarcadas*/

					jogo->board[pedra->coord.x][pedra->coord.y].type = -1;

					printJogo(FALSE);
					fflush(stdout);
					system(SLEEP " 1 >nul");
				}

				retorno = TRUE;
				combo = combo + 1;
				calcScore(tam, combo); /*Para cada novo match encontrado aumenta o combo e calcula o score*/
				printCombo(tam, combo);
			}
			else{ /*Se não, só marca*/
				while(!filaVazia(fila)){
					removeFila(fila, pedra);

					jogo->board[pedra->coord.x][pedra->coord.y].mark2 = TRUE;
					insereFila(fila_mark, jogo->board[pedra->coord.x][pedra->coord.y]);
				}
			}

		tam = 1;
		}
	}

	while(!(filaVazia(fila_mark))){ /*Desmarca as pedras*/
		removeFila(fila_mark, pedra);
		jogo->board[pedra->coord.x][pedra->coord.y].mark2 = FALSE;
	}

	free(pedra);
	free(fila_mark);
	free(fila);

	if(retorno){
		system(SLEEP " 1 >nul");
		preencheBoard();
	}

	return retorno;
}

/* Algoritmo de procura em largura para match3 */
fila_t *match3(coord_t z, int *tam){
	*tam = 1; /*Quantidade de elementos na fila*/
	fila_t *fila_mark, *fila_aux, *fila;
	pedra_t *pedra;

	pedra = malloc(sizeof(pedra_t));
	fila_aux = malloc(sizeof(fila_t));
	fila_mark = malloc(sizeof(fila_t));
	fila = malloc(sizeof(fila_t));

	jogo->board[z.x][z.y].mark = TRUE; /*Marca a primeira pedra como visistada*/

	inicializaFila(fila_aux);
	insereFila(fila_aux, jogo->board[z.x][z.y]);

	inicializaFila(fila_mark);
	insereFila(fila_mark, jogo->board[z.x][z.y]);

	inicializaFila(fila);
	insereFila(fila, jogo->board[z.x][z.y]);


	/*Preenche e esvazia a fila principal conforme acha pedras do mesmo tipo*/
	while(!filaVazia(fila)){
		removeFila(fila, pedra);

		/* UP check*/
		if(!((pedra->coord.x - 1) < 0)){
			if (jogo->board[pedra->coord.x - 1][pedra->coord.y].mark != TRUE){
				jogo->board[pedra->coord.x - 1][pedra->coord.y].mark = TRUE;
				insereFila(fila_mark, jogo->board[pedra->coord.x - 1][pedra->coord.y]); /*Põe as pedras marcadas numa lista para depois serem desmarcadas*/

				if (jogo->board[pedra->coord.x - 1][pedra->coord.y].type == pedra->type){ /*Se não estiver marcada e for do mesmo tipo, coloca na fila*/
					insereFila(fila, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x - 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		/* RIGHT check*/
		if(!((pedra->coord.y + 1) >= jogo->w)){
			if (jogo->board[pedra->coord.x][pedra->coord.y + 1].mark != TRUE){
				jogo->board[pedra->coord.x][pedra->coord.y + 1].mark = TRUE;
				insereFila(fila_mark, jogo->board[pedra->coord.x][pedra->coord.y + 1]);

				if (jogo->board[pedra->coord.x][pedra->coord.y + 1].type == pedra->type){
					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y + 1]);
					*tam = *tam + 1;
				}
			}
		}

		/* DOWN check*/
		if(!((pedra->coord.x + 1) >= jogo->h)){
			if (jogo->board[pedra->coord.x + 1][pedra->coord.y].mark!= TRUE){
				jogo->board[pedra->coord.x + 1][pedra->coord.y].mark = TRUE;
				insereFila(fila_mark, jogo->board[pedra->coord.x + 1][pedra->coord.y]);

				if (jogo->board[pedra->coord.x + 1][pedra->coord.y].type == pedra->type){
					insereFila(fila, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					insereFila(fila_aux, jogo->board[pedra->coord.x + 1][pedra->coord.y]);
					*tam = *tam + 1;
				}
			}
		}

		/*LEFT check */
		if(!((pedra->coord.y - 1)  < 0)){
			if (jogo->board[pedra->coord.x][pedra->coord.y - 1].mark!= TRUE){
				jogo->board[pedra->coord.x][pedra->coord.y - 1].mark = TRUE;
				insereFila(fila_mark, jogo->board[pedra->coord.x][pedra->coord.y - 1]);

				if (jogo->board[pedra->coord.x][pedra->coord.y - 1].type == pedra->type){
					insereFila(fila, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					insereFila(fila_aux, jogo->board[pedra->coord.x][pedra->coord.y - 1]);
					*tam = *tam + 1;
				}
			}
		}
	}

	while(!(filaVazia(fila_mark))){ /*Desmarca as pedras*/
		removeFila(fila_mark, pedra);
		jogo->board[pedra->coord.x][pedra->coord.y].mark = FALSE;
	}


	free(pedra);
	free(fila_mark);
	free(fila);

	return fila_aux;
}

/*Recebe as duas coordenadas da jogada e verifica se fazem match3*/
int testaJogada(coord_t a, coord_t b){
	int i, tam_a, tam_b, retorno;
	coord_t aux;
	fila_t *fila_a, *fila_b;
	pedra_t *pedra;

	retorno = FALSE;

	pedra = malloc(sizeof(pedra_t));

	/* Troca as pedras no board */
	*pedra = jogo->board[a.x][a.y];
	jogo->board[a.x][a.y] = jogo->board[b.x][b.y];
	jogo->board[b.x][b.y] = *pedra;

	/*Troca as coordenadas*/
	aux = a;
	a = b;
	b = aux;
	jogo->board[a.x][a.y].coord = a;
	jogo->board[b.x][b.y].coord = b;

	printJogo(FALSE);
	fflush(stdout);
	system(SLEEP " 1 >nul");

	/*Calcula os match3 */
	fila_a = match3(a, &tam_a);
	fila_b = match3(b, &tam_b);

	/* Destroca as pedras caso não houve um match3 */
	if((tam_a < 3) && (tam_b < 3)){
		*pedra = jogo->board[b.x][b.y];
		jogo->board[b.x][b.y] = jogo->board[a.x][a.y];
		jogo->board[a.x][a.y] = *pedra;

		jogo->board[a.x][a.y].coord = a;
		jogo->board[b.x][b.y].coord = b;
	}
	else{
		retorno = TRUE;
	}

	if(tam_a >= 3){/*Se o tamanho for maior que 3, "estoura" as pedras*/
		while(!filaVazia(fila_a)){
			removeFila(fila_a, pedra);

			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;

			printJogo(FALSE);
			fflush(stdout);
			system(SLEEP " 1 >nul");
		}

		calcScore(tam_a, 0);
		printCombo(tam_a, 0);
	}
	else{/*Se não, só remove da fila*/
		while(!filaVazia(fila_a)){
			removeFila(fila_a, pedra);
		}
	}

	if(tam_b >= 3){
		while(!filaVazia(fila_b)){
			removeFila(fila_b, pedra);

			jogo->board[pedra->coord.x][pedra->coord.y].type = -1;

			printJogo(FALSE);
			fflush(stdout);
			system(SLEEP " 1 >nul");
		}

		calcScore(tam_b, 0);
		printCombo(tam_b, 0);
	}
	else{
		while(!filaVazia(fila_b)){
			removeFila(fila_b, pedra);
		}
	}

	free(pedra);
	free(fila_a);
	free(fila_b);

	/* Se formou match, repreenche o tabuleiro */
	if(retorno){
		preencheBoard();
	}

	return retorno;
}

/* Re-preenche o tabuleiro com novas pedras */
void preencheBoard(){
	int i, j;
	int* array; /*Guarda quantas pedras estouradas em cada coluna*/
	pedra_t* pedra;
	fila_t *fila, *fila_pop;

	array = malloc(sizeof(int) * jogo->w);
	pedra = malloc(sizeof(pedra_t));
	fila = malloc(sizeof(fila_t));
	fila_pop = malloc(sizeof(fila_t));

	for(i = 0; i < jogo->w; i++){
		array[i] = 0;
	}

	for(i = 0; i < jogo->w; i++){ /*Anda na largura contando quantas pedras estouradas houve em sua respectiva coluna*/
		for(j = 0; j < jogo->h; j++){
			if (jogo->board[j][i].type == -1){
				array[i]++;
			}
		}
	}


	for(i = 0; i < jogo->w; i++){ /*Anda na largura preenchendo*/
		if(array[i] > 0){ /*Se há estourados nessa coluna*/
			inicializaFila(fila);
			inicializaFila(fila_pop);

			for(j = jogo->h - 1; j >= 0; j--){ /*Itera de baixo para cima colocando as peças na fila*/
				if (jogo->board[j][i].type != -1) { /*Se a pedra já existe coloca na fila principal, se não na secundária*/
					insereFila(fila, jogo->board[j][i]);
				} else{
					insereFila(fila_pop, jogo->board[j][i]);
				}
			}

			/* Para o numero de pedras estouradas de cada coluna, remove da fila secundaria e insere na fila principal */
			for(j = 0; j < array[i]; j++){
				removeFila(fila_pop, pedra);
				insereFila(fila, *pedra);
			}

			/* Re-insere essa coluna no board */
			for(j = jogo->h - 1; j >= 0; j--){
				removeFila(fila, pedra);
				pedra->coord.x = j;
				pedra->coord.y = i;
				if(pedra->type == -1){ /*Se a pedra for vazia, insere na fila para escolha do tipo*/
					insereFila(fila_pop, *pedra);
				}
				jogo->board[j][i] = *pedra;
			}
			while(!(filaVazia(fila_pop))){ /*Passa escolhendo o tipo da pedra*/
				removeFila(fila_pop, pedra);
				escolhePedra(pedra->coord, 50, 70);
			}
		}
	}

	free(pedra);
	free(array);
	free(fila);
	free(fila_pop);
}

void calcScore(int tam, int combo){
	int mult = 1;

	mult = combo == 0 ? mult : combo;
	jogo->score = jogo->score + (tam * 10 * mult);
}

void espera(){
	fflush(stdin);
	getchar();
	getchar();
}
