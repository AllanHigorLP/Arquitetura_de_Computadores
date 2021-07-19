// Autor: Allan Higor Liborio Pardinho
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define quant_threads 100
#define tamanho_matriz 1000

int m1[tamanho_matriz][tamanho_matriz];
int m2[tamanho_matriz][tamanho_matriz];
int resultado[tamanho_matriz][tamanho_matriz];


#define valor_m1 5  //valores usados para preencher as matrizes
#define valor_m2 10 //


int main () {
    int nthreads;
    //PREENCHENDO AS MATRIZES
    for(int i = 0; i<tamanho_matriz; i++){
    	for(int j =0 ; j<tamanho_matriz; j++){
    	     m1[i][j] = valor_m1;
    	     m2[i][j] = valor_m2;
    	}
    }
       
    clock_t begin = clock(); // MARCA O TEMPO DE INICIO DA EXECUÇÃO
    //ENTRA NA ZONA PARALELA
    #pragma omp parallel num_threads(quant_threads)
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        
        //FOR QUE SEPARA AS MULTIPLICACOES POR THREADS
        for (i=id; i<nthrds; i=i+nthrds){
           //MULTIPLICANDO AS MATRIZES  
    	   for(int i = (id*(tamanho_matriz/quant_threads)); i< ((id+1)*(tamanho_matriz/quant_threads)); i++){
    	       for(int j=0; j<tamanho_matriz; j++){
    	       resultado[i][j]=0;
    	           for (int k=0; k<tamanho_matriz; k++){
    	     	   resultado[i][j] += m1[i][k]*m2[k][j];
    	           }
    	       }
           }
        }
    }  
    //SAI DA ZONA PARALELA
    clock_t end = clock(); //MARCA O TEMPO DE FINALIZAÇÃO DA EXECUÇÃO
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // Printa os valores da matriz resultado 
    for(int i=0; i<tamanho_matriz; i++){        
          for(int j=0; j<tamanho_matriz; j++){
              printf("%d |", resultado[i][j]);
          }
          printf("\n");
    } 
    
    printf("%f",time_spent);
    
    return 0;
}
