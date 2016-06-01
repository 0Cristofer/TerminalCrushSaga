/*Arquivo header de funções diversas
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef UTIL
#define UTIL

#define TRUE 1
#define FALSE 0

#define CLS "clear" //Para mudança entre OSs

typedef struct{
        int **board, w, h, n_sym;
}game;

void quit();

#endif
