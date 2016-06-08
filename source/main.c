/*Arquivo principal de Ternimal Crush Saga
Data: 31/05/2016
autor: Cristofer Oswald */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Nossos includes
#include "util.h"
#include "menu.h"
#include "saga.h"

//Função principal
int main(){
	int menu;
	game *jogo;

	jogo = malloc(sizeof(game));
	menu = mainMenu();

	switch(menu){
		case 0: //Novo jogo
			leDados(jogo);
			mainGame(jogo);
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
	//exit(1);
}
