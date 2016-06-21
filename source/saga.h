/*Arquivo header de saga.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef SAGA
#define SAGA

/*Nossas bibliotecas*/
#include "util.h"
#include "fila_lista_ligada/fila.h"

int verifica(coord_t a, coord_t b);
int testaJogada(coord_t a, coord_t b);
int *ordena(double *vet, int tam);
int verificaBoard();
int jogada();

fila_t *match3(coord_t z, int *tam);

void escolhePedra(coord_t a, int change, int max);
void calcScore(int tam, int combo);
void mainGame();
void novoJogo();
void preencheBoard();
void espera();

#endif
