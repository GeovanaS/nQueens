#include <stdio.h>
#include "nqueens.h"
#include "simplegrade.h"


void testes_parametros(){
	DESCRIBE("Testes com parametros que devem falhar");

	WHEN("Numero de rainhas ou dimensoes sao negativos");
	THEN("Nao deve executar");

	isEqual_long(nqueens(-1, -1),0,1);
	isEqual_long(nqueens(-1, 2),0,1);
	isEqual_long(nqueens(2, -1),0,1);

	WHEN("Numero de rainhas ou dimensoes sao zero");
	THEN("Nao deve executar");

	isEqual_long(nqueens(2, 0),0,1);
	isEqual_long(nqueens(0, 2),0,1);
}

void testes_uma_rainha(){
	DESCRIBE("Testes com uma rainha e diversos tamanhos de tabuleiro");

	WHEN("A rainha pode ser colocada em qualquer casa");
	THEN("O resultado deve ser 2^(dim^2) - 1");

	isEqual_long(nqueens(1,1),1,1); 
	isEqual_long(nqueens(2,1),15,1);
	isEqual_long(nqueens(3,1),511,1);
	isEqual_long(nqueens(4,1),65535,1);
	isEqual_long(nqueens(5,1),33554431,1);
	isEqual_long(nqueens(6,1),68719476735,1);

}

void testes_rainhas_mais_que_tabuleiro(){
	DESCRIBE("Testes com número de rainhas que não cabem no tabuleiro");

	WHEN("O numero de rainhas eh maior que o lado do tabuleiro");
	THEN("Nao ha resultado viavel");

	isEqual_long(nqueens(1,2),0,1);
	isEqual_long(nqueens(2,3),0,1);
	isEqual_long(nqueens(3,4),0,1);
	isEqual_long(nqueens(4,5),0,1);

}

void testes_variados(){
	DESCRIBE("Testes com tamanhos e numero de rainhas variados");

	WHEN("Numero de rainhas eh proximo da dimensao do tabuleiro");
	THEN("Ha menos resultados");

	isEqual_long(nqueens(3,2),990,2);
	isEqual_long(nqueens(3,3),0,2);
	isEqual_long(nqueens(4,3),312936,2);
	isEqual_long(nqueens(5,4),454950820,2);
	isEqual_long(nqueens(6,5),2203265494560,2);
	isEqual_long(nqueens(6,6),32980810590,2); //17247371778

	WHEN("Numero de rainhas eh menor");
	THEN("Ha mais resultados");

	isEqual_long(nqueens(4,2),389946,2);
	isEqual_long(nqueens(5,2),401697908,2);
	isEqual_long(nqueens(5,3),865055776,2);
	isEqual_long(nqueens(6,2),1373360533740,2);
	isEqual_long(nqueens(6,3),6264797809140,2);
}


void teste_grande(){
	DESCRIBE("Teste com tamanho grande de tabuleiro");
	isEqual_long(nqueens(10,5),10234134736855859172U,3);
}

int main(){

	testes_parametros();
	testes_uma_rainha();
	testes_rainhas_mais_que_tabuleiro();
	testes_variados();
	//teste_grande();

	GRADEME();

	if (grade==maxgrade)
		return 0;
	else return grade;
}
