#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int read = 0;
sem_t servQ;

void *writer(void *wno)
{
    key_t key = ftok("q5", 65);
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget error");
        exit(1);
    }
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    sem_wait(&wrt);
    *cnt = 'b';
    printf("Writer %d modified cnt to %d\n", (*((int *)wno)), *cnt);
    sem_post(&wrt);
    pthread_exit(NULL);
}

void *reader(void *rno)
{
    key_t key = ftok("q5", 65);
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget error");
        exit(1);
    }
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    pthread_mutex_lock(&mutex);
    read++;
    if (read == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: read cnt as %d\n", *((int *)rno), *cnt);
    pthread_mutex_lock(&mutex);
    read--;
    if (read == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(void)
{
    printf("Hello Workd %s\n", __FILE__);

    key_t key = ftok("q5", 65);
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget error");
        exit(1);
    }
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    *cnt = 'a';
    pthread_t read[15];
    pthread_t write;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    int a[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int temp;
    for (int i = 0; i < 15; i++)
    {
        temp = pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
        if (temp < 0)
        {
            perror("pthread create error");
            return 1;
        }
    }
    temp = pthread_create(&write, NULL, (void *)writer, (void *)&a[0]);
    if (temp < 0)
    {
        perror("pthread create error");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        temp = pthread_join(read[i], NULL);
        if (temp < 0)
        {
            perror("pthread join error");
            return 1;
        }
    }
    temp = pthread_join(write, NULL);
    if (temp < 0)
    {
        perror("pthread join error");
        return 1;
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    shmdt(cnt);
    return 0;
}
