/***********************************************************/
/* Author Bruno Cesar Puli                                  /
/* 31/05/2016                                               /
/* ---------------------------------------------------------/
/* Teste daImplementação genérica de fila com lista ligada  /
/*                                                          /
/***********************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

int main(){
	int i, a, ret, *retirado, opt = 1;
	fila_t* fila;
	lista_t *elemento;

	fila = malloc(sizeof(fila_t));

	printf("Teste da biblioteca de fila implementada com lista ligada!\n");

	inicializaFila(fila);

	printf("------Menu------\n1 - Inserir elemento na fila\n2 - Retirar e printar elemento da fila\n3 - printar todos elementos da fila\n4 - Inserir X elementos\n\n0 - Sair\n---------------------------\n");

	while(opt > 0){
		scanf(" %d", &opt);
		
		switch(opt){
			case 1:
				elemento = malloc(sizeof(lista_t));
				
				printf("Insira info (Generic info test): ");
				scanf(" %d",&elemento->info);

				insereFila(fila,elemento);
				
				break;

			case 2:
				retirado = malloc(sizeof(int));

				ret = removeFila(fila, retirado);

				if(ret){
					printf("Elemento retirado info: %d\n", *retirado);
				}

				break;

			case 3:
				if(filaVazia(fila)){
					printf("Fila vazia!\n");
				}
				else{
					elemento = fila->inicio;

					printf("Printando fila:\n");

					while(elemento != NULL){
						printf("%d ",elemento->info);
						elemento = elemento->prox;
					}

					printf("\n");
				}

				break;

			case 4:
				printf("Número de elementos a inserir: ");
				scanf(" %d", &a);
				
				for(i = 0; i < a; i++){
					elemento = malloc(sizeof(lista_t));
					elemento->info = i;
					insereFila(fila, elemento);
				}

				printf("%d elementos inseridos\n", a);

            			break;

			default:
				printf("FIM\nSaindo...\n");
				break;
		}
		printf("Feito!\n");
	}
	return 0;
}
