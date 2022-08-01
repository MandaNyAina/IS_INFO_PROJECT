#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>     /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h>  /* pour htons, htonl et inet_aton */
#define LG_MESSAGE 256
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */
    int ecrits;                    /* nb d’octets ecrits */
    int retour;
    // Crée un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0); /* 0 indique que l’on utilisera le
    protocole par défaut associé à SOCK_DGRAM soit UDP */
    // Teste la valeur renvoyée par l’appel système socket()
    if (descripteurSocket < 0) /* échec ? */
    {
        perror("socket"); // Affiche le message d’erreur
        exit(-1);         // On sort en indiquant un code erreur
    }
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // n’importe quelle interface locale disponible
    pointDeRencontreLocal.sin_port = htons(0);                 // l’os choisira un numéro de port libre
    // On demande l’attachement local de la socket
    if ((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse)) < 0)
    {
        perror("bind");
        exit(-2);
    }
    printf("Socket attachée avec succès !\n");
    //<-- Début de l’étape n°3
    // Obtient la longueur en octets de la structure sockaddr_in
    longueurAdresse = sizeof(pointDeRencontreDistant);
    // Initialise à 0 la structure sockaddr_in
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
    // Renseigne la structure sockaddr_in avec les informations du serveur distant
    pointDeRencontreDistant.sin_family = PF_INET;
    // On choisit le numéro de port d’écoute du serveur
    pointDeRencontreDistant.sin_port = htons(atoi(argv[2])); // = 5000
    // On choisit l’adresse IPv4 du serveur
    inet_aton(argv[1], &pointDeRencontreDistant.sin_addr); // à modifier selon ses besoins
    // Initialise à 0 le message
    memset(messageEnvoi, 0x00, LG_MESSAGE * sizeof(char));
    // Envoie un message au serveur
    scanf("%s", messageEnvoi);
    ecrits = sendto(descripteurSocket, messageEnvoi, strlen(messageEnvoi), 0, (struct sockaddr *)&pointDeRencontreDistant, longueurAdresse);
    switch (ecrits)
    {
    case -1: /* une erreur ! */
        perror("sendto");
        close(descripteurSocket);
        exit(-3);
    case 0:
        fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
        close(descripteurSocket);
        return 0;
    default: /* envoi de n octets */
        if (ecrits != strlen(messageEnvoi))
            fprintf(stderr, "Erreur dans l’envoie des données !\n\n");
        else
            printf("Message %s envoyé avec succès (%d octets)\n\n", messageEnvoi, ecrits);
            int res = getnameinfo((struct sockaddr*)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal), messageEnvoi, sizeof(messageEnvoi), NULL, 0, NI_NUMERICSERV | NI_NUMERICHOST );
            if (res) {
                printf("Message envoye par : %d\n", res);
            }
    }
    //--> Fin de l’étape n°3 !
    // On ferme la ressource avant de quitter
    close(descripteurSocket);
    return 0;
}