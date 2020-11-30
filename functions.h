#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#ifndef TRUE
#define TRUE 1
#endif // TRUE
#ifndef FALSE
#define FALSE 0
#endif // FALSE
typedef struct MATRIZ{ //STRUCT DA MATRIZ PRINCIPAL
    int **data, linha, coluna;
}Matriz;
typedef struct MACROBLOCO{//STRUCT DOS MACROBLOCOS
    int LinhaI, LinhaF, ColunaI, ColunaF;
}Macrobloco;
void CriarMatriz(int , int); //CRIAR MATRIZ
void Preencher();//PREENCHER MATRIZ
int Primo(int);//RETORNA SE O NUMERO É PRIMO OU NÃO
int Sequencial();//RETORNA NUMERO DE PRIMOS DA CONTAGEM SEQUENCIAL
void FreeMatriz();//LIBERA A MATRIZ
void CriarMacroblocos(float , float);//CRIA O VETOR DE MACROBLOCOS
void PrintMacros();//MOSTRA NA TELA OS MACROBLOCOS
void *GercenciadorDeMacros(); // GERENCIA OS MACROS PARA AS THREADS
void *FuncaoThread(); //AS THREADS EXECUTAM AQUI
void Paralela(); //A FUNÇÃO QUE AS THREADS EXECUTAM
void IniciarThreads();//INICIADOR DOS MUTEXES
int GetContPrimoP(); //O GET DA CONTAGEM DOS NUMEROS PRIMOS CONTADOS EM PARALELO
void ModificarThreads(int); //FUNÇÃO PARA MODIFICAR O NUMERO DE THREADS
#endif // FUNCTIONS_H
