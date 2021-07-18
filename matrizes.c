
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
static long num_steps = 100000; double step;
#define NUM_THREADS 2
#define N 4

int MATRIZ_1[N][N];
int MATRIZ_2[N][N];
int MATRIZ_3[N][N];


void mult(int id){
    int threadID = id;
    int i, j, k;
    for(i = (threadID*(N/NUM_THREADS)); i< ((threadID+1)*(N/NUM_THREADS)); i++){
    	for(j=0; j<N; j++){
    	     MATRIZ_3[i][j]=0;
    	     for (k=0; k<N; k++){
    	     	MATRIZ_3[i][j] += MATRIZ_1[i][k]*MATRIZ_2[k][j];
    	     }
    	}
     }
}


int main () {
    int i,j,n,k, nthreads; double pi, sum[NUM_THREADS];
    step = 1.0/(double) num_steps;
    
    for(i=0; i<N; i++){
    	for(j=0; j<N; j++){
    	     MATRIZ_1[i][j] = j+1;
    	     MATRIZ_2[i][j] = j*2;
    	}
    }
       
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i=id, sum[id]=0.0; i<nthrds; i=i+nthrds){
            printf("%d --- \n", i);
            mult(i);
        }
    }
    for(i=0; i<N; i++){
    	for(j=0; j<N; j++){
    	     printf("%d ", MATRIZ_1[i][j]);
    	}
    	printf("\n");
    }
    
    
    for(i=0; i<N; i++){
    	for(j=0; j<N; j++){
    	     printf("%d ", MATRIZ_3[i][j]);
    	}
    	printf("\n");
    }
    
    return 0;
}




























