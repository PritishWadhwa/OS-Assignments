/*********************************************************************************
 * Name:        Pritish Wadhwa                                                   *
 * Section:     B                                                                *
 * Roll NUmber: 2019440                                                          *
 ********************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>

extern int errno;

void processData(char *section[400], int studentId[400], int marks[4][400])
{
    int fd = open("file.csv", O_RDONLY | O_EXCL);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    char *c = (char *)calloc(6800, sizeof(char));
    char *data[401];
    int sz = read(fd, c, 6800);
    if (sz < 0)
    {
        perror("read");
        return;
    }
    char *token = strtok(c, "\n");
    int ctr = 0;
    int itr = 0;
    while (token != NULL)
    {
        data[itr++] = token;
        token = strtok(NULL, "\n");
        ctr++;
    }
    for (int i = 0; i < 400; i++)
    {
        token = strtok(data[i + 1], ",");
        studentId[i] = atoi(token);
        token = strtok(NULL, ",");
        section[i] = token;
        token = strtok(NULL, ",");
        marks[0][i] = atoi(token);
        token = strtok(NULL, ",");
        marks[1][i] = atoi(token);
        token = strtok(NULL, ",");
        marks[2][i] = atoi(token);
        token = strtok(NULL, ",");
        marks[3][i] = atoi(token);
    }
    if (close(fd) < 0)
    {
        perror("close");
        return;
    }
}

void printToScreen(char *str)
{
    size_t w = write(1, str, strlen(str));
    if (w < 0)
    {
        if (errno != EINTR)
        {
            perror("write");
            return;
        }
    }
}

int main()
{
    int studentId[400];
    char *section[400];
    int marks[4][400];
    pid_t id;
    int stat;
    int ctr = 1;
    double avg = 0;
    char str[1000000];
    if ((id = fork()) == 0)
    {
        processData(section, studentId, marks);

        for (int i = 0; i < 200; i++)
        {
            avg = 0;
            for (int j = 0; j < 4; j++)
            {
                avg += marks[j][i];
            }
            avg /= 4;
            snprintf(str, 10000, "%d) The average marks of student with id %d and section %s is %lf\n", ctr++, studentId[i], section[i], avg);
            printToScreen(str);
        }
        printf("\n");
        exit(0);
    }
    else if (id > 0)
    {
        while (waitpid(id, &stat, 0) == -1)
        {
            if (stat != EINTR)
            {
                perror("waitpid");
                return EX_SOFTWARE;
            }
        }
        processData(section, studentId, marks);
        for (int i = 200; i < 400; i++)
        {
            avg = 0;
            for (int j = 0; j < 4; j++)
            {
                avg += marks[j][i];
            }
            avg /= 4;
            snprintf(str, 10000, "%d) The average marks of student with id %d and section %s is %lf\n", ctr++, studentId[i], section[i], avg);
            printToScreen(str);
        }
    }
    else
    {
        perror("fork");
        return EX_OSERR;
    }
    return 0;
}