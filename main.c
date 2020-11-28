#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <C:\Users\hiago\Documents\C\PRIMOS\functions.h>
int main(){
    CriarMatriz(7, 4);
    Preencher();
    printf("Existem %d primos", Sequencial());
    CriarMacroblocos(3,3);
    PrintMacros();
    FreeMatriz();
}
