#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#ifndef TRUE
#define TRUE 1
#endif // TRUE
#ifndef FALSE
#define FALSE 0
#endif // FALSE

int **Matriz(int Tamanho); //CRIAR MATRIZ
void Preencher(int **matriz, int Tamanho);//PREENCHER MATRIZ
bool Primo(int Numero);//RETORNA SE O NUMERO É PRIMO OU NÃO
int Sequencial(int **matriz, int tam);


#endif // FUNCTIONS_H
