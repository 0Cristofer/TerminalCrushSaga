/***********************************************************/
/* Author Bruno Cesar Puli                                  /
/* 31/05/2016                                               /
/* ---------------------------------------------------------/
/* Implementação genérica de fila com lista ligada (cabeça) /
/* Onde "generic" adaptar para a finalidade do uso          /
/***********************************************************/

#ifndef __FILA_H
#define __FILA_H

#include "./../util.h"

typedef struct lista lista_t;
struct lista{
    pedra_t info;
    lista_t *prox;
};

typedef struct fila fila_t;
struct fila{
    lista_t *inicio;
    lista_t *fim;
};

int removeFila(fila_t *fila, pedra_t *elemento);
int filaVazia(fila_t *fila);

void insereFila(fila_t *fila, pedra_t elemento);
void inicializaFila(fila_t *fila);

#endif /* __FILA_H */
