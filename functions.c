#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "functions.h"
int QuantThreads; //QUANTIDADE DE THREADS
int Seed=50; //SEED UTILIZADA
int ContprimoS; //CONTADOR DE PRIMOS SEQUENCIAL
int ContprimoP = 0; //CONTADOR DE PRIMOS PARALELO
Matriz *MatPrincipal; //MATRIZ DE NUMEROS
Macrobloco *Macros; //VETOR COM AS INFORMA��ES DOS MACROBLOCOS
int QuantMacro = 0; // NUMERO DE MACROBLOCOS
int Gerenciador = 0; //GERENCIADOR DOS MACROBLOCOS
pthread_mutex_t THREADMACROS; //MUTEX DAS THREADS
pthread_mutex_t THREADPRIMOS; //MUTEX DO CONTADOR
void CriarMatriz(int linha, int coluna){ //FUN��O PARA CRIAR E ALOCAR A MATRIZ DINAMICAMENTE
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
void Preencher(){ //FUN��O QUE PREENCHE A MATRIZ COM NUMEROS ALEATORIOS
    if(MatPrincipal!=NULL){
    srand(Seed);
        for(int i=0; i<MatPrincipal->linha; i++){
            for(int j=0; j<MatPrincipal->coluna; j++){
                MatPrincipal->data[i][j]=rand() % 29999;
            }
        }
    }
}
int Primo(int Numero){ //FUN��O QUE VERIFICA SE O NUMERO � PRIMO
    if(Numero == 0 || Numero == 1 || Numero == NULL){
        return FALSE;
    }
    if(Numero==2){
        return TRUE;
    }
    int cont=2;
    while(cont <= ceil(sqrt(Numero))){
        if(Numero%cont==0){
            return FALSE;
        }
        cont++;
    }
    return TRUE;
}
int Sequencial(){ //FUN��O QUE CALCULA QUANTOS PRIMOS EXISTEM, EXECUTA EM SEQUENCIA
    if(MatPrincipal!=NULL){
        ContprimoS=0;
        for(int i=0; i<MatPrincipal->linha; i++){
            for(int j=0; j<MatPrincipal->coluna; j++){
                //printf("%i ",MatPrincipal->data[i][j]);
                ContprimoS+=Primo(MatPrincipal->data[i][j]);
            }
            //printf("\n");
        }
    }
    return ContprimoS;
}
void FreeMatriz(){ //DESALOCA A MATRIZ
	for (int i = 0; i < MatPrincipal->linha; i++) {
		free(MatPrincipal->data[i]);
	}
	free(MatPrincipal->data);
	free(MatPrincipal);
}
void CriarMacroblocos(float linha, float coluna){ //CRIA A LISTA DE MACROBLOCOS COM SUAS INFORMA��ES
    if(MatPrincipal!=NULL){
        float MacroPorLinha, MacroPorColuna;
        MacroPorLinha=ceil(MatPrincipal->linha/linha);
        MacroPorColuna=ceil(MatPrincipal->coluna/coluna);
        QuantMacro=MacroPorLinha*MacroPorColuna;
        Macros=(Macrobloco*)malloc(sizeof(Macrobloco) * QuantMacro);
        int cont=0;
        for(int i=0; i<MatPrincipal->linha; i+=linha){
            for(int j=0; j<MatPrincipal->coluna; j+=coluna){
                Macros[cont].LinhaI=i;
                Macros[cont].LinhaF=i+linha-1;
                Macros[cont].ColunaI=j;
                Macros[cont].ColunaF=j+coluna-1;
                cont++;
            }
        }
    }
}
void PrintMacros(){//COLOCA NA TELA TODOS OS MACROBLOCOS EXISTENTES E SUAS INFORMA��ES
    if(Macros!=NULL){
        for(int i=0; i<QuantMacro; i++){
            printf("\nMacro %i\nLinha I:%i\tLinha F:%i\nColuna I:%i\tColuna F:%i\n\n",i+1,Macros[i].LinhaI,Macros[i].LinhaF
                   ,Macros[i].ColunaI,Macros[i].ColunaF);
        }
    }
}
void *GercenciadorDeMacros(){//GERENCIADOR DOS MACROBLOCOS PARA AS THREADS
    return (Gerenciador >= QuantMacro) ? NULL : &Macros[Gerenciador++];
}
void *FuncaoThread(){//A FUN��O QUE AS THREADS EXECUTAM SUAS PROGRAMA��ES
    Macrobloco *MacroLocal;
    int i,j, ContPrimoL;
    while(TRUE){
        pthread_mutex_lock(&THREADMACROS); //PEGANDO UM MACROBLOCO
        MacroLocal=(Macrobloco*)GercenciadorDeMacros(); // COLOCANDO NO MACRO LOCAL
        pthread_mutex_unlock(&THREADMACROS);

        if(MacroLocal == NULL){ //SE N TIVER MAIS NENHUM MACRO, A FUN��O SAI DO CICLO
            pthread_exit(NULL);
        }
        ContPrimoL=0; //SENAO O CONTADOR LOCAL ZERA

        for(i=MacroLocal->LinhaI; i<=MacroLocal->LinhaF; i++){//CONTAGEM DOS PRIMOS
            if(MatPrincipal->data[i]!=NULL){
                for(j=MacroLocal->ColunaI; j<=MacroLocal->ColunaF; j++){
                    ContPrimoL+=Primo(MatPrincipal->data[i][j]);
                }
            }
        }

        pthread_mutex_lock(&THREADPRIMOS);//MUTEX QUE GERENCIA A CONTAGEM DE PRIMOS PARALELO
        ContprimoP+=ContPrimoL;
        pthread_mutex_unlock(&THREADPRIMOS);
    }
}
void Paralela(){ //FUN��O QUE AS THREADS EXECUTAM
    int ContThreads, RespThread;
    pthread_t threads[QuantThreads]; //NUMERO DE THREADS

    for(ContThreads=0; ContThreads < QuantThreads; ContThreads++){
        RespThread = pthread_create(&threads[ContThreads], NULL, &FuncaoThread, NULL);
        if(RespThread){
            printf("Erro na THREAD %i\n", ContThreads);
            exit(-1);
        }

    }

    for(ContThreads =0; ContThreads < QuantThreads; ContThreads++){//EXECU��O DAS THREADS
        pthread_join(threads[ContThreads], NULL);
    }
}

void IniciarThreads(){//FUN��O QUE INICIALIZA OS MUTEXES
    pthread_mutex_init(&THREADMACROS,NULL);
    pthread_mutex_init(&THREADPRIMOS,NULL);
}

int GetContPrimoP(){ //FUN��O QUE RESGATA O NUMERO TOTAL DE PRIMOS NA CONTAGEM PARALELA
    return ContprimoP;
}

void ModificarThreads(int Num){ //FUN��O QUE MODIFICA A QUANTIDADE DE THREADS
    QuantThreads=Num;
}
