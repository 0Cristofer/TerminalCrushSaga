/***********************************************************/
/* Author Bruno Cesar Puli                                  /
/* 31/05/2016                                               /
/* ---------------------------------------------------------/
/* Implementação genérica de fila com lista ligada (cabeça) /
/***********************************************************/

#include <stdio.h>
#include "fila.h"

/* inicializa */
void inicializaFila(fila_t* fila){
    fila->inicio = NULL;
    fila->fim = NULL;
}

/* vazia_check */
int filaVazia(fila_t* fila){
    if((fila->inicio == NULL) && (fila->fim == NULL)){
        return 1;
    } else {
        return 0;
    }
}

/* insere */
void insereFila(fila_t* fila, lista_t* elemento){
    if (filaVazia(fila)){
        fila->fim = elemento;
        fila->fim->prox = NULL;
    }
    elemento->prox = fila->inicio;
    fila->inicio = elemento;
}

/* remove */
void removeFila(fila_t* fila, lista_t* elemento){
    if (!(filaVazia(fila))){
        if (fila->inicio == fila->fim){
            elemento->info = fila->fim->info;
            free(fila->fim);
            inicializaFila(fila);
        }
        else{
            elemento->info = fila->fim->info;
            lista_t* fim = fila->fim;
            fila->fim = fila->inicio;
            while (fila->fim->prox != fim){
                fila->fim = fila->fim->prox;
            }
            free(fim);
            fila->fim->prox = NULL;
        }
    } else{
        printf("Fila vazia!\n");
    }
}
