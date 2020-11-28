#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#ifndef TRUE
#define TRUE 1
#endif // TRUE
#ifndef FALSE
#define FALSE 0
#endif // FALSE
#define MATRIZ_LINHAS 5
#define MATRIZ_COLUNAS 5
typedef struct MATRIZ{
    int **data, linha, coluna;
}Matriz;
void CriarMatriz(int , int); //CRIAR MATRIZ
void Preencher();//PREENCHER MATRIZ
bool Primo(int);//RETORNA SE O NUMERO É PRIMO OU NÃO
int Sequencial();
void FreeMatriz();

#endif // FUNCTIONS_H
