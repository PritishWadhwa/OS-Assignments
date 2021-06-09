#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

//to handle the deadlock situation, I have enforced that the philosophers can eat only when their neighbours are not eating
//state == 0 when eating
//state == 1 when ready to eat
//state == 2 when thinking
#define LEFT (philo + 4) % 5
#define RIGHT (philo + 1) % 5
sem_t mutex;
int state[5];
sem_t semaphores[5];

void test(int philo)
{
    if (state[philo] == 1 && state[LEFT] != 0 && state[RIGHT] != 0)
    {
        state[philo] = 0;
        printf("P%d recieves F%d, F%d\n", philo + 1, LEFT + 1, philo + 1);
        sem_post(&semaphores[philo]);
    }
}

void take_fork(int philo)
{
    sem_wait(&mutex);
    state[philo] = 1;
    test(philo);
    sem_post(&mutex);
    sem_wait(&semaphores[philo]);
}

void put_fork(int philo)
{
    sem_wait(&mutex);
    state[philo] = 2;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philospher(void *num)
{
    int *id = num;
    take_fork(*id);
    put_fork(*id);
    pthread_exit(NULL);
}

int main(void)
{
    printf("Hello Workd %s\n", __FILE__);
    pthread_t thread[5];
    sem_init(&mutex, 0, 1);
    int philosophers[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++)
    {
        sem_init(&semaphores[i], 0, 0);
    }
    for (int i = 0; i < 5; i++)
    {
        int errCheck = pthread_create(&thread[i], NULL, philospher, &philosophers[i]);
        if (errCheck != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread[i], NULL);
    }
    return 0;
}