#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8389

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket creation error");
        return 1;
    }
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
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    char *token = strtok(buff, " ");
    char tepm[500];
    while (token != NULL)
    {
        strcpy(tepm, token);
        sendto(sockfd, (const char **)tepm, strlen(tepm), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Message sent: %s \n", token);
        token = strtok(NULL, " ");
    }
    close(sockfd);
    return 0;
}