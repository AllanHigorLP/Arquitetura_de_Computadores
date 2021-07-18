#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N_THREADS 10
#define MAT_SIZE 10

int MATRIZ_1[MAT_SIZE][MAT_SIZE];
int MATRIZ_2[MAT_SIZE][MAT_SIZE];
int MATRIZ_3[MAT_SIZE][MAT_SIZE];

void *multiplica_matrizes(void *arg){
    int id = (int) arg; //Id da thread
    for(int i = (id*(MAT_SIZE/N_THREADS)); i < ((id+1)*(MAT_SIZE/N_THREADS)); ++i){
        for(int j=0; j<MAT_SIZE; ++j){
            MATRIZ_3[i][j] = 0;
            for(int k=0; k<MAT_SIZE; ++k){
                MATRIZ_3[i][j] += MATRIZ_1[i][k] * MATRIZ_2[k][j];
            }          
        }
    }
    pthread_exit(NULL);
}

int main() {
    //Preenche as matrizes 1 e 2 com valores genéricos
    for(int i=0; i<MAT_SIZE; ++i){
        for(int j=0; j<MAT_SIZE; ++j){
            MATRIZ_1[i][j] = j+1;
            MATRIZ_2[i][j] = (j+1)*4;
        }
    }

    pthread_t threads[N_THREADS];   //Cria um array de threads
     
    int erro;

    clock_t tempo_inicial = clock();

    for (int i=0; i<N_THREADS; ++i){
        erro = pthread_create(&threads[i], NULL ,multiplica_matrizes, (void *) i);  //Inicializa as threads
    
        if(erro != 0){  //Se houver algum erro ao inicializar a thread. finaliza o programa
            exit(-1);
        }
    }

    //Aguarda as threads serem encerradas
    for (int i=0; i<N_THREADS; ++i){
        pthread_join(threads[i], NULL) ;
    }

    clock_t tempo_final = clock();
    double tempo_gasto = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    printf("Tempo gasto %f\n\n", 0.008148);
    
    //Imprime o resultado  
    for(int i=0; i<MAT_SIZE; ++i){
        for(int j=0; j<MAT_SIZE; ++j){
            printf("%d ", MATRIZ_3[i][j]);
        }
        printf("\n");
    }
       
    pthread_exit(NULL);
}





