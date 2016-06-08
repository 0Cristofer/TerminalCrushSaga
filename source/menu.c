/*Biblioteca responsável por administrar o menu do aplicativo Terminal Crush Saga
Data: 31/05/2016
Autor: Cristofer Oswald */

#include <stdio.h>
#include <stdlib.h>

//Nossos includes
#include "menu.h"
#include "saga.h"
#include "util.h"

//Mostra o menu e suas opções e a retorna a entrada do usuário
int mainMenu(){
	char op;

	system(CLS);
	printTopo();
	printf(TAB"|                                         Menu Principal                                              |\n");
	printf(TAB"|S - Inicia o jogo                                                                                    |\n");
	printf(TAB"|X - Sai do jogo                                                                                      |\n");
	printLado(14);
	printTer();
	moveCursor(14, 26);
	scanf(" %c", &op);

	system(CLS);

	switch(op){
		case 's':
			return 0;
		case 'S':
			return 0;
		case 'x':
			return 1;
		case 'X':
			return 1;
		default:
			printf("Opção inválida, saindo do jogo...\n");
			return 1;
	}
}

//Lê os dados do jogo (tamanho do tabuleiro e quantidade de tipos de peças)
void leDados(game *jogo){
	printTopo();
	printf(TAB"|Insira a largura do tabuleiro:                                                                       |\n");
	printf(TAB"|Insira a altura do tabuleiro:                                                                        |\n");
	printf(TAB"|Insira a quantidade de simbolos:                                                                     |\n");
	printLado(13);
	printTer();
	moveCursor(11, 57);
	scanf(" %d", &jogo->w);
	moveCursor(12, 56);
	scanf(" %d", &jogo->h);
	moveCursor(13, 59);
	scanf(" %d", &jogo->n_sym);
}

//Escreve o topo do jogo (é chamado toda vez que a tela é limpa)
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

//Logo do jogo
void printLogo(){

	printf(TAB"|    __                      _             __                        __                               |\n");
	printf(TAB"|   / /____  _________ ___  (_)___  ____ _/ /  ____________  _______/ /_     _________ _____ _____ _  |\n");
	printf(TAB"|  / __/ _ \\/ ___/ __ `__ \\/ / __ \\/ __ `/ /  / ___/ ___/ / / / ___/ __ \\   / ___/ __ `/ __ `/ __ `/  |\n");
	printf(TAB"| / /_/  __/ /  / / / / / / / / / / /_/ / /  / /__/ /  / /_/ (__  ) / / /  (__  ) /_/ / /_/ / /_/ /   |\n");
	printf(TAB"| \\__/\\___/_/  /_/ /_/ /_/_/_/ /_/\\__,_/_/   \\___/_/   \\____/____/_/ /_/  /____/\\__,_/\\__, /\\__,_/    |\n");
	printf(TAB"|                                                                                     /____/          |\n");
}

//Logo para 1080p
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

//Escreve o 'terminal', tanto do superior quanto inferior
void printTer(){
	printf(TAB"-------------------------------------------------------------------------------------------------------\n");
}

//Move o cursor para a linha x, coluna y
void moveCursor(int x, int y){
	printf("\033[%d;%dH", x, y);
}

int inGameMenu(){

}

//Escreve o tabuleiro centralizado
void printBoard(game *jogo){
        int i, j, cond, par, dig;

        system(CLS);

	printTopo();

	par = (jogo->w%2) == 0 ? -1 : 0; //Caso seja par diminui um espaçamento

	for(i = 0; i < (jogo->h + 2); i++){
		printf(TAB"|"); 
		cond = (LARG - (jogo->w * 3)) / 2; //Quantidade de espaços
		dig = i > 11 ? -1 : 0; //Caso seja um número com mais de dois dígitos

		for(j = 0; j < (cond + dig + par + 1); j++){
			printf(" ");
		}

		for(j = 0; j < jogo->w; j++){
			if(i == 0){
				if(j == 0){
					printf("   ");
				}
				printf("%d  ", j);
			}
			else if(i == 1){
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
				if(j == 0){
					printf("%d| ", (i-2));
				}
				printf("%d  ", jogo->board[(i-2)][j].type);
			}
		}
		for(j = 0; j < cond; j++){
			printf(" ");
		}
		printf("|\n");
	}
	printLado(2);
}

//Escreve todo o jogo (topo, tabuleiro, opções, etc)
int printJogo(game* jogo){
	int opt;

	printTopo();
	printBoard(jogo);

	printf(TAB"|  1 - Realizar jogada | 2 - Shuffle | 3 - Sair                                                       |\n");

	printTer();
	printLado(2);
	printTer();
	moveCursor((jogo->h + 17), 26);
	scanf(" %d", &opt);
	return opt;
}

void leCoord(int h, coord *a, coord *b){
	moveCursor((h + 18), 26);
	printf(" , | , ");
	moveCursor((h + 18), 26);
	scanf(" %d", &a->x);
	moveCursor((h + 18), 28);
	scanf(" %d", &a->y);
	moveCursor((h + 18), 30);
	scanf(" %d", &b->x);
	moveCursor((h + 18), 32);
	scanf(" %d", &b->y);
}
