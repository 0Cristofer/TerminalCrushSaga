/*Arquivo principal de Ternimal Crush Saga
Data: 31/05/2016
Autor: Cristofer Oswald */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "menu.h"
#include "saga.h"

int main(){
	int menu;
	game *jogo;

	jogo = malloc(sizeof(game));
	menu = mainMenu();

	switch(menu){
		case 0:
			leDados(jogo);
			mainGame(jogo);
			break;
		case 1:
			quit();
			break;
		default:
			break;
	}

	getchar();
	getchar();
	
	return 0;
}

void quit(){
	printf("\n\nAté logo!\n\n");
	system("sleep 5");
	system(CLS);
}
