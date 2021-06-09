#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct mesgQ
{
    long mesg_type;
    char mesg_text[100];
} message = {.mesg_type = 1};

int main()
{
    key_t key = ftok("q2", 65);
    FILE *fptr = fopen("para2.txt", "r");
    char buff[500];
    if (fptr == NULL)
    {
        printf("fopen error");
        return 1;
    }
    else
    {
        printf("Data read from the file:\n");
        fscanf(fptr, "%[^\n]", buff);
        printf("%s\n", buff);
        fclose(fptr);
    }
    int msgid = msgget(key, 0666 | IPC_CREAT);
    char *token = strtok(buff, " ");
    while (token != NULL)
    {
        strcpy(message.mesg_text, token);
        int mgsSend = msgsnd(msgid, &message, sizeof(message), 0);
        if (mgsSend < 0)
        {
            perror("Message send error");
            return 1;
        }
        printf("Sent message: %s\n", token);
        token = strtok(NULL, " ");
    }
    return 0;
}