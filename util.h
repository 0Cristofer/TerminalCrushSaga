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
#define LARG 101

typedef struct{
        int **board;
	int w;
	int h;
	int n_sym;
}game;

void quit();

#endif
