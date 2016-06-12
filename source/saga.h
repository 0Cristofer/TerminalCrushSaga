/*Arquivo header de saga.c. Descrição das funções estão no arquivo .c
Data: 31/05/2016
Autor: Cristofer Oswald */

#ifndef SAGA
#define SAGA

//Nossas bibliotecas
#include "util.h"
#include "fila_lista_ligada/fila.h"

int verifica(game_t *jogo, coord_t a, coord_t b);
int testaJogada(game_t *jogo, coord_t a, coord_t b, int *score);
int escolhePedra(game_t *jogo, coord_t a);
int jogada(game_t *jogo);
int verificaBoard(game_t *jogo, int *score);
int *ordena(double *vet, int tam);

fila_t *match3(game_t *jogo, coord_t z, int *tam);

void mainGame(game_t *jogo);
void novoJogo(game_t *jogo);
void preencheBoard(game_t *jogo);
void limpaMark(game_t *jogo, int type);
void espera();

#endif
