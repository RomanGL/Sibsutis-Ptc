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

int main()
{
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, thread_func, NULL);
    if (rc != 0) {
        fprintf(stderr, "Can't create thread\n");
        exit(EXIT_FAILURE);
    }
    printf("Hello from master thread %u\n", (unsigned int)pthread_self());
    // Мастер-поток ожидает завершение дочернего потока
    pthread_join(tid, NULL);
    return 0;
}
