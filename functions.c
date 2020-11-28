#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <C:\Users\hiago\Documents\C\PRIMOS\functions.h>

int ContprimoS;
Matriz *MatPrincipal;

void CriarMatriz(int linha, int coluna){
    MatPrincipal=(Matriz*)malloc(sizeof(Matriz));
    if(MatPrincipal!=NULL){
        MatPrincipal->linha=linha;
        MatPrincipal->coluna=coluna;
        MatPrincipal->data=(int**)malloc(sizeof(int*) * linha);
        if(MatPrincipal->data!=NULL){
            for(int i=0; i<linha; i++){
                MatPrincipal->data[i]=(int*)malloc(sizeof(int) * coluna);
            }
        }
    }
}
void Preencher(){
    if(MatPrincipal!=NULL){
    srand(89);
        for(int i=0; i<MatPrincipal->linha; i++){
            for(int j=0; j<MatPrincipal->coluna; j++){
                MatPrincipal->data[i][j]=rand() % 29999;
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
int Sequencial(){
    if(MatPrincipal!=NULL){
        ContprimoS=0;
        for(int i=0; i<MatPrincipal->linha; i++){
            for(int j=0; j<MatPrincipal->coluna; j++){
                printf("%i ",MatPrincipal->data[i][j]);
                if(Primo(MatPrincipal->data[i][j])){
                    ContprimoS++;
                }
            }
                printf("\n");
        }
    }
    return ContprimoS;
}
void FreeMatriz(){
	for (int i = 0; i < MatPrincipal->linha; i++) {
		free(MatPrincipal->data[i]);
	}
	free(MatPrincipal->data);
	free(MatPrincipal);
}
