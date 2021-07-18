#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_THREADS 50
#define MAT_SIZE 100

int MATRIZ_1[MAT_SIZE][MAT_SIZE];
int MATRIZ_2[MAT_SIZE][MAT_SIZE];
int MATRIZ_3[MAT_SIZE][MAT_SIZE];


void multiplica_matrizes(int id){
    int threadID = id;  //ID da Thread
    for(int i = (threadID*(MAT_SIZE/N_THREADS)); i< ((threadID+1)*(MAT_SIZE/N_THREADS)); i++){
    	for(int j=0; j<MAT_SIZE; j++){
    	     MATRIZ_3[i][j]=0;
    	     for (int k=0; k<MAT_SIZE; k++){
    	     	MATRIZ_3[i][j] += MATRIZ_1[i][k]*MATRIZ_2[k][j];
    	     }
    	}
    }
}


int main () {
    int i,j, nthreads;
    //Preenche as matrizes 1 e 2 com valores genéricos
    for(i=0; i<MAT_SIZE; i++){
    	for(j=0; j<MAT_SIZE; j++){
    	     MATRIZ_1[i][j] = j+1;
    	     MATRIZ_2[i][j] = j*2;
    	}
    }
  
    clock_t begin = clock();     //inicia a contagem de tempo 
    //entra na zona paralela
    #pragma omp parallel num_threads(N_THREADS)
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i=id; i<nthrds; i=i+nthrds){
            multiplica_matrizes(i); //cada thread multiplica uma parte 
            			     // da matriz
        }
    }  
    //sai da zona paralela
    clock_t end = clock();    //termina a contagem de tempo
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    //imprime a matriz
    for(i=0; i<MAT_SIZE; i++){
    	for(j=0; j<MAT_SIZE; j++){
    	     printf("%d ", MATRIZ_3[i][j]);
    	}
    	printf("\n");
    }
    //printa o tempo utilizado para a multiplicacao
    printf("%f",time_spent);
    
    return 0;
}
