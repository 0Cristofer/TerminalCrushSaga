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
    int opt = 1;
    fila_t* fila;
    lista_t* elemento;
    lista_t* retirado;

    fila = malloc(sizeof(fila_t));
    printf("Teste da biblioteca de fila implementada com lista ligada!\n");

    inicializaFila(fila);
    printf("------Menu------\n1 - Inserir elemento na fila\n2 - Retirar e printar elemento da fila\n3 - printar todos elementos da fila\n\n0 - Sair\n---------------------------\n");
    while(opt > 0){
        scanf("%d",&opt);
        switch(opt){
            case 1:
                elemento = malloc(sizeof(lista_t));
                printf("Insira info (Generic info test): ");
                scanf("%d",&elemento->info);
                insereFila(fila,elemento);
                break;

            case 2:
                retirado = malloc(sizeof(lista_t));
                removeFila(fila, retirado);
                printf("Elemento retirado info: %d\n",retirado->info);
                break;

            case 3:
                if(fila->inicio == NULL){
                    printf("Fila vazia!\n");
                } else{
                    elemento = fila->inicio;
                    printf("Printando fila:\n");
                    while(elemento != NULL){
                        printf("%d ",elemento->info);
                        elemento = elemento->prox;
                    }
                    printf("\n");
                }
                break;

            default:
                printf("FIM\nSaindo...\n");
                return 0;
        }
        printf("Feito!\n");
    }
}
