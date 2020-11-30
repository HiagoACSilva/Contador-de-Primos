#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "functions.h"
int main(){
    //VARIAVEIS PARA CALCULAR A QUANTIDADE DE TEMPO GASTA
    clock_t TempoIS;//TEMPO INICIAL DO SEQUENCIAL
	clock_t TempoFS;//TEMPO FINAL DO SEQUENCIAL
	clock_t TempoIP;//TEMPO INICIAL DO PARALELO
	clock_t TempoFP;//TEMPO FINAL DO PARALELO
    int LM, CM, Qt, Lm, Cm;//LINHAS E COLUNAS DA MATRIZ E DOS MACROBLOCOS E A QUANTIDADE DE THREADS
    printf("\tContador De Primos\nDigite a quantidade de Linhas e Colunas da Matriz\n");
    scanf("%i%i", &LM, &CM);
    printf("\nDigite a quantidade de Linhas e Colunas dos Macroblocos\n");
    scanf("%i%i", &Lm, &Cm);
    printf("\nDigite a quantidade de Threads a se utilizar\n");
    scanf("%i",&Qt);
    CriarMatriz(LM, CM);//CRIA플O DA MATRIZ
    Preencher();//PREENCHIMENTO DE NUMEROS DE 0 A 29999
    ModificarThreads(Qt);
    TempoIS = clock(); //EXECU플O DO SEQUENCIAL
    int PrimosS=Sequencial();
    TempoFS = clock(); //FINAL DA EXECU플O DO SEQUENCIAL

    CriarMacroblocos(Lm,Cm); //CRIA플O DOS MACROBLOCOS

    //PrintMacros(); //FUN플O PARA PRINTAR OS MACROBLOCOS

    IniciarThreads(); //INICIALIZA플O DAS THREADS

    TempoIP = clock(); //EXECU플O DO PARALELO
    Paralela();
    TempoFP = clock(); //FINAL DA EXECU플O DO PARALELO

    printf("\nBUSCA SEQUENCIAL\nPrimos encontrados na matriz: %i\n", PrimosS);
	printf("Time: %.3f\n", (double)(TempoFS - TempoIS)/CLOCKS_PER_SEC); //CALCULO DO TEMPO SEQUENCIAL
	printf("\nBUSCA PARALELA\nPrimos encontrados na matriz: %i\n", GetContPrimoP());
	printf("Time: %.3f\n", (double)(TempoFP - TempoIP) / CLOCKS_PER_SEC); // CALCULO DO TEMPO PARALELO

    FreeMatriz();
}
