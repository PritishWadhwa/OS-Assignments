/*********************************************************************************
 * Name:        Pritish Wadhwa                                                   *
 * Section:     B                                                                *
 * Roll NUmber: 2019440                                                          *
 ********************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void makeDir(char fileName[1000])
{
    int check = mkdir(fileName, 0777);
    if (check == -1)
    {
        perror(fileName);
    }
}

void makeDirV(char fileName[1000])
{
    int check = mkdir(fileName, 0777);
    if (check == -1)
    {
        perror(fileName);
    }
    else
    {
        printf("mkdir: created directory '%s'\n", fileName);
    }
}

void makeDirM(char fileName[1000], int mode)
{
    int check = mkdir(fileName, mode);
    if (check == -1)
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
            makeDir(fileName);
        }
        else
        {
            if (flag[1] == 'v')
            {
                makeDirV(fileName);
            }
            else if (flag[1] == 'm' && flag[2] == '=')
            {
                if (strlen(flag) < 6)
                {
                    printf("Invalid Input -- %s\n", flag);
                    return 1;
                }
                if (strlen(flag) == 7)
                {
                    char modeStr[5];
                    for (int i = 0; i < 4; i++)
                    {
                        modeStr[i] = flag[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    makeDirM(fileName, mode);
                }
                else
                {
                    char modeStr[4];
                    for (int i = 0; i < 3; i++)
                    {
                        modeStr[i] = flag[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    makeDirM(fileName, mode);
                }
            }
            else
            {
                printf("Invalid Input -- %s\n", flag);
                return 1;
            }
        }
        token = strtok(NULL, " ");
    }
    return 0;
}