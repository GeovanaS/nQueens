
#ifndef _NQUEENS_
#define _NQUEENS_

#include <stdint.h> 

/** Calcula a soma das posicoes de rainhas que nao se atacam em tabuleiros de dim x dim 
  * Cada posicao do tabuleiro é uma potencia de dois (2^0, 2^1, ...), da esquerda para direita,
  * de cima para baixo.
  *
  * Ex: 3x3 
  * X 0 0    0 X 0   
  * 0 0 X    0 0 0   ...
  * 0 0 0    X 0 0
  *
  * 2^0 + 2^5 = 1 + 32 = 33 
  * 2^1 + 2^6 = 2 + 64 = 66
  * ...
  * Os valores de todas as possibilidades devem ser somados e retornados pela funcao
  * Caso os parametros sejam invalidos, retorne 0
  */
unsigned long long nqueens(int dim, int queens);

#endif
