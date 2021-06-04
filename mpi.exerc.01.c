#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

/*
1 - Fazer um programa em MPI que utilize 3 processos, os processos 1 e 2 devem
enviar um valor inteiro para o processo 0. O processo 0 deve efetuar as 4 operações
básicas com os inteiros recebidos (+,-.*,/), após isso deve imprimir os resultados.
*/

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag=0;
	float num1, num2, soma, subtracao, mult, divisao;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    	if (meu_rank == 0) {
       		MPI_Recv(&num1, 1, MPI_REAL, 1, tag, MPI_COMM_WORLD, &status);
    		MPI_Recv(&num2, 1, MPI_REAL, 2, tag, MPI_COMM_WORLD, &status);
        	soma = num1 + num2;
        	subtracao = num1 - num2;
			mult = num1 * num2;
			divisao = num1 / num2
        	printf("A soma e: %f\n\n\n", soma);
        	printf("A diferenca e: %f\n\n\n", subtracao);
        	printf("O produto e: %f\n\n\n", mult);
			printf("O quociente e: %f\n\n\n", divisao);
	}
	else if (meu_rank == 1) {
		num1 = 6;
		MPI_Send(&num1, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}
	else {
		num2 = 9;
		MPI_Send(&num2, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}	
	MPI_Finalize( );
}
