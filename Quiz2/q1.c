#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

int hasEscapeChar(char chr)
{
    if (chr == 'a' || chr == 'b' || chr == 'f' || chr == 'r' || chr == 't' || chr == 'v')
    {
        return 1;
    }
    return 0;
}

void ConvertToUpper(char *str)
{
    int ctr = 0;
    do
    {
        if (str[ctr] == (char)'\\' && str[ctr + 1] != '\0' && str[ctr + 1] == (char)'n')
        {
            str[ctr] = '\0';
            break;
        }
        else if (str[ctr] == (char)'\\' && str[ctr + 1] != '\0')
        {
            if (hasEscapeChar(str[ctr + 1]) == 1)
            {
                ctr += 2;
                continue;
            }
        }
        else if (str[ctr] >= 'a' && str[ctr] <= 'z')
        {
            str[ctr] = str[ctr] - 32;
        }
        ctr++;
    } while (str[ctr] != '\0');
    return;
}

int main()
{
    int pipe1[2];
    int pipe2[2];
    int pipeStat = pipe(pipe1);
    int pipeStat2 = pipe(pipe2);
    pid_t procId;
    if (pipeStat < 0)
    {
        fprintf(stderr, "%s\n", "Pipe 1 failed\n");
        return 1;
    }
    if (pipeStat2 < 0)
    {
        fprintf(stderr, "%s\n", "Pipe 2 failed\n");
        return 1;
    }
    if ((procId = fork()) == 0)
    {
        char readingBuffer[128];
        close(pipe2[0]);
        close(pipe1[1]);
        read(pipe1[0], readingBuffer, 128);
        ConvertToUpper(readingBuffer);
        write(pipe2[1], readingBuffer, 128);
        close(pipe2[1]);
        close(pipe1[0]);
    }
    else if (procId > 0)
    {
        char charIn;
        close(pipe1[0]);
        close(pipe2[1]);
        char readingBuffer[128];
        scanf("%[^\n]", readingBuffer);
        write(pipe1[1], readingBuffer, 128);
        wait(NULL);
        read(pipe2[0], readingBuffer, 128);
        printf("%s\n", readingBuffer);
        close(pipe1[1]);
        close(pipe2[0]);
    }
    if (procId < 0)
    {
        fprintf(stderr, "%s\n", "Fork failed\n");
        return 1;
    }
    return 0;
}