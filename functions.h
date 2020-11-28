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
typedef struct MACROBLOCO{
    int LinhaI, LinhaF, ColunaI, ColunaF;
}Macrobloco;
void CriarMatriz(int , int); //CRIAR MATRIZ
void Preencher();//PREENCHER MATRIZ
bool Primo(int);//RETORNA SE O NUMERO É PRIMO OU NÃO
int Sequencial();
void FreeMatriz();
void CriarMacroblocos(float linha, float coluna);

#endif // FUNCTIONS_H
