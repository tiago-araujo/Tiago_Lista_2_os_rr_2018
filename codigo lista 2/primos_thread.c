/**
    Tiago Araújo Nunes de Lima
    Objetivo: Imprimir os números primos de 0 a 99999 utilizando threads,
    separando blocos de 1000 para cada uma. 
        Ex:

    [0..999][1000..1999][2000..2999][3000..3999][4000..4999]...
    thread1     thread2     thread3     thread4     thread5 ...
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define TAM_MAXIMO 100000  
#define BLOCO 1000  // Macro bloco linha
#define NTHREADS TAM_MAXIMO/BLOCO      // Numero de threads
int b = 0;                  // Determina o inicio de cada bloco na thread
pthread_mutex_t  mutex_bloco; // Controle dos blocos

/*
    ehPrimo(): verificar se um numero é primo.
*/
int ehPrimo(int num) {
    if (num == 2)
        return 1;
    if ((num % 2) == 0 || num < 2)
        return 0;
    int i = 3, raiz = (int)sqrt(num);      
    while (i <= raiz){
        if ((num % i) == 0)
            return 0;
        i+=2;
    }
    return 1;
}

void *imprimePrimos(void* arg) {
    int tid = *(int*)arg;
    while (1) {
        
        int limBloco = 0; //limite do bloco
        
        // Controla a região critica que atribui os blocos a thread.
        pthread_mutex_lock(&mutex_bloco);
        b += BLOCO;
        limBloco = b; 
        pthread_mutex_unlock(&mutex_bloco);
        // Se passar do tamanho maximo sai do loop
        if (limBloco > TAM_MAXIMO)
            return(NULL);

        // Começa em (limBloco - BLOCO) e termina em limBloco
        for (int i = (limBloco - BLOCO); i < limBloco; i++) {
            if (ehPrimo(i)) {
                printf("%i\n", i);
            }
        }
    }
    return(NULL);
}


int main() {

    pthread_t threads[NTHREADS];
    int i = 0;

    pthread_mutex_init(&mutex_bloco, NULL);

    for (i = 0; i < NTHREADS; i++){
        pthread_create(&(threads[i]), NULL, imprimePrimos, &i);
    }

    for (i = 0; i < NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
}