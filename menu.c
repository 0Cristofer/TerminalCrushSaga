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

	//printTopo();
	//printLado();
	//printCab();
	//printLado();
	printLogo();
	printf("\n\n\t\t\t\t\t\t\tMenu Principal\n");
	printf("\n\t\tS - Inicia o jogo\n");
	printf("\t\tX - Sai do jogo\n");
	printf("\n\t\t");
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
	printf("\n\t\tInsira a largura do tabuleiro: ");
	scanf(" %d", &jogo->w);
	printf("\t\tInsira a altura do tabuleiro: ");
	scanf(" %d", &jogo->h);
	printf("\t\tInsira a quantidade de simbolos: ");
	scanf(" %d", &jogo->n_sym);
}

void printTopo(){
	printf("\t\t\t\t\t-----------------------------------------------------------------\n");
}

void printLado(){
	printf("\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t|                                                               |\n");
}

void printCab(){
	printf("\t\t\t\t\t|\t\tT E R M I N A L  C R U S H  S A G A\t\t|\n");
}

void printLogo(){

 printf("       __                      _             __                        __                              \n");
 printf("      / /____  _________ ___  (_)___  ____ _/ /  ____________  _______/ /_     _________ _____ _____ _ \n");
 printf("     / __/ _ \\/ ___/ __ `__ \\/ / __ \\/ __ `/ /  / ___/ ___/ / / / ___/ __ \\   / ___/ __ `/ __ `/ __ `/ \n");
 printf("    / /_/  __/ /  / / / / / / / / / / /_/ / /  / /__/ /  / /_/ (__  ) / / /  (__  ) /_/ / /_/ / /_/ /  \n");
 printf("    \\__/\\___/_/  /_/ /_/ /_/_/_/ /_/\\__,_/_/   \\___/_/   \\____/____/_/ /_/  /____/\\__,_/\\__, /\\__,_/   \n"); 
 printf("                                                                                       /____/          \n");

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
