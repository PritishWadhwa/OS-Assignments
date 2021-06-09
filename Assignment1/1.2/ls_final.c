/*********************************************************************************
 * Name:        Pritish Wadhwa                                                   *
 * Section:     B                                                                *
 * Roll NUmber: 2019440                                                          *
 ********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void printLs(char argument[1000])
{
    struct dirent **names;
    int n;
    if (strlen(argument) == 0)
    {
        n = scandir(".", &names, NULL, alphasort);
    }
    else
    {
        n = scandir(argument, &names, NULL, alphasort);
    }
    int i = 0;
    if (n < 0)
    {
        perror("scandir");
    }
    else
    {
        while (i < n)
        {
            if (names[i]->d_name[0] == '.')
            {
                free(names[i++]);
                continue;
            }
            printf("%s ", names[i]->d_name);
            free(names[i++]);
        }
        printf("\n");
        free(names);
    }
}

void printLsA(char argument[1000])
{
    struct dirent **names;
    int n;
    if (strlen(argument) == 0)
    {
        n = scandir(".", &names, NULL, alphasort);
    }
    else
    {
        n = scandir(argument, &names, NULL, alphasort);
    }
    int i = 0;
    if (n < 0)
    {
        perror("scandir");
    }
    else
    {
        while (i < n)
        {
            printf("%s ", names[i]->d_name);
            free(names[i++]);
        }
        printf("\n");
        free(names);
    }
}

void printLsL(char argument[1000])
{
    DIR *thedirectory;
    struct dirent *thefile;
    struct stat thestat;
    struct passwd *tf;
    struct group *gf;
    char buf[512];
    if (strlen(argument) == 0)
    {
        argument = ".";
    }
    thedirectory = opendir(argument);
    while ((thefile = readdir(thedirectory)) != NULL)
    {
        if (thefile->d_name[0] == '.')
        {
            continue;
        }
        sprintf(buf, "%s/%s", argument, thefile->d_name);
        stat(buf, &thestat);
        switch (thestat.st_mode & S_IFMT)
        {
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("-");
            break;
        }
        printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
        printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
        printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
        printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
        printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
        printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
        printf((thestat.st_mode & S_IROTH) ? "r" : "-");
        printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
        printf((thestat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", thestat.st_nlink);
        tf = getpwuid(thestat.st_uid);
        printf(" %s", tf->pw_name);
        gf = getgrgid(thestat.st_gid);
        printf(" %s", gf->gr_name);
        printf(" %zu", thestat.st_size);
        printf(" %s", thefile->d_name);
        printf(" %s", ctime(&thestat.st_mtime));
    }
    closedir(thedirectory);
}

int main(int argc, char *argv[])
{
    char commandName[10] = "";
    char flag[10] = "";
    char argument[1000] = "";
    if (argc > 1)
    {
        char *token = strtok(argv[1], " ");
        strcpy(commandName, token);
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (token[0] == '-')
            {
                strcpy(flag, token);
                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(argument, token);
                }
            }
            else
            {
                strcpy(argument, token);
            }
        }
    }
    if (flag[0] == '\0')
    {
        printLs(argument);
    }
    else if (flag[1] == 'a')
    {
        printLsA(argument);
    }
    else if (flag[1] == 'l')
    {
        printLsL(argument);
    }
    else
    {
        printf("Invalid Input -- %s\n", flag);
        return 1;
    }
    return 0;
}