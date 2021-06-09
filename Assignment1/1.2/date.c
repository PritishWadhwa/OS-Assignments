/*********************************************************************************
 * Name:        Pritish Wadhwa                                                   *
 * Section:     B                                                                *
 * Roll NUmber: 2019440                                                          *
 ********************************************************************************/
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sysexits.h>
#include <errno.h>

void printDate()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = localtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s %s %02d %02d:%02d:%02d %s %d\n", buf1, buf2, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, buf3, ptm->tm_year + 1900);
}

void printDateU()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = gmtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s %s %02d %02d:%02d:%02d UTC %d\n", buf1, buf2, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, ptm->tm_year + 1900);
}

void printDateR()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = localtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s, %02d %s %d %02d:%02d:%02d %s\n", buf1, ptm->tm_mday, buf2, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, buf3);
}

int main(int argc, char *argv[])
{
    char commandName[10] = "";
    char flag[10] = "";
    char *token = strtok(argv[1], " ");
    strcpy(commandName, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        strcpy(flag, token);
    }
    if (strcmp(flag, "") == 0)
    {
        printDate();
    }
    else if (flag[1] == 'u')
    {
        printDateU();
    }
    else if (flag[1] == 'R')
    {
        printDateR();
    }
    else
    {
        printf("Invalid Input -- %s\n", flag);
        return 1;
    }
    return 0;
}