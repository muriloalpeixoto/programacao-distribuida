/*
5 - Desenvolva uma aplicação paralela em MPI para multiplicar duas matrizes 3x3.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag=0;
	int i, j, k;
	float matriz1[3][3], matriz2[3][3];
	float resultado[3][3];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
    
    for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			matriz1[i][j] = i + j;
			matriz2[i][j] = i - j;
		}
	}

	if (meu_rank == 1) {
        for (i = 0; i < 3; i++) {
        	for (j = 0; j < 3; j++) {
            	resultado[i][j] = 0;
            	for (k = 0; k < 3; k++) {
                	resultado[i][j] += matriz1[i][k] * matriz2[k][j];
        		}
			}
		}
        MPI_Send(&resultado, 1, MPI_REAL, 0, tag, MPI_COMM_WORLD);
	}
	
    else if (meu_rank == 0) {
        MPI_Recv(&resultado, 1, MPI_REAL, 1, tag, origem, MPI_COMM_WORLD, &status);
        printf("O resultado da multiplicação de todos os elementos da matriz e %f\n", somat);
		for (i = 0; i < 3; i++) {
        	for (j = 0; j < 3; j++) {
            	printf("%f", resultado[i][j]);
        	}
        printf("\n");
    	}
	}

    MPI_Finalize( );
}

