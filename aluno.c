#include "nqueens.h"
#include "simplegrade.h"


void teste1(){

    DESCRIBE("Teste com entradas invalidas");

    WHEN("Tenho um tabuleiro 1x1 e tenho duas rainhas");
    THEN("Deve retornar zero");
    isEqual(nqueens(1,2),0,1);

    WHEN("Tenho um tabuleiro 2x2 e tenho mais do que uma rainha");
    THEN("Deve retornar zero");
    isEqual(nqueens(2,2),0,1);
     
    WHEN("Tenho um tabuleiro 3x3 e tenho três rainhas");
    THEN("Deve retornar zero");
    isEqual(nqueens(3,3),0,1);

    WHEN("Tenho um tabuleiro 2x2 e tenho cinco rainhas");
    THEN("Deve retornar zero");
    isEqual(nqueens(2,4),0,1);
    
}

void teste2(){

     DESCRIBE("Teste com entradas validas");

     WHEN("Tenho um tabuleiro 1x1 e uma rainha");
     THEN("Deve retornar 1");
     isEqual(nqueens(1,1),1,1);
   
     WHEN("Tenho um tabuleiro 2x2 e tenho uma rainha");
     THEN("Deve retornar 15");
     isEqual(nqueens(2,1),15,1);
     
     WHEN("Tenho um tabuleiro 3x3 e tenho duas rainhas");
     THEN("Deve retornar 990");
     isEqual(nqueens(3,2),990,1); 
     
     WHEN("Tenho um tabuleiro 4x4 e tenho quatro rainhas");
     THEN("Deve retornar 27030");
     isEqual(nqueens(4,4),27030,1);    

}


void teste3(){

     WHEN("Tenho um tabuleiro 4x4 e tenho duas rainhas");
     THEN("Deve retornar 389946");
     isEqual(nqueens(4,2),389946,1); 

     WHEN("Tenho um tabuleiro 5x5 e tenho cinco rainhas");
     THEN("Deve retornar 67108862");
     isEqual(nqueens(5,5),67108862,1);

     WHEN("Tenho um tabuleiro 7x7 e tenho seis rainhas");
     THEN("Deve retornar 59490566");
     isEqual(nqueens(7,6),59490566,1);

}


int main(){
		
    DESCRIBE("Arquivo de testes do trabalho 1");
    
    teste1();
    teste2();
    teste3();


    GRADEME();
    if(grade == maxgrade)
        return 0;
    else
        return grade;
}
