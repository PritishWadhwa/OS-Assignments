#include <stdio.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(void)
{
    printf("Hello Workd %s\n", __FILE__);

    sem_t *mutex_alpha, *mutex_num;
    sem_t *alpha_write, *num_write, *alpha_read, *num_read;
    int flag = O_CREAT;
    int flag2 = O_CREAT | O_RDWR;
    mutex_alpha = sem_open("MUT_A", flag, 0666, 1);
    if (mutex_alpha < 0)
    {
        perror("sem open error");
        return 1;
    }
    mutex_num = sem_open("MUT_N", flag, 0666, 1);
    if (mutex_num < 0)
    {
        perror("sem open error");
        return 1;
    }
    alpha_write = sem_open("ALPHA_WRITE", flag, 0666, 0);
    if (alpha_write < 0)
    {
        perror("sem open error");
        return 1;
    }
    alpha_read = sem_open("ALPHA_READ", flag, 0666, 1);
    if (alpha_read < 0)
    {
        perror("sem open error");
        return 1;
    }
    num_write = sem_open("NUM_WRITE", flag, 0666, 0);
    if (num_write < 0)
    {
        perror("sem open error");
        return 1;
    }
    num_read = sem_open("NUM_READ", flag, 0666, 1);
    if (num_read < 0)
    {
        perror("sem open error");
        return 1;
    }
    if (num_read == SEM_FAILED)
    {
        perror("SEM_FAILED");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        int shmfd = shm_open("/shm", flag2, 0666);
        if (shmfd < 0)
        {
            perror("shm open error");
            return 1;
        }
        int err = ftruncate(shmfd, 1024);
        if (err < 0)
        {
            perror("ftruncate error");
            return 1;
        }
        char *buf = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
        if (buf == MAP_FAILED)
        {
            perror("mmap error");
            return 1;
        }
        char localbuf[1024];
        strcpy(localbuf, "");
        while (strcmp(localbuf, "\n\n") != 0)
        {
            int locerr;
            locerr = sem_wait(alpha_write);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            locerr = sem_wait(mutex_alpha);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            strcpy(localbuf, buf);
            printf("%s ", localbuf);
            locerr = sem_post(mutex_alpha);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
            locerr = sem_post(alpha_read);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
        }
        int shmfdnum = shm_open("/shmnum", flag2, 0666);
        if (shmfdnum < 0)
        {
            perror("shm open error");
            return 1;
        }
        err = ftruncate(shmfdnum, sizeof(int));
        if (err < 0)
        {
            perror("ftruncate error");
            return 1;
        }
        int *bufnum = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfdnum, 0);
        if (bufnum == MAP_FAILED)
        {
            perror("mmap error");
            return 1;
        }
        int localnum = 0;
        while (localnum != -1)
        {
            int locerr;
            locerr = sem_wait(num_write);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            locerr = sem_wait(mutex_num);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            localnum = *bufnum;
            fflush(stdout);
            printf("%d ", localnum);
            locerr = sem_post(mutex_num);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
            locerr = sem_post(num_read);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
        }
        err = sem_unlink("MUT_N");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = sem_unlink("MUT_A");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = sem_unlink("ALPHA_WRITE");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = sem_unlink("ALPHA_READ");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = sem_unlink("NUM_READ");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = sem_unlink("NUM_WRITE");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = shm_unlink("/shm");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        err = shm_unlink("/shmnum");
        if (err < 0)
        {
            perror("sem unlink error");
            return 1;
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        int shmfd = shm_open("/shm", flag2, 0666);
        if (shmfd < 0)
        {
            perror("shm open error");
            return 1;
        }
        int err = ftruncate(shmfd, 1024);
        if (err < 0)
        {
            perror("ftruncate error");
            return 1;
        }
        char *buf = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
        if (buf == MAP_FAILED)
        {
            perror("mmap error");
            return 1;
        }
        char listbuf[10][1024];
        for (int i = 1; i <= 10; i++)
        {
            sprintf(listbuf[i - 1], "word number %d\n", i);
        }
        for (int i = 0; i < 10; i++)
        {
            int locerr;
            locerr = sem_wait(alpha_read);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            locerr = sem_wait(mutex_alpha);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            strcpy(buf, listbuf[i]);
            locerr = sem_post(mutex_alpha);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
            locerr = sem_post(alpha_write);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
        }
        err = sem_wait(alpha_read);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        err = sem_wait(mutex_alpha);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        strcpy(buf, "\n\n");
        err = sem_post(mutex_alpha);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        err = sem_post(alpha_write);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        int shmfdnum = shm_open("/shmnum", O_CREAT | O_RDWR, 0666);
        if (shmfdnum < 0)
        {
            perror("shm open error");
            return 1;
        }
        err = ftruncate(shmfdnum, sizeof(int));
        if (err < 0)
        {
            perror("ftruncate error");
            return 1;
        }
        int *bufnum = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfdnum, 0);
        if (bufnum == MAP_FAILED)
        {
            perror("mmap error");
            return 1;
        }
        for (int i = 0; i < 10; i++)
        {
            int locerr;
            locerr = sem_wait(num_read);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            locerr = sem_wait(mutex_num);
            if (locerr < 0)
            {
                perror("sem wait error");
                return 1;
            }
            *bufnum = i + 100;
            locerr = sem_post(mutex_num);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }

            locerr = sem_post(num_write);
            if (locerr < 0)
            {
                perror("sem post error");
                return 1;
            }
        }
        err = sem_wait(num_read);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        err = sem_wait(mutex_num);
        if (err < 0)
        {
            perror("sem wait error");
            return 1;
        }
        *bufnum = -1;
        err = sem_post(mutex_num);
        if (err < 0)
        {
            perror("sem post error");
            return 1;
        }
        err = sem_post(num_write);
        if (err < 0)
        {
            perror("sem post error");
            return 1;
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("FORK");
        return EXIT_FAILURE;
    }
    return 0;
}