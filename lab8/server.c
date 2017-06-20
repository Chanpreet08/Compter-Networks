#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MYPORT "4950" // the port users will be connecting to
#define MAXBUFLEN 100
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    
 if (sa->sa_family == AF_INET) {
 return &(((struct sockaddr_in*)sa)->sin_addr);
 }
 return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(void)
{
    struct addrinfo hints, *servinfo, *p;
    int sockfd, status;
    char ipstr[INET6_ADDRSTRLEN];
    socklen_t addr_len;
    struct sockaddr_storage client_addr;
    char buf[MAXBUFLEN];
    int numbytes;
    int data;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, MYPORT, &hints, &servinfo) != 0) {
        fprintf(stderr, "Server: getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("Server: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("Server: bind");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Server: Failed to Connect\n");
        exit(2);
    }

    printf("listener: waiting to recvfrom...\n");

        addr_len = sizeof client_addr;
        
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&client_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }
        
        buf[numbytes] = '\0';
        printf("Received %s\n",buf);

        data = atoi(buf);
        data += data;
        
        sprintf(buf, "%d", data);

        if ((numbytes = sendto(sockfd, &buf, strlen(buf), 0,
                 (struct sockaddr *)&client_addr, addr_len)) == -1) {
            perror("Server: sendto");
            exit(1);
        }

    close(sockfd);
    freeaddrinfo(servinfo);

    return 0;
}