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
	printLado();
	printCab();
	printLado();
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
