/*Arquivo header com as definições de estruturas e funções diversas
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef UTIL
#define UTIL

#define TRUE 1
#define FALSE 0

#define CLS "clear" //Para mudança entre OSs
#define SLEEP "sleep" //    ||
#define TAB "\t\t\t"	//Para centralização
#define LARG 98				//Largura do tabuleiro

//Representa uma coordenada no tabuleiro
typedef struct coord coord_t;
struct coord{
	int x;
	int y;
};

//Struct que representa uma peça do tabuleiro
typedef struct pedra pedra_t;
struct pedra{
	int type;
	int mark;
	int mark2;
	coord_t coord;
};

//Representa os dados do jogo atual
typedef struct game game_t;
struct game{
	pedra_t **board;
	int w;
	int h;
	int n_sym;
	int score;
};

extern game_t *jogo; //Variável global

void quit();

#endif
