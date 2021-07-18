
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
static long num_steps = 100000; double step;
#define NUM_THREADS 4
#define N 4

int MATRIZ_1[N][N];
int MATRIZ_2[N][N];
int MATRIZ_3[N][N];


void mult(){
    int i, j, k;
    for(j=0; j<N; j++){
    	MATRIZ_3[i][j]=0;
    	for (k=0; k<N; k++){
    	     MATRIZ_3[i][j] += MATRIZ_1[i][k]*MATRIZ_2[k][j];
    	}
    }
}


int main () {
    int i, nthreads; double pi, sum[NUM_THREADS];
    step = 1.0/(double) num_steps;
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i=id, sum[id]=0.0; i<num_steps; i=i+nthrds) {
            mult();
        }
    }

    for(i=0, pi=0.0; i<nthreads; i++){
        pi += sum[i] * step;
    }
    printf("%f",pi);
    return 0;
}
