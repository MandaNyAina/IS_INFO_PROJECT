#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 


int main() {
    struct sockaddr *sa;
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    if (getnameinfo(sa, sizeof(sa), hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV)) {
        printf("host = %s, serve = %s \n", hbuf, sbuf);
    }
    return 0;
}