/*
3 - Utilizando MPI em C, faça um programa de soma
de matrizes 3x3, onde cada um dos 3 processos criados
fará a soma de uma das linha da matriz e enviará para o
processo 0(ZERO) fazer a impressão. Para imprimir em tela
o resultado correto deve-se imprimir os processor em ordem de rank(1,2,3). 
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag=0;
	int i, j;
	float matriz[3][3];
	float soma1, soma2, soma3, somat;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			matriz[i][j] = i + j;
		}
	}

	if (meu_rank == 1) {
        soma1 = matriz[1][1] + matriz[1][2] + matriz[1][3];
        MPI_Send(&soma1, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}
	else if (meu_rank == 2) {
        soma2 = matriz[2][1] + matriz[2][2] + matriz[2][3];
        MPI_Send(&soma2, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}
	else if (meu_rank == 3) {
        soma3 = matriz[3][1] + matriz[3][2] + matriz[3][3];
        MPI_Send(&soma3, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}
	
    else if (meu_rank == 0) {
        MPI_Recv(&soma1, 1, MPI_REAL, 1, tag, origem, MPI_COMM_WORLD, &status);
        MPI_Recv(&soma2, 1, MPI_REAL, 2, tag, origem, MPI_COMM_WORLD, &status);
        MPI_Recv(&soma3, 1, MPI_REAL, 3, tag, origem, MPI_COMM_WORLD, &status);
        printf("O resultado da soma dos elementos da linha 1 da matriz e %f\n", soma1);
        printf("O resultado da soma dos elementos da linha 2 da matriz e %f\n", soma2);
        printf("O resultado da soma dos elementos da linha 3 da matriz e %f\n", soma3);
        somat = soma1 + soma2 + soma3;
        printf("O resultado da soma de todos os elementos da matriz e %f\n", somat);
    }
    
    MPI_Finalize( );
}

