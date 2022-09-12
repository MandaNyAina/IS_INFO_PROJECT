#include <stdio.h>      //printf
#include <stdlib.h>     //printf
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>

#define MAX 15

int main(int argc, char *argv[])
{

    char ch;

    FILE *fichier;

    char *text;

    long numbytes;

    char buf[MAX];

    int sock, read_size;
    struct sockaddr_in server;
    char message[4096], server_reply[4096];
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    // Allocate ressources
    memset(&server, 0, sizeof(server));

    puts("Connected\n");
    // keep communicating with server
    while (1)
    {

        // for (int i = 0; i <= sizeof(message); i++)
        // {
        //     message[i] = '\0';
        // }

        bzero(message, sizeof(message));

        printf("Enter message : ");

        // fgets(message, 4096, stdin);
        int n = 0;
        while ((message[n++] = getchar()) != '\n')
            ;
        // printf("n = %d", n);
        // printf("%d", strlen(message));
        message[n - 1] = ' ';
        // printf("%d", strlen(message));
        strcat(message, "2>&1");

        // printf("%d", strlen(message));

        // char mess[4096] = strcat(message, " 2>&1");

        // char mess[5] = " 2>&1";
        // char mess = " 2>&1";
        // strcat(message, mess);

        printf("Command = %s\n", message);

        // if (message == "exit")
        // {
        //     exit 0;
        // }

        if ((send(sock, message, strlen(message), 0)) < 0)
        {
            puts("Send failed");
            return 1;
        }
        // Receive a reply from the server
        if ((read_size = recv(sock, server_reply, 4096, 0)) < 0)
        {
            puts("recv failed");
            break;
        }

        fichier = fopen("resultat.txt", "r");

        // while ((ch = fgetc(fichier)) != EOF)
        if (fichier == NULL)
            return 1;

        fseek(fichier, 0L, SEEK_END);
        numbytes = ftell(fichier);
        fseek(fichier, 0L, SEEK_SET);

        text = (char *)calloc(numbytes, sizeof(char));

        if (text == NULL)
            return 1;

        fread(text, sizeof(char), numbytes, fichier);

        puts("Server reply :");
        // puts(server_reply);

        fread(text, sizeof(char), numbytes, fichier);

        server_reply[read_size] = '\0';

        fclose(fichier);

        puts(text);
    

        // for (int siz = 0; siz <= strlen(server_reply); siz++)
        // {

        //     server_reply[read_size] = '\0';
        // }
    }
    close(sock);
    return 0;
}