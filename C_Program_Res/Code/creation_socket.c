#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h> /* pour htons et htonl */
#include <unistd.h>
int main() {
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    socklen_t longueurAdresse;
    // Crée un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0);
    // Teste la valeur renvoyée par l’appel système socket()
    if(descripteurSocket < 0) {
        perror("socket"); // Affiche le message d’erreur
        exit(-1); // On sort en indiquant un code erreur
    }
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);
    //<-- Début de l’étape n°2 !
    // On prépare l’adresse d’attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // n’importe quelle interface locale disponible
    pointDeRencontreLocal.sin_port = htons(0); // l’os choisira un numéro de port libre
    // On demande l’attachement local de la socket
    if((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse)) < 0) {
        perror("bind");
        exit(-2);
    }
    //--> Fin de l’étape n°2 !
    printf("Socket attachée avec succès !\n");
    // On ferme la ressource avant de quitter
    close(descripteurSocket);
    return 0;
}