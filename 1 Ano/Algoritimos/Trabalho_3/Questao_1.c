#include <stdio.h>
#include <stdlib.h>


typedef struct Celula
{
  struct Celula *direita,*abaixo;
  int linha,coluna;
  double valor;
} Celula;

typedef struct TMatriz
{
    Celula *inicio;
    short m,n;
} TMatriz;

//Função de inicializar qualquer matriz
int iniciar(TMatriz *matriz,int m,int n)
{
  int i,j;
  Celula *aux,*P;
  //Aloca o primeiro bloco (-1,-1)
  aux= (Celula*)malloc(sizeof(Celula));

  //A matriz recebe esse bloco como o inicio
  matriz->inicio=aux;

  //Define o tamanho da matriz
  matriz->m=m;
  matriz->n = n;

  //Configura o "bloco"
  aux->abaixo= aux;
  aux->direita= aux;
  aux->linha=-1;
  aux->coluna=-1;
  aux->valor= 0;

  P= matriz->inicio;

  //Cria os elementos para as linhas
  for(i=1;i<=m;i++)
  {
    aux= (Celula*)malloc(sizeof(Celula)); //Aloca o bloco
    if(aux==NULL) //Se estiver nulo, deu erro de alocação
      return 1;

    P->abaixo= aux;
    aux->direita= aux;

    aux->valor=0;
    aux->coluna= 0;
    aux->linha=-1;

    //O elemento de cima vai apontar para ele
    P= aux;
  }
  //Faz a ultima linha apontar o ponteiro de baixo para o bloco inicial
  P->abaixo= matriz->inicio;
  P= matriz->inicio;

  //Cria os elementos para colunas
  for(j=1;j<=n;j++)
  {
    aux= (Celula*)malloc(sizeof(Celula)); //Aloca o bloco
    if(aux==NULL) //Se estiver nulo, significa que deu erro
      return 1;

    P->direita= aux;
    aux->abaixo=aux;

    aux->valor=0;
    aux->coluna= -1;
    aux->linha=0;

    //O elemento da esquerda vai apontar para ele
    P=aux;
  }
    //Faz a ultima coluna apontar o ponteiro da direita para o bloco inicial
  P->direita=matriz->inicio;
  return 0;
}

//Função de apagar matriz
void apagar(TMatriz *matriz)
{
  Celula *aux,*prox,*p1;
  aux= matriz->inicio;
  while(matriz->n)
  {
    if(aux->direita)
      prox=aux->direita;
    while(matriz->m)
    {
      p1= aux;
      if(aux->abaixo)
        aux= aux->abaixo;
      free(p1);
      matriz->m--;
    }
    aux= prox;
    matriz->n--;
  }
  matriz->inicio=NULL;
}

//Função de printar a matriz
void imprimeMatriz(TMatriz matriz)
{
  int m=1,n=1;
  Celula *aux,*P1;

  P1= matriz.inicio;
  for(m=1;m<=matriz.m;m++)
  {
      printf("| ");
    //P1 já avança para o bloco de baixo
    P1= P1->abaixo;
    //Aux recebe o primeiro bloco real(que tem um valor) da linha
    aux=P1->direita;
    for(n=1;n<=matriz.n;n++) //Enquanto tiver colunas, ele executa
    {
        if(n==aux->coluna) //Se o "n" for igual da coluna do bloco, ele printa e avança,pois significa que não pulou nenhum bloco
        {
          printf("%.1lf ",aux->valor);
          aux = aux->direita;
        }
        else //se não, significa que pulou algo, ou seja, não existe
          printf("0 ");
    }
    printf("|");
    printf("\n");
  }
}

//Função de inserir um elemento
void insere(int m,int n, double v, TMatriz* matriz)
{
  int i,j;
  Celula *ultimoCol, *ultimoLin,*P;
  ultimoCol = ultimoLin = matriz->inicio;

  //Chegam na coluna e linha que é pra mudar
  for(i=0;i<n;i++)
    ultimoCol= ultimoCol->direita;

  for(j=0;j<m;j++)
    ultimoLin = ultimoLin->abaixo;

  //Acham as posições mais próximas do bloco
  for(i=1;i<=m-1;i++)
    if(ultimoCol->abaixo->coluna!=-1 && ultimoCol->abaixo->linha!=m) //Verifica se não avançou demais
      ultimoCol = ultimoCol->abaixo;
    else
        break;
  for(j=1;j<=n-1;j++)
    if(ultimoLin->direita->linha!=-1 && ultimoLin->direita->coluna!=n) //Verifica se não avançou muito
      ultimoLin = ultimoLin->direita;
    else
        break;


  if(ultimoLin->direita->coluna==n) //Verifica se é um novo bloco
  {
      if(v) //Verifica se não é um valor nulo
      {
        ultimoLin= ultimoLin->direita; //Avança p/ o bloco existente
        ultimoLin->valor= v;
      }
      else
      {
        //P recebe o próximo bloco(o que vai ser eliminado)
        P = ultimoLin->direita;

        //Muda os ponteiros corretamente para pular o bloco atual
        ultimoLin->direita= P->direita;
        ultimoCol->abaixo= P->abaixo;

        //Libera o bloco que agora é 0
        free(P);
      }
  }
  else
  {

    if(v) //Verifica se "v" não é 0
    {
     //Aloca memória
      P = (Celula*)malloc(sizeof(Celula));

      //Subsititui os nós
      P->direita= ultimoLin->direita;
      P->abaixo= ultimoCol->abaixo;
      ultimoCol->abaixo=P;
      ultimoLin->direita= P;

      //Salva as info do vetor
      P->linha=m;
      P->coluna= n;
      P->valor= v;
      return;
    }
    else
      return;
  }
}

//Função de ler matriz
void leMatriz(TMatriz* matriz)
{

  int y,x,i,j,m,n;
  double valor=1;
  printf("\tDigite o tamanho da matriz(linhas x colunas): ");
  scanf("%d %d",&m,&n);

  if(!iniciar(matriz,m,n)) //Inicia a matriz
  {
    printf("\tDigite os valores: \n");
    for(x=1;x<=m;x++)
    {
      for(y=1;y<=n;y++,valor++)
      {
        scanf("%lf",&valor);
        insere(x,y,valor,matriz);
      }

	}
      //imprimeMatriz(*matriz);
  }
  else printf("Erro de inicialização");

}

void somamatriz(TMatriz *matriz1,TMatriz *matriz2)
{
    TMatriz matrizcalculada;
    Celula *P1,*P2;
    int i,j;
    double soma;
    if(matriz1->m==matriz2->m && matriz1->n==matriz2->n) //Verifica se os tamanhos são iguais
    {
        iniciar(&matrizcalculada,matriz1->m,matriz1->n);

        //Define os ponteiros no elemento da primeira linha
        P1= matriz1->inicio->abaixo;
        P2= matriz2->inicio->abaixo;
        for(i=1;i<=matriz1->m;i++)
        {
            //Avança para as colunas
            P1= P1->direita;
            P2= P2->direita;

            for(j=1;j<=matriz1->n;j++)
            {
                soma=0; //Reseta o valor a soma

                //Se "j" for igual à coluna do elemento, significa que está no posição correta, logo ele soma
                if(j==P1->coluna)
                {
                    soma+= P1->valor;
                    P1= P1->direita;
                }
                if(j==P2->coluna)
                {
                    soma+= P2->valor;
                    P2= P2->direita;
                }

                //Insere a soma na matriz
                insere(i,j,soma,&matrizcalculada);
            }
            //Vão para a proxima linha
            P1= P1->abaixo;
            P2= P2->abaixo;
        }

        imprimeMatriz(matrizcalculada);
        apagar(&matrizcalculada);
    }
    else
    {
        printf("Tamanhos de matrizes incompatíveis\n");
        return;
    }
}

void multiplicamatriz(TMatriz *matriz1,TMatriz *matriz2)
{
    TMatriz matrizmultiplicada;
    Celula *P1,*P2,*aux, *aux1, *aux2;
    double soma;
    int i,j,k;


    if(matriz1->n == matriz2->m) //Verifica se os tamanhos estão corretos
    {
        //Inicia a matriz onde vai ser salva o resultado
        iniciar(&matrizmultiplicada,matriz1->m,matriz2->n);

        //Recebe a primeira linha
        aux1 = matriz1->inicio->abaixo;
        aux2 = matriz2->inicio->direita;

        for(i=1;i<=matriz1->m;i++)
        {
            for(j=1;j<=matriz2->n;j++)
            {
                 //Reseta a soma
                 soma=0;
                
                //reseta os ponteiros para os valores reais
                 P1 = aux1->direita;
                 P2 = aux2->abaixo;

                 for(k=1; k<=matriz2->m && (P1->linha != -1) && (P2->coluna != -1) ;k++)
                 {
                    if(P1->coluna == P2->linha)
                    {
                        soma += P1->valor*P2->valor;
                        P1 = P1->direita;
                        P2 = P2->abaixo;
                    }
                    else 
                    {
                        if(P1->coluna < k+1)
                            P1 = P1->direita;
                        if(P2->linha < k+1)
                            P2 = P2->abaixo;
                    }  
                 }
                 insere(i,j,soma,&matrizmultiplicada);
                 //transfere para a próxima sequencia de colunas
                 aux2 = aux2->direita;
            }
            //tranfere para a próxima sequencia de linhas
            aux1 = aux1->abaixo;
            //reinicia as colunas
            aux2 = matriz2->inicio->direita;
        }
        printf("Matriz Resultante: \n");
        imprimeMatriz(matrizmultiplicada);
        apagar(&matrizmultiplicada);
    }
    else
    {
        printf("Tamanhos de matrizes incompatíveis\n");
        return;
    }
}
void interface()
{
  TMatriz matriz,matriz2;
  int opcao=1,i,j;
  double valor;
  void (*funcao[6])();
  funcao[0]= imprimeMatriz;
  funcao[1]= leMatriz;
  funcao[2]= somamatriz;
  funcao[3]= multiplicamatriz;
  funcao[4] = insere;

  while(opcao)
  {
    printf("\tMatriz Esparsas\n");
    printf("\tMenu Principal\n");

    printf("\t[0] Sair\n");
    printf("\t[1] Printar/Imprimir a matriz\n");
    printf("\t[2] Ler Matriz\n");
    printf("\t[3] Somar Matrizes\n");
    printf("\t[4] Multiplicar matrizes\n");
    printf("\t[5] Inserir valor\n");
    printf("\tQual opcao voce deseja executar?  ");
    scanf("%d",&opcao);

    if(opcao>0 && opcao<6)
    {
      if(opcao==1)
        (*funcao[opcao-1])(matriz);
      else if(opcao==2)
        (*funcao[opcao-1])(&matriz);
      else if(opcao == 3 || opcao == 4)
      {
          printf("\tMatriz 1: \n");
          leMatriz(&matriz);
          printf("\tMatriz 2: \n");
          leMatriz(&matriz2);
          (*funcao[opcao-1])(&matriz,&matriz2);
      }
      else if(opcao==5)
      {
        printf("\tDiga a posição(linha,coluna) e o valor a ser inserido: ");
        scanf("%d %d %lf",&i,&j,&valor);
        (*funcao[opcao-1])(i,j,valor,&matriz);
        imprimeMatriz(matriz);
      }
    }
    apagar(&matriz);
    apagar(&matriz2);
  }
}

int main()
{
  interface();
}
