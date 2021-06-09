//Name:Pritish Wadhwa
//Roll Number:2019440
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

// n: number of philosophers
int n;

// structure for the custom semaphore
struct my_semaphore
{
    pthread_mutex_t lock;
    int value;
} pickFork, bowl1, bowl2, *forks;

// my_semaphore's init function
int my_semaphore_init(struct my_semaphore *sem, int count)
{
    if (sem == NULL)
    {
        return 1;
    }
    sem->value = count;
    int ret = pthread_mutex_init(&(sem->lock), NULL);
    if (ret != 0)
    {
        perror("pthread_mutex_init");
    }
    return 0;
}

// my_semaphore's wait function
int wait(struct my_semaphore *sem)
{
    if (sem == NULL)
    {
        return 1;
    }
    int ret = pthread_mutex_trylock(&(sem->lock));
    if (ret < 0)
    {
        perror("pthread_mutex_trylock");
    }
    while (sem->value == 0)
    {
        ret = pthread_mutex_unlock(&(sem->lock));
        if (ret != 0)
        {
            perror("pthread_mutex_unlock");
            return ret;
        }
        return 1;
    }
    sem->value--;
    ret = pthread_mutex_unlock(&(sem->lock));
    if (ret != 0)
    {
        perror("pthread_mutex_unlock");
    }
    return 0;
}

// my_semaphore's signal function
int signal(struct my_semaphore *sem)
{
    if (sem == NULL)
    {
        return 1;
    }
    int ret = pthread_mutex_lock(&(sem->lock));
    if (ret != 0)
    {
        perror("pthread_mutex_lock");
        return ret;
    }
    sem->value++;
    ret = pthread_mutex_unlock(&(sem->lock));
    if (ret != 0)
    {
        perror("pthread_mutex_unlock");
        return ret;
    }
    return 0;
}

// my_semaphore's printValue function for debugging
void printSignal(int printValue)
{
    if (printValue > n - 1 || printValue < 0)
    {
        printf("Error in semaphore with the val %d", printValue);
    }
}

// main function where the dining philosopher's problem is solved
void *funcPhilosopher(void *x)
{
    int idx = *((int *)x);
    while (1)
    {
        int val;
        int temp;
        sleep(0);
        temp = wait(&pickFork);
        while (temp)
        {
            temp = wait(&pickFork);
        }
        printSignal(pickFork.value);
        temp = wait(&forks[idx]);
        while (temp)
        {
            temp = wait(&forks[idx]);
        }
        printSignal(forks[idx].value);
        temp = wait(&forks[(idx + 1) % n]);
        while (temp)
        {
            temp = wait(&forks[(idx + 1) % n]);
        }
        printSignal(forks[(idx + 1) % n].value);
        temp = wait(&bowl1);
        while (temp)
        {
            temp = wait(&bowl1);
        }
        printSignal(bowl1.value);
        temp = wait(&bowl2);
        while (temp)
        {
            temp = wait(&bowl2);
        }
        printSignal(bowl2.value);
        printf("Philosopher %d eats using fork number %d and fork number %d.\n", idx, idx, (idx + 1) % n);
        sleep(0);
        signal(&bowl2);
        printSignal(bowl2.value);
        signal(&bowl1);
        printSignal(bowl1.value);
        signal(&forks[(idx + 1) % n]);
        printSignal(forks[(idx + 1) % n].value);
        signal(&forks[idx]);
        printSignal(forks[idx].value);
        signal(&pickFork);
        printSignal(pickFork.value);
    }
    pthread_exit(NULL);
}

int main(void)
{
    printf("Enter the number of philsophers: ");
    scanf("%d", &n);
    pthread_t philosophers[n];
    my_semaphore_init(&pickFork, n - 1);
    forks = (struct my_semaphore *)malloc(n * sizeof(struct my_semaphore));
    // creating semaphores for bowls
    my_semaphore_init(&bowl1, 1);
    my_semaphore_init(&bowl2, 1);
    // creating semaphores for forks
    for (int i = 0; i < n; i++)
    {
        my_semaphore_init(&forks[i], 1);
    }
    for (int i = 0; i < n; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        int res = pthread_create(&philosophers[i], NULL, funcPhilosopher, (void *)arg);
        if (res != 0)
        {
            perror("pthread_create");
        }
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}