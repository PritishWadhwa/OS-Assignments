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
    ;
    int msgid = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msgid, &message, sizeof(message), message.mesg_type, 0);
    printf("Recieved Message: %s\n", message.mesg_text);
    while (strcmp(message.mesg_text, "\0") != 0)
    {
        int msgRecieve = msgrcv(msgid, &message, sizeof(message), message.mesg_type, 0);
        if (msgRecieve < 0)
        {
            perror("recieveError");
            return 1;
        }
        printf("Data Received is : %s \n", message.mesg_text);
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}