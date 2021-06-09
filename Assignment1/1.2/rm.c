/*********************************************************************************
 * Name:        Pritish Wadhwa                                                   *
 * Section:     B                                                                *
 * Roll NUmber: 2019440                                                          *
 ********************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void rmFile(char fileName[1000])
{
    if (unlink(fileName) != 0)
    {
        perror(fileName);
    }
}

void rmFileD(char fileName[1000])
{
    if (rmdir(fileName) != 0)
    {
        perror(fileName);
    }
}

void rmFileV(char fileName[1000])
{
    if (unlink(fileName) == 0)
    {
        printf("removed '%s'\n", fileName);
    }
    else
    {
        perror(fileName);
    }
}

int main(int argc, char *argv[])
{
    char commandName[10] = "";
    char flag[10] = "";
    char *token = strtok(argv[1], " ");
    strcpy(commandName, token);
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flag, token);
        token = strtok(NULL, " ");
    }
    while (token != NULL)
    {
        char fileName[1000] = "";
        strcpy(fileName, token);
        if (flag[0] == '\0')
        {
            rmFile(fileName);
        }
        else if (flag[1] == 'd')
        {
            rmFileD(fileName);
        }
        else if (flag[1] == 'v')
        {
            rmFileV(fileName);
        }
        else
        {
            printf("Invalid Input -- %s\n", flag);
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}