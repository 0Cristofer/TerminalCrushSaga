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

void printTopo(){
	printTer();
	printLado(1);
        printLogo();
        printLado(2);
}

void printLado(int n){
	int i;
	for(i = 0; i < n; i++){
		printf(TAB"|                                                                                                     |\n");
	}
}

void printLogo(){

	printf(TAB"|    __                      _             __                        __                               |\n");
	printf(TAB"|   / /____  _________ ___  (_)___  ____ _/ /  ____________  _______/ /_     _________ _____ _____ _  |\n");
	printf(TAB"|  / __/ _ \\/ ___/ __ `__ \\/ / __ \\/ __ `/ /  / ___/ ___/ / / / ___/ __ \\   / ___/ __ `/ __ `/ __ `/  |\n");
	printf(TAB"| / /_/  __/ /  / / / / / / / / / / /_/ / /  / /__/ /  / /_/ (__  ) / / /  (__  ) /_/ / /_/ / /_/ /   |\n");
	printf(TAB"| \\__/\\___/_/  /_/ /_/ /_/_/_/ /_/\\__,_/_/   \\___/_/   \\____/____/_/ /_/  /____/\\__,_/\\__, /\\__,_/    |\n");
	printf(TAB"|                                                                                     /____/          |\n");
}

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

void printTer(){
	printf(TAB"-------------------------------------------------------------------------------------------------------\n");
}

void moveCursor(int x, int y){
	printf("\033[%d;%dH", x, y);
}

int inGameMenu(){

}

void printJogo(game *jogo){
        int i, j, aux;

        system(CLS);

	printTopo();

	aux = (jogo->w%2) == 0 ? 1 : 0;

	for(i = 0; i < jogo->h; i++){
		printf(TAB"|");
		for(j = 0; j < (((LARG - (jogo->w * 3))/2) + aux); j++){
			printf(" ");
		}
		for(j = 0; j < jogo->w; j++){
			printf("%d  ", jogo->board[i][j].type);
		}
		for(j = 0; j < (((LARG - (jogo->w * 3))/2)); j++){
			printf(" ");
		}
		printf("|\n");
	}
	printLado(2);
}

int printBoard(game* jogo){
	int opt;
	printTopo();
	printJogo(jogo);
	printf(TAB"|  1 - Realizar jogada | 2 - Shuffle | 3 - Sair                                                       |\n");
	printTer();
	//moveCursor(35, 50);
	scanf(" %d", &opt);
	return opt;
}
