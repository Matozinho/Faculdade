#include<stdio.h>
#include <stdio.h>
#include <math.h>

//define os nós que irão conter os elementos
typedef struct Celula
{
    Celula *direita, *abaixo;
    int linha, coluna;
    double valor;
} Celula;

//define as cabeças
typedef struct Matriz
{
	Celula *direita, *baixo;
	int linha, coluna; 
} Matriz;

//inicia a matriz
void initMat(Matriz *M)
{
    M->direita = NULL;
    M->baixo = NULL;
    M->coluna = -1;
    M->linha = -1;
}

// lê a matriz esparça
void leMatriz(int l, int c, Matriz *M)
{
    int i, j;

    for(i=0; i<=l; i++)
    {
        for(j=0; j<=c; j++)
        {
            
        }
    }

}

int main()
{
    Matriz M;
    int m,n; //linhas e colunas
    

    printf("Digite as dimensões da matriz(linhas x colunas):\n");
    scanf("%d %d", &m, &n);

    initMat(&M);

    printf("Digite os elementos da matriz:\n");
    leMatriz(m,n);


    return 0;
}
