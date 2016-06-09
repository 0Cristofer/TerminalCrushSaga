/*Arquivo header de funções diversas
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef UTIL
#define UTIL

#define TRUE 1
#define FALSE 0

#define CLS "clear" //Para mudança entre OSs
#define SLEEP "sleep"
#define TAB "\t\t\t"
#define LARG 98

//Representa uma coordenada no tabuleiro
typedef struct coord coord_t;
struct coord{
	int x, y;
};

void quit();

#endif
