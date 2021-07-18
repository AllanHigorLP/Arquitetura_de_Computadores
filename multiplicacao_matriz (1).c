// Autor: Allan Higor Liborio Pardinho

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define tamanho_matriz 30    // ordem das matrizes
#define quant_threads 30     // quant de threads usadas

#define valor_m1 5  //valores usados para preencher as matrizes
#define valor_m2 10 //

int m1[tamanho_matriz][tamanho_matriz];
int m2[tamanho_matriz][tamanho_matriz];
int resultado[tamanho_matriz][tamanho_matriz];

void *mult_matriz(void *id_thread);

int main() {
    pthread_t threads[quant_threads];
    for(int i=0; i<tamanho_matriz; i++){
        for(int j=0; j<tamanho_matriz; j++){
            m1[i][j] = valor_m1;
            m2[i][j] = valor_m2;
        }
    }
    clock_t begin = clock();    //MARCA O TEMPO DE INICIO DA EXECUÇÃO
    for (int i=0; i<quant_threads; i++){
        pthread_create(&threads[i], NULL, mult_matriz, (void *) i);
    }

    for (int i=0; i<quant_threads; i++){
        pthread_join(threads[i], NULL) ;
    }
    clock_t end = clock();      //MARCA O TEMPO DE FINALIZAÇÃO DA EXECUÇÃO
    printf("TEMPO DE EXECUÇÃO: %f\n", (double)(end-begin) / CLOCKS_PER_SEC);

    for(int i=0; i<tamanho_matriz; i++){        // Printa os valores da matriz 1
        for(int j=0; j<tamanho_matriz; j++){
            printf("%d |", m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
 
    for(int i=0; i<tamanho_matriz; i++){        // Printa os valores da matriz 2
        for(int j=0; j<tamanho_matriz; j++){
            printf("%d |", m2[i][j]);
        }
        printf("\n");
    }  
    printf("\n");

    for(int i=0; i<tamanho_matriz; i++){        // Printa os valores da matriz resultado
        for(int j=0; j<tamanho_matriz; j++){
            printf("%d |", resultado[i][j]);
        }
        printf("\n");
    }
}

void *mult_matriz(void *id_thread){
    int id_thread_int = (int) id_thread;
    int limite_inicial = id_thread_int*(tamanho_matriz/quant_threads);      // calcula os limites que cada thread
    int limite_final = (id_thread_int+1)*(tamanho_matriz / quant_threads);  // deve calcular das matrizes

    for(int i = limite_inicial; i < limite_final; i++){
        for(int j=0; j<tamanho_matriz; j++){
            resultado[i][j] = 0;
            for(int k=0; k<tamanho_matriz; k++){
                resultado[i][j] += m1[i][k] * m2[k][j];
            }          
        }
    }
}