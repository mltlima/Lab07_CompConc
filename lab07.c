/**
 * Miguel Lima Tavares
 * 119161571
 * Lab 07
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS 4

/* Variaveis globais */
int x = 0;
sem_t condt1, condt2;

//Thread A
void *A (void *t) {

    sem_wait(&condt2);
    printf("Volte Sempre!\n");
 
    pthread_exit(NULL);
}


//Thread B
void *B (void *t) {
    
    sem_wait(&condt1);
    x++;
    printf("Fique a vontade.\n");

    sem_post(&condt1);

    if (x == 3){
        sem_post(&condt2); 
    } 
    
    
    pthread_exit(NULL);
}

//Thread C
void *C (void *t) {
    

    sem_wait(&condt1);
    x++;
    printf("Sente-se por favor.\n"); 

    sem_post(&condt1);

    if (x == 3){
        sem_post(&condt2);
    } 
 
    pthread_exit(NULL);
}

//Thread D
void *D (void *t) {

    printf("Seja bem-vido!\n"); 
    x++;
    sem_post(&condt1);
    
    pthread_exit(NULL);
}



//----------------------------------------
int main(void) {

    pthread_t threads[NTHREADS];

    //inicia os semaforos
    sem_init(&condt1, 0, 0);
    sem_init(&condt2, 0, 0);

    //Threads
    pthread_create(&threads[0], NULL, A, NULL);
    pthread_create(&threads[1], NULL, B, NULL);
    pthread_create(&threads[2], NULL, C, NULL);
    pthread_create(&threads[3], NULL, D, NULL);

    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i], NULL);
    }

    /* Desaloca variaveis e termina */
    sem_destroy(&condt1);
    sem_destroy(&condt2);
    return 0;

}
