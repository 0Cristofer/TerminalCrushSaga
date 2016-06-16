/*Arquivo principal de Ternimal Crush Saga
Data: 31/05/2016
autor: Cristofer Oswald */

//Bibliotecas dos sistemas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Nossas bibliotecas
#include "util.h"
#include "menu.h"
#include "saga.h"

game_t *jogo; //Variável global

//Função principal
int main(){
	int menu;

	jogo = malloc(sizeof(game_t));
	menu = mainMenu();

	switch(menu){
		case 0: //Novo jogo
			leDados();
			mainGame();
			break;

		case 1: //Sair
			quit();
			break;

		default:
			break;
	}

	quit();

	return 0;
}

//Limpa a tela e mostra os créditos
void quit(){
	system(CLS);
	printf("\n\n\n"TAB"Todos os direitos reservados a Bruno Cesar & Cristofer Oswald, 2016\n\n");
	system(SLEEP " 2");
	system(CLS);
}
