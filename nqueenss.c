#include "nqueens.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
   Versão sequencial do trabalho 1 
*/

//variável compartilhada
unsigned long long soma = 0;


int **alocaTabuleiro(int dim);
void inicializaTabuleiro(int **tab, int dim);
void liberaTabuleiro(int **tab,int dim);
void imprimeTabuleiro(int **tab,int dim);
int verificaPosicao(int **tab,int dim,int lin,int cont);
unsigned long long calculaPos(int **tab,int dim,int queens);
int posicionaRainha(int **tab,int dim,int queens,int lin,int contQ);
unsigned long long nqueens(int dim,int queens);


/* Função que retorna a soma das posições da rainhas em cada umas das soluções */
unsigned long long nqueens(int dim,int queens){
  int **tab;
  soma = 0;

  //verifica foram passados parametros invalidos
  if(queens == 0 || dim < 1 || queens > dim){
      return 0; //parametro invalido
  }

  tab = alocaTabuleiro(dim); //aloca espaco de memoria para o tabuleiro
  if(tab == NULL){
     exit(1);
  }

  inicializaTabuleiro(tab,dim); //inicializa posições do tabuleiro com zero

  posicionaRainha(tab,dim,queens,0,0); //acha as soluções possiveis e calcula a soma das posições
  liberaTabuleiro(tab,dim); //desaloca a memoria alocada para o tabuleiro

  return soma; // retorna a soma das posições que a rainha(s) pode assumir em todas as soluções possiveis
}

/* Função que posiciona a rainha no tabuleiro e faz o calculo das posições possiveis */
int posicionaRainha(int **tab,int dim,int queens,int lin,int contQ){
    int i,j;

    if(contQ == queens){ //verifica se já inseriu a quantidade de rainhas desejada
        if(queens==1){ //verifica se apenas uma rainha estar sendo inserida
          soma = calculaPos(tab,dim,queens);
        }else{ //caso tenha mais de uma rainha sendo inserida
          soma += calculaPos(tab,dim,queens);
        }
    }

    for(i = lin; i < dim; ++i){
       for(j = 0; j < dim; ++j){
           if(verificaPosicao(tab,dim,i,j)){ //verifica se a posição é valida
               tab[i][j] = 1; //posiciona a rainha no tabuleiro
             if(posicionaRainha(tab,dim,queens,i+1,contQ+1)){ //usa recursão para inserir o resto das rainhas
                return 1;
              }else{
                tab[i][j] = 0; //se não leva a uma solução remove a rainha
              }
           }
       }
    }   
    return 0;
}

/* Função que realiza o calculo de todas as posições que levam a alguma solução */
unsigned long long calculaPos(int **tab,int dim,int queens){
    int i, j, cont = 0;
    unsigned long long somaPos = 0;

    for (i = 0; i < dim; ++i){
      for (j = 0; j < dim; ++j){
        if(tab[i][j]){
          if(queens==1){  //caso apenas uma rainha esteja sendo inserida no tabuleiro
            somaPos = pow(2,pow(dim,2))-1;
          }
          else{ 
            somaPos += pow(2, cont); //calcula a posição da rainha em cada solução
          }
        }
            cont++; //incrementa casa do tabuleiro
      }
    }
     return somaPos;
}


/* Função que verifica se a rainha estar sendo inserida em uma posição valida*/
int verificaPosicao(int **tab,int dim,int lin,int col){
      int i, j;

      for(j = 0; j < col; ++j){
         if(tab[lin][j]){  //verifica se exista alguma rainha na mesma linha
           return 0; //posição invalida
         }
      }
  
      for(i = 0; i < lin; ++i){
         if(tab[i][col]){ //verifica se existe alguma rainha na mesma coluna
            return 0; //posicao invalida
         }
      }

      for(i = lin, j = col; i >= 0 && j >= 0; --i,--j){
        if(tab[i][j]){ //verifica se exista alguma rainha na diagonal superior
          return 0; //posicao invalida
        }
      }

      for(i = lin, j = col; i >= 0 && j < dim; --i,++j){
         if(tab[i][j]){ //verifica se existe alguma rainha na diagonal inferior
           return 0; //posicao invalida
         }
      }

      return 1; //estar inserindo em uma posicao valida
}


/* Função que aloca espaço de memoria para a criação do tabuleiro */
int **alocaTabuleiro(int dim){
    int i;
    int **tab = (int **)calloc(dim, sizeof(int *));
    if(tab==NULL){
      return NULL;
    }
    for(i = 0; i < dim; ++i){
      tab[i] = (int *)calloc(dim, sizeof(int *));
      if(tab[i]==NULL){
        return NULL;
      }
    }
    return tab;
}

/* Função que inicializa o tabuleiro */
void inicializaTabuleiro(int **tab, int dim){
  int lin,col;
  for(lin = 0; lin < dim; ++lin){
    for(col = 0; col < dim; ++col){
        tab[lin][col] = 0;
    }
  }
}

/* Função que imprime o tabuleiro*/
void imprimeTabuleiro(int **tab,int dim){
    int lin,col;
    for(lin = 0; lin < dim; ++lin){
      for(col = 0; col < dim; ++col){
        if(tab[lin][col]){
          printf("X ");
        }else{
          printf("0 ");
        }
      }
      printf("\n");
    }
    printf("\n");
}


/* Função que desaloca a memoria alocada para o tabuleiro */
void liberaTabuleiro(int **tab,int dim){
  int i;
  for(i = 0; i < dim; ++i){
    free(tab[i]);
  }
  free(tab);
}