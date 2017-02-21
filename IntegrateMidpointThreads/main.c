#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *integrate(void *arg);

const double a = -4.0;
const double b = 4.0;
const int n = 10000000;

// Глобальная сумма
double s = 0.0;

struct thread_data {
    pthread_t tid;
    int threadno;   // Порядковый номер потока 0, 1, 2, …
    int nthreads;   // Количество потоков
};

int main(int argc, char **argv)
{
    int nthreads = (argc > 1) ? atoi(argv[1]) : 2;
    printf("Numerical integration (%d threads): [%f, %f], n = %d\n", nthreads, a, b, n);
    struct thread_data *tdata = malloc(sizeof(*tdata) * nthreads);
    if (tdata == NULL) {
        fprintf(stderr, "No enough memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < nthreads; i++) {    // Запуск nthreads – 1 потоков!
        tdata[i].threadno = i;
        tdata[i].nthreads = nthreads;
        if (pthread_create(&tdata[i].tid, NULL, integrate, &tdata[i]) != 0) {
            fprintf(stderr, "Can't create thread\n");
            exit(EXIT_FAILURE);
        }
    }
    tdata[0].threadno = 0;
    tdata[0].nthreads = nthreads;
    integrate(&tdata[0]);   // Мастер-поток участвует в вычислениях, всего nthreads потоков

    for (int i = 1; i < nthreads; i++)
        pthread_join(tdata[i].tid, NULL);
    free(tdata);

    printf("Result Pi: %.12f\n", s * s);
    return 0;
}



double func(double x) {
    return exp(-x * x);
}

void *integrate(void *arg)
{
    struct thread_data *p = (struct thread_data *)arg;
    double h = (b - a) / n;

    int points_per_proc = n / p->nthreads;
    int lb = p->threadno * points_per_proc;
    int ub = (p->threadno == p->nthreads - 1) ? (n - 1) : (lb + points_per_proc - 1);

    for (int i = lb; i < ub; i++)   // Вся суть распараллеливания – цикл распределен между потоками
        s += func(a + h * (i + 0.5));

    s *= h;     // Обновление глобальной суммы
    return NULL;
}