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
        perror("socket creation failed");
        return 1;
    }
    struct sockaddr_in servaddr, cliaddr;
    char temp[500];
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    strcpy(temp, "hello from server");
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        return 1;
    }
    char buffer[1024];
    int len = sizeof(cliaddr);
    int n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    if (n < 0)
    {
        perror("recieve error");
        return 1;
    }
    printf("Message Recieved: %s\n", buffer);
    while ((char *)buffer != NULL)
    {

        n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        if (n < 0)
        {
            perror("recieve error");
            return 1;
        }
        buffer[n] = '\0';
        printf("Message Recieved: %s\n", buffer);
    }
    sendto(sockfd, (const char **)temp, strlen(temp), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    return 0;
}