/***********************************************************/
/* Author Bruno Cesar Puli                                  /
/* 31/05/2016                                               /
/* ---------------------------------------------------------/
/* Implementação genérica de fila com lista ligada (cabeça) /
/***********************************************************/

#include <stdio.h>
#include <stdlib.h>

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
	}
	else {
		return 0;
	}
}

/* insere */
void insereFila(fila_t* fila, pedra_t pedra){
	lista_t* elemento;
	elemento = malloc(sizeof(lista_t));
	elemento->info = pedra;

	if (filaVazia(fila)){
		fila->inicio = elemento;
	}
	else{
		fila->fim->prox = elemento;
	}
	elemento->prox = NULL;
	fila->fim = elemento;
}

/* remove */
int removeFila(fila_t* fila, pedra_t *info){
	if (!(filaVazia(fila))){
		*info = fila->inicio->info;
		if (fila->inicio == fila->fim){
			free(fila->inicio);
			inicializaFila(fila);
		}
		else{
			lista_t* fim = fila->inicio;
			fila->inicio = fila->inicio->prox;
			free(fim);
		}
		return 1;
	}
	else{
		printf("Fila vazia!\n");
	}
	return 0;
}
