#include "nqueens.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#define num_threads 4

typedef struct Argumentos{
  int **tab;
  int dim, queens, lin, contQ;
}Arg;

typedef struct ArgumentosS{
  int **tab;
  int dim;
  //int queens;
}ArgS;

pthread_mutex_t mutex,mutex_soma,mutex_sol; 
sem_t m;

//variável compartilhada
unsigned long long soma = 0;

int **alocaTabuleiro(int dim);
void inicializaTabuleiro(int **tab, int dim);
void liberaTabuleiro(int **tab,int dim);
void imprimeTabuleiro(int **tab,int dim);
int verificaPosicao(int **tab,int dim,int lin,int cont);
unsigned long long nqueens(int dim,int queens);
Arg *criaArgs(int **tab,int dim,int queens,int lin,int contQ);
ArgS *criaArgSoma(int **tab,int dim);
void *inicializa(void *args);
void *posicionaRainha(void *args);
void *calculaPos(void *args);


/* Função que retorna a soma das posições da rainhas em cada umas das soluções */
unsigned long long nqueens(int dim,int queens){
  int **tab, i;
  unsigned long long somaP = 0;
  soma = 0;

  pthread_t threads[num_threads]; 

  //verifica foram passados parametros invalidos
  if(queens == 0 || dim < 1 || queens > dim){
      return 0; //parametro invalido
  }

  tab = alocaTabuleiro(dim); //aloca espaco de memoria para o tabuleiro
  if(tab == NULL){
     exit(1);
  }

  inicializaTabuleiro(tab,dim); //inicializa posições do tabuleiro com zero

  sem_init(&m,0,1); 

  pthread_mutex_init(&mutex,NULL);
  pthread_mutex_init(&mutex_soma,NULL);
  pthread_mutex_init(&mutex_sol,NULL);

  for(i = 0; i < num_threads; ++i){
     pthread_create(&threads[i],NULL,inicializa,(void *)criaArgs(tab,dim,queens,0,0));
  }

  for(i = 0; i < num_threads; ++i){
   pthread_join(threads[i],NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutex_soma);
  pthread_mutex_destroy(&mutex_sol);

  sem_destroy(&m);
  somaP=soma;
  somaP/=num_threads;
  
  liberaTabuleiro(tab,dim); //desaloca a memoria alocada para o tabuleiro  

  return somaP; // retorna a soma das posições que a rainha(s) pode assumir em todas as soluções possiveis
}


/* Função que cria os argumentos a serem passados para a função que posiciona a rainha no tabuleiro */
Arg *criaArgs(int **tab,int dim,int queens,int lin,int contQ){
    Arg *arg = malloc(sizeof(Arg));
    arg->tab = tab;
    arg->dim = dim;
    arg->queens = queens;
    arg->lin = lin;
    arg->contQ = contQ;
    return arg;
}

/* Função que cria os argumentos a serem passados para a função do calculo das posições */
ArgS *criaArgSoma(int **tab,int dim){
    ArgS *arg = malloc(sizeof(ArgS));
    arg->tab = tab;
    arg->dim = dim;
    return arg;
}


void *inicializa(void *args){
     Arg *arg = args;
     sem_wait(&m);
     pthread_mutex_lock(&mutex);
     posicionaRainha(criaArgs(arg->tab,arg->dim,arg->queens,arg->lin,arg->contQ));
     pthread_mutex_unlock(&mutex);
     sem_post(&m);
     free(arg);
     pthread_exit(NULL);
     return arg;
}

/* Função que posiciona a rainha no tabuleiro e faz o calculo das posições possiveis */
void *posicionaRainha(void *args){
     Arg *arg = args;
     int i,j;

     if(arg->contQ==arg->queens){
      pthread_mutex_lock(&mutex_soma);
      soma += (unsigned long long) calculaPos(criaArgSoma(arg->tab,arg->dim));
      pthread_mutex_unlock(&mutex_soma);

     }

     for(i = arg->lin; i < arg->dim; ++i){
       for(j = 0; j < arg->dim; ++j){
           if(verificaPosicao(arg->tab,arg->dim,i,j)){ //verifica se a posição é valida
              pthread_mutex_lock(&mutex_sol);
              arg->tab[i][j] = 1; //posiciona a rainha no tabuleiro
              pthread_mutex_unlock(&mutex_sol);
            if(posicionaRainha(criaArgs(arg->tab,arg->dim,arg->queens,i+1,arg->contQ+1))){ //usa recursão para inserir o resto das rainhas
               return (void *)1;
            }else{
               arg->tab[i][j] = 0; //se não leva a uma solução remove a rainha
            }
         }     
       }
     }

     free(arg);
     return (void *)0;
}


/* Função que realiza o calculo de todas as posições que levam a alguma solução */
void *calculaPos(void *args){
   Arg *arg = args;
   int i, j, cont = 0;
   unsigned long long somaPos = 0;

    for (i = 0; i < arg->dim; ++i){
      for (j = 0; j < arg->dim; ++j){
        pthread_mutex_lock(&mutex_sol);
        if(arg->tab[i][j]){
           somaPos += pow(2, cont); //calcula a posição da rainha em cada solução
        }
        cont++; //incrementa casa do tabuleiro
        pthread_mutex_unlock(&mutex_sol);
      }
    }
    free(arg);
    return (void *)somaPos;
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
