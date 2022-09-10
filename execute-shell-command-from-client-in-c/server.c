#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

#include <stdlib.h>

#define MAX 4096

int system(const char *command);

void sendToClient(char *messageToClient)
{
}

int main(int argc, char *argv[])
{

    char ch;
    FILE *fichier;
    FILE *sourceFile;

    // freopen("resultat.txt", "w", stdout);

    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[4096], response[4096];

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    memset(&server, 0, sizeof(server));

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        // print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);

    // accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    // Receive a message from client
    while ((read_size = recv(client_sock, client_message, 4096, 0)) > 0)
    {

        fichier = fopen("resultat.txt", "w");

        // strcat(client_message, " 2>&1");

        // strcat(client_message, "");

        sourceFile = popen(client_message, "r");

        // Copy the result of the command into resultat.txt
        while ((ch = fgetc(sourceFile)) != EOF)
            fputc(ch, fichier);

        fclose(fichier);

        write(client_sock, client_message, strlen(client_message));

        // Free ressources consumed
        for (int siz = 0; siz <= read_size; siz++)
        {
            client_message[siz] = '\0';
        }
    }

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }
    return 0;
}