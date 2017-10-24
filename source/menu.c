/*Biblioteca responsável por administrar o menu do aplicativo Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer Oswald e Bruno Cesar */

//Bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>

//Nossas bibliotecas
#include "menu.h"
#include "saga.h"
#include "util.h"

/* Mostra o menu e suas opções e a retorna a entrada do usuário */
int mainMenu(){
	char *op, opt;

	system(CLS);
	printTopo();
	printf(TAB"|                                         Menu Principal                                              |\n");
	printf(TAB "|" TAB "\t\tS - Inicia o jogo                                             |\n");
	printf(TAB "|" TAB "\t\tX - Sai do jogo                                               |\n");
	printLado(14);
	printTer();

	moveCursor(14, 70);
	scanf(" %ms", &op); //Lê um número indeterminado de caracteres

	opt = op[0]; //Pega apenas o primeiro
	free(op); //Limpa a memória

	system(CLS);

	switch(opt){
		case 's': //Jogar
			return 0;

		case 'S': //Jogar
			return 0;

		case 'x': //Sair
			return 1;

		case 'X': //Sair
			return 1;

		default:
			printf("Opção inválida, saindo do jogo...\n");
			return 1;
	}
}

//Lê os dados do jogo (tamanho do tabuleiro e quantidade de tipos de peças)
void leDados(){
	printTopo();
	printf(TAB"|Insira a largura do tabuleiro:                                                                       |\n");
	printf(TAB"|Insira a altura do tabuleiro:                                                                        |\n");
	printf(TAB"|Insira a quantidade de simbolos:                                                                     |\n");
	printLado(13);
	printTer();
	//controle do cursor
	moveCursor(11, 57);
	scanf(" %d", &jogo->w);
	moveCursor(12, 56);
	scanf(" %d", &jogo->h);
	moveCursor(13, 59);
	scanf(" %d", &jogo->n_sym);

	if( ((jogo->w < 4) || (jogo->w > 20) ) || ((jogo->h < 4) || (jogo->h > 20)) ){
		moveCursor(15, 27);
		printf("Tabuleiro definido com dimensões maiores ou menores que as permitidas, por favor, reinsira os dados");
		fflush(stdout);
		system(SLEEP " 1.5");
		system(CLS);
		leDados();
	}
	else if((jogo->n_sym < 4) || (jogo->n_sym > 9)){
		moveCursor(15, 30);
		printf("Número de simbolos é muito grande ou pequeno, por favor reinsira os dados");
		fflush(stdout);
		system(SLEEP " 1.5");
		system(CLS);
		leDados();
	}
}

/* Escreve o topo do jogo (é chamado toda vez que a tela é limpa) */
void printTopo(){
	printTer();
	printLado(1);
  printLogo();
  printLado(2);
}

//Escreve n '|'
void printLado(int n){
	int i;

	for(i = 0; i < n; i++){
		printf(TAB"|                                                                                                     |\n");
	}
}

/* Logo do jogo */
void printLogo(){

	printf(TAB"|    __                      _             __                        __                               |\n");
	printf(TAB"|   / /____  _________ ___  (_)___  ____ _/ /  ____________  _______/ /_     _________ _____ _____ _  |\n");
	printf(TAB"|  / __/ _ \\/ ___/ __ `__ \\/ / __ \\/ __ `/ /  / ___/ ___/ / / / ___/ __ \\   / ___/ __ `/ __ `/ __ `/  |\n");
	printf(TAB"| / /_/  __/ /  / / / / / / / / / / /_/ / /  / /__/ /  / /_/ (__  ) / / /  (__  ) /_/ / /_/ / /_/ /   |\n");
	printf(TAB"| \\__/\\___/_/  /_/ /_/ /_/_/_/ /_/\\__,_/_/   \\___/_/   \\____/____/_/ /_/  /____/\\__,_/\\__, /\\__,_/    |\n");
	printf(TAB"|                                                                                     /____/          |\n");
}

/* Logo para 1080p */
void printLogo1080(){
	printf(" |    _________  _______   ________  _____ ______   ___  ________   ________  ___             ________  ________  ___  ___  ________  ___  ___          ________  ________  ________  ________       | \n");
	printf(" |   |\\___   ___\\\\  ___ \\ |\\   __  \\|\\   _ \\  _   \\|\\  \\|\\   ___  \\|\\   __  \\|\\  \\           |\\   ____\\|\\   __  \\|\\  \\|\\  \\|\\   ____\\|\\  \\|\\  \\        |\\   ____\\|\\   __  \\|\\   ____\\|\\   __  \\      | \n");
	printf(" |   \\|___ \\  \\_\\ \\   __/|\\ \\  \\|\\  \\ \\  \\\\__ \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\          \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\\\\\  \\       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\|\\  \\     | \n");
	printf(" |        \\ \\  \\ \\ \\  \\_|/_\\ \\   _  _\\ \\  \\\\|__| \\  \\ \\  \\ \\  \\\\ \\  \\ \\   __  \\ \\  \\          \\ \\  \\    \\ \\   _  _\\ \\  \\\\\\  \\ \\_____  \\ \\   __  \\       \\ \\_____  \\ \\   __  \\ \\  \\  __\\ \\   __  \\    | \n");
	printf(" |         \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\\\  \\\\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\____      \\ \\  \\____\\ \\  \\\\  \\\\ \\  \\\\\\  \\|____|\\  \\ \\  \\ \\  \\       \\|____|\\  \\ \\  \\ \\  \\ \\  \\|\\  \\ \\  \\ \\  \\   | \n");
	printf(" |          \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\\\ \\__\\    \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\_______\\     \\ \\_______\\ \\__\\\\ _\\\\ \\_______\\____\\_\\  \\ \\__\\ \\__\\        ____\\_\\  \\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\  | \n");
	printf(" |           \\|__|  \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|__|\\|__| \\|__|\\|__|\\|__|\\|_______|      \\|_______|\\|__|\\|__|\\|_______|\\_________\\|__|\\|__|       |\\_________\\|__|\\|__|\\|_______|\\|__|\\|__|  | \n");
	printf(" |                                                                                                                            \\|_________|                \\|_________|                               | \n");
	printf("\n\n");
}

//Escreve o 'terminal', tanto superior quanto inferior
void printTer(){
	printf(TAB"-------------------------------------------------------------------------------------------------------\n");
}

/* Move o cursor para a linha x, coluna y */
void moveCursor(int x, int y){
	printf("\033[%d;%dH", x, y);
}

/* Escreve o tabuleiro centralizado */
void printBoard(){
  int i, j, cond, par, dig, d;

	par = (jogo->w%2) == 0 ? -1 : 0; //Caso seja par diminui um espaçamento
	d = jogo->w > 10 ? 1 : 0; // Case seja uma largura com mais de dois dígitos

	for(i = 0; i < (jogo->h + 2 + d); i++){
		printf(TAB"|");

		cond = (LARG - (jogo->w * 3)) / 2; //Quantidade de espaços
		dig = i > (11 + d) ? -1 : 0; //Caso seja uma altura com mais de dois dígitos

		for(j = 0; j < (cond + dig + par + 1); j++){ //Escreve o espaçamento esquerdo
			printf(" ");
		}

		for(j = 0; j < jogo->w; j++){ //Escreve o tabuleiro
			if((d == 1) && (i == 0)){ //Escreve o primeiro digito (caso tiver mais de um) da coordenada horizontal
				if(j == 0){
					printf("   ");
				}
				if((j/10) > 0){
					printf("%d  ", j/10);
				}
				else{
					printf("   ");
				}
			}
			else if(i == d){ //Escreve as coordenadas horizontais
				if(j == 0){
					printf("   ");
				}
				printf("%d  ", (j%10));
			}
			else if(i == (1 + d)){ //Escreve as linhas horizontais
				if(j == 0){
					printf("---");
				}
				if(j == (jogo->w - 1)){
					printf("-  ");
				}
				else{
					printf("---");
				}
			}
			else{
				if(j == 0){ //Escreve as coordenadas verticais
					printf("%d| ", (i-2-d));
				}
				if (jogo->board[(i-2-d)][j].type == -1){
					printf("   ");

				} else{
					printf("%d  ", (jogo->board[(i-2-d)][j].type + 1));
				}
			}
		}

		for(j = 0; j < cond; j++){ //Escreve o espaçamento direito
			printf(" ");
		}

		printf("|\n");
	}

	printLado(3 - d); //Caso a largura for maior que 10, escre um "lado" a menos

}

/* Escreve todo o jogo (topo, tabuleiro, opções, etc) */
int printJogo(int op){
	int opt = 2;
	int w = 0;
	int score = 0;

	system(CLS);
	printTopo();
	printBoard();

	if(op){
		score = jogo->score;
		printf(TAB"|  1 - Realizar jogada | 2 - Shuffle | 3 - Sair");
		while((score / 10) >= 1){
			w = w + 1;
			score = score / 10;
		}
		moveCursor((jogo->h + 16), (111 - w));
		printf("---SCORE %d ---  |\n", jogo->score);
	}

	printTer();
	printLado(2);
	printTer();

	if(op){
		moveCursor((jogo->h + 18), 26);
		scanf(" %d", &opt);
	}

	return opt;
}

void printCombo(int tam, int combo){

	switch (tam) {
		case 3:
			moveCursor(jogo->h + 17, 73);
			printf("BOA!");
			break;

		case 4:
			moveCursor(jogo->h + 17, 73);
			printf("WOW!");
			break;

		case 5:
			moveCursor(jogo->h + 17, 70);
			printf("INCRÍVEL!!");
			break;

		case 6:
			moveCursor(jogo->h + 17, 69);
			printf("PARABAINS CARA!!");
			break;

		default:
			moveCursor(jogo->h + 17, 61);
			printf("MEU DEUS QUE DELICIOUSER!!!");
			break;

	}

	if(combo){
		switch (combo) {
			case 1:
				moveCursor(jogo->h + 18, 70);
			  printf("* COMBO! *");
				break;

			case 2:
				moveCursor(jogo->h + 18, 63);
				printf("** SUPER COMBO!! **");
				break;

			case 3:
				moveCursor(jogo->h + 18, 64);
				printf("*** HYPER COMBO!!! ***");
				break;

			case 4:
				moveCursor(jogo->h + 18, 64);
				printf("*** ULTRA COMBO!!! ***");
				break;

			default:
				moveCursor(jogo->h + 18, 52);
				printf("***** FUCKING UNBELIVABLE COMBO!!!!! *****");
				break;
		}

	}
	fflush(stdout);
	system(SLEEP " 1");
	//espera();
}

/* Escreve as porcentagens de cada peça do tabuleiro */
void printaPorcetagens(){
	int *qt, i, j;

	qt = malloc(jogo->n_sym*sizeof(int));
	for(i = 0; i < jogo->n_sym; i++){
		qt[i] = 0;
	}

	for(i = 0; i < jogo->h; i++){ //Conta quantas peças de cada tipo há
		for(j = 0;j < jogo->w; j++){
			if(jogo->board[i][j].type != -1){
				qt[jogo->board[i][j].type] += 1;
			}
		}
	}

	for(i = 0; i < jogo->n_sym; i++){ //Calcula a porcentagem e escreve
			printf("\nsimbolo %d: %d vezes, %.2lf porcento \n", (i+1), qt[i], ((qt[i]/(double)(jogo->h * jogo->w))*100) );
	}

	free(qt);
}

/* Lê as coordenadas inseridas pelo usuário */
void leCoord(int h, coord_t *a, coord_t *b){
	moveCursor((h + 19), 26);
	printf("  ,  |  ,  ");
	moveCursor((h + 19), 26);
	scanf(" %d", &a->x);
	moveCursor((h + 19), 29);
	scanf(" %d", &a->y);
	moveCursor((h + 19), 32);
	scanf(" %d", &b->x);
	moveCursor((h + 19), 35);
	scanf(" %d", &b->y);
}

/* Lê uma confirmação do usuário */
int confirma(int x, int y){
	char copt;
	int iopt;

	moveCursor(x,y);
	printf("Você tem certeza? [S/N]");
	moveCursor(x+1,y);
	scanf(" %c", &copt);

	switch (copt) {
		case 'S': //Sim
			iopt = 1;
			break;
		case 's': //Sim
			iopt = 1;
			break;
		default: //Não
			iopt = 0;
			break;
	}

	return iopt;
}
