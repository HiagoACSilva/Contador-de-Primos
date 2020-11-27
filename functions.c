#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <C:\Users\hiago\Documents\C\Primos\functions.h>

int **Matriz(int Tamanho){
    int **matriz;
    matriz=(int**)malloc(sizeof(int*) * Tamanho);
    if(matriz!=NULL){
        for(int i=0; i<Tamanho; i++){
            matriz[i]=(int*)malloc(sizeof(int) * Tamanho);
        }
    }
    return matriz;
}
void Preencher(int **matriz, int Tamanho){
    if(matriz!=NULL){
    srand(50);
        for(int i=0; i<Tamanho; i++){
            for(int j=0; j<Tamanho; j++){
                matriz[i][j]=rand() % 29999;
            }
        }
    }
}
bool Primo(int Numero){
    int cont=2;
    while(cont <= ceil(sqrt(Numero))){
        if(Numero%cont==0){
            return FALSE;
        }
        cont++;
    }
    return TRUE;
}
int Sequencial(int **matriz, int tam){
    int cont=0;
    if(matriz!=NULL){
        for(int i=0; i<tam; i++){
            for(int j=0; j<tam; j++){
                printf("%i ",matriz[i][j]);
                if(Primo(matriz[i][j])){
                    cont++;
                }
            }
                printf("\n");
        }
    }
    return cont;
}
