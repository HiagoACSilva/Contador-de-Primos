#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <C:\Users\hiago\Documents\C\Primos\functions.h>

int main(){
    int **matriz;
    int tam;
    printf("Digite o tamanho da matriz\n");
    scanf("%d",&tam);
    matriz=Matriz(tam);
    Preencher(matriz, tam);
    int cont;
    cont=Sequencial(matriz,tam);
    printf("Existem %i primos", cont);
}
