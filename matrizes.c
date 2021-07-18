#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4
#define N 4

int MATRIZ_1[N][N];
int MATRIZ_2[N][N];
int MATRIZ_3[N][N];

void *multiplica_matrizes(void *id){
    int threadId = ( int)id;
    int i,j,k;
    for (i= ( threadId*(N/MAX_THREADS)); i< ((threadId+1)*(N/MAX_THREADS) );i++){
        for (j=0; j<N; j++){
                MATRIZ_3[i][j]=0;
                for (k=0;k<N;k++)
                    MATRIZ_3 [i][j]+=MATRIZ_1[i][k]*MATRIZ_2[k][j] ;
        }
    }
    pthread_exit(NULL);
}

int main() {
    //Preenche as matrizes 1 e 2
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            MATRIZ_1[i][j] = j+1;
            MATRIZ_2[i][j] = j*2;
        }
    }

    pthread_t threads[MAX_THREADS] ;
     
    int erro;

    for (int i=0; i<MAX_THREADS; i++){
        erro = pthread_create(&threads[i], NULL ,multiplica_matrizes, (void *) i) ;
    }
                
    if (erro)
        exit(-1);

    // Aguarda as threads serem encerradas
    for (int i=0; i<MAX_THREADS; i++){
        pthread_join (threads[i], NULL) ;
    }
            
    //Imprime o resultado  
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            printf("%d ", MATRIZ_3[i][j]);
        }
        printf("\n");
    }
       
    pthread_exit(NULL);
}
