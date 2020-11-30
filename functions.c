#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <C:\Users\hiago\Documents\C\PRIMOS\functions.h>

int ContprimoS; //CONTADOR DE PRIMOS SEQUENCIAL
int ContprimoP = 0; //CONTADOR DE PRIMOS PARALELO
Matriz *MatPrincipal; //MATRIZ DE NUMEROS
Macrobloco *Macros; //VETOR COM AS INFORMAÇÕES DOS MACROBLOCOS
int QuantMacro; // NUMERO DE MACROBLOCOS
int Gerenciador = 0; //GERENCIADOR DOS MACROBLOCOS
pthread_mutex_t THREADMACROS; //MUTEX DAS THREADS
pthread_mutex_t THREADPRIMOS; //MUTEX DO CONTADOR
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
                MatPrincipal->data[i][j]=rand() % 9;
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
void CriarMacroblocos(float linha, float coluna){
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
void PrintMacros(){
    if(Macros!=NULL){
        for(int i=0; i<QuantMacro; i++){
            printf("\nMacro %i\nLinha I:%i\tLinha F:%i\nColuna I:%i\tColuna F:%i\n\n",i+1,Macros[i].LinhaI,Macros[i].LinhaF
                   ,Macros[i].ColunaI,Macros[i].ColunaF);
        }
    }
}
void *GercenciadorDeMacros(){
    return (Gerenciador >= QuantMacro) ? NULL : &Macros[Gerenciador++];
}
void *FuncaoThread(){
    Macrobloco *MacroLocal;
    int i,j, ContPrimoL;
    while(TRUE){
        pthread_mutex_lock(&THREADMACROS);
        MacroLocal=(Macrobloco*)GercenciadorDeMacros();
        pthread_mutex_unlock(&THREADMACROS);

        if(MacroLocal == NULL){
            pthread_exit(NULL);
        }
        ContPrimoL=0;

        for(i=MacroLocal->LinhaI; i<=MacroLocal->LinhaF; i++){
            for(j=MacroLocal->ColunaI; j<=MacroLocal->ColunaF; j++){
                if(Primo(MatPrincipal->data[i][j])){
                    ContPrimoL++;
                }
            }
        }

        pthread_mutex_lock(&THREADPRIMOS);
        ContprimoP+=ContPrimoL;
        pthread_mutex_unlock(&THREADPRIMOS);
    }
}
void Paralela(){
    int ContThreads, RespThread;
    pthread_t threads[4];

    for(ContThreads=0; ContThreads < 4; ContThreads++){
        RespThread = pthread_create(&threads[ContThreads], NULL, &FuncaoThread, NULL);
        if(RespThread){
            printf("Erro na THREAD %i\n", ContThreads);
            exit(-1);
        }

    }

    for(ContThreads =0; ContThreads < 4; ContThreads++){
        pthread_join(threads[ContThreads], NULL);
    }
}
