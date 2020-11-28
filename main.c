#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <C:\Users\hiago\Documents\C\PRIMOS\functions.h>

int main(){
    CriarMatriz(MATRIZ_LINHAS, MATRIZ_COLUNAS);
    Preencher();
    printf("Existem %d primos", Sequencial());
    FreeMatriz();
}
