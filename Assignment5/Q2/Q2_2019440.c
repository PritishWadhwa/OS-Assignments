//Name: Pritish Wadhwa
//Roll Number: 2019440
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/file.h>

FILE *fp = NULL;

int fd;

void loadMainMenu()
{
    printf("1.) Add/Edit Files\n");
    printf("2.) View data in a file\n");
    printf("3.) Exit\n");
    printf("Enter Choice: ");
    // return;
}

void addFile()
{
    char fileName[20];
    char writeData[1000];
    char readData[1000];
    printf("Enter the file name: ");
    scanf(" %[^\n]*c", fileName);
    fp = fopen(fileName, "r+");
    if (fp != NULL)
    {
        fd = fileno(fp);
        if (flock(fd, LOCK_EX | LOCK_NB) == -1)
        {
            printf("File locked\n");
        }
        else
        {
            printf("File unlocked\n");
        }
    }
    if (fp == NULL)
    {
        printf("File doesn't exists, New file with the name %s created!\n", fileName);
        fp = fopen(fileName, "w");
        fd = fileno(fp);
        if (flock(fd, LOCK_EX | LOCK_NB) == -1)
        {
            printf("File locked\n");
        }
        else
        {
            printf("File unlocked\n");
        }
        printf("Write the data to be added: ");
        scanf(" %[^\n]*c", writeData);
        fputs(writeData, fp);
        printf("Data added to the file\n");
    }
    else
    {
        int readChoice;
        printf("File opened!!!\nThe data in the file is: ");
        while (fgets(readData, 1000, fp) != NULL)
        {
            printf("%s", readData);
        }
        printf("\nWould you like to:-\n");
        printf("1.) Add to this data\n");
        printf("2.) Change this data\n");
        printf("Input your choice: ");
        scanf("%d", &readChoice);
        if (readChoice == 1)
        {
            fclose(fp);
            fp = fopen(fileName, "a");
            printf("Write the data to be added: ");
            scanf(" %[^\n]*c", writeData);
            fputs(writeData, fp);
            printf("Data added to the file\n");
        }
        else
        {
            fclose(fp);
            fp = fopen(fileName, "w");
            printf("Write the new data: ");
            scanf(" %[^\n]*c", writeData);
            fputs(writeData, fp);
            printf("Old data replaced with new Data!\n");
        }
    }
    fd = fileno(fp);
    flock(fd, F_UNLCK);
    // if (flock(fd, 8) == 0)
    // {
    //     printf("End File locked");
    // }
    // else
    // {
    //     printf("End File unlocked");
    // }
    fclose(fp);
}

void viewData()
{
    char fileName[20];
    char readData[1000];
    printf("Enter the file name: ");
    scanf(" %[^\n]*c", fileName);
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("File doesn't exist!\n");
        return;
    }
    else
    {
        printf("File opened!!!\nThe data in the file is: ");
        while (fgets(readData, 1000, fp) != NULL)
        {
            printf("%s", readData);
        }
        printf("\n");
    }
    fclose(fp);
}

int main(void)
{
    int runMain = 1;
    int choice;
    while (runMain == 1)
    {
        loadMainMenu();
        scanf("%d", &choice);
        if (choice == 1)
        {
            addFile();
        }
        else if (choice == 3)
        {
            return 0;
        }
        else if (choice == 2)
        {
            viewData();
        }
    }
    return 0;
}
