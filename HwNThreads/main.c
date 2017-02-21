#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg)
{
    // Код дочернего потока
    pthread_t tid = pthread_self();
    printf("Hello from slave thread %u\n", (unsigned int)tid);
    sleep(5);
    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads = argc > 1 ? atoi(argv[1]) : 4;
    pthread_t *tids = malloc(sizeof(*tids) * nthreads);
    if (tids == NULL) {
        fprintf(stderr, "No enough memory\n");
        exit(EXIT_FAILURE);
    }
    printf("Launching %d threads\n", nthreads);
    for (int i = 0; i < nthreads; i++) {
        if (pthread_create(&tids[i], NULL, thread_func, NULL) != 0) {
            fprintf(stderr, "Can't create thread\n");
            exit(EXIT_FAILURE);
        }
    }
    // Now we have nthreads + 1 master thread
    printf("Hello from master thread %u\n",
           (unsigned int)pthread_self());
    for (int i = 0; i < nthreads; i++)
        pthread_join(tids[i], NULL);
    free(tids);
    return 0;
}