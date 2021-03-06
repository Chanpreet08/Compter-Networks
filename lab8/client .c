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
#define SERVERPORT "4950" // the port users will be connecting to
#define MAXBUFLEN 100

int main(int argc, char *argv[])
{
   int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    socklen_t addr_len;
    struct sockaddr_storage server_addr;
    char buf[MAXBUFLEN];

    
    if (argc != 2) {
        fprintf(stderr,"Client: Talker Hostname Message\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "Client: getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("Client: socket");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "Client: Failed to Create Socket\n");
        return 2;
    }
    
    if ((numbytes = sendto(sockfd, argv[1], strlen(argv[1]), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("Client: sendto");
        exit(1);
    }
    
    addr_len = sizeof server_addr;
    
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0,
		(struct sockaddr *)&server_addr, &addr_len)) == -1) {
        perror("recvfrom");
		exit(1);
	}

    buf[numbytes] = '\0';
    printf("Received %s\n",buf);
    
    freeaddrinfo(servinfo);
    close(sockfd);
    return 0;
}