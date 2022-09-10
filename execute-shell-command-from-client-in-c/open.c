include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>     /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h>  /* pour htons, htonl et inet_aton */
#include <netdb.h>


int main(int argc, char *argv[])
{

    // struct sockaddr *sa;
    // char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

    // if (getnameinfo(sa, sizeof(sa), hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV))
    // {

    //     printf("host=%s, serv=%s \n", hbuf, sbuf);

    // }



}