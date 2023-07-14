#include <stdio.h>

#define NUM_SERVERS 5

// Structure représentant un serveur
typedef struct {
    int id;
    int isCoordinator;
} Server;

// Fonction pour lancer l'élection
void startElection(Server servers[]) {
    int i, j;
    int coordinatorID = -1;

    // Recherche du plus grand ID de serveur
    for (i = 0; i < NUM_SERVERS; i++) {
        if (servers[i].id > coordinatorID) {
            coordinatorID = servers[i].id;
        }
    }

    // Processus d'élection
    for (i = 0; i < NUM_SERVERS; i++) {
        if (servers[i].isCoordinator) {
            // Un serveur actif démarre l'élection
            printf("Server %d initiates the election process.\n", servers[i].id);

            // Envoie un message d'élection aux serveurs avec un ID plus élevé
            for (j = i + 1; j < NUM_SERVERS; j++) {
                if (servers[j].id > servers[i].id) {
                    printf("Server %d sends an election message to Server %d.\n", servers[i].id, servers[j].id);
                }
            }
        }
    }

    // Vérification des réponses et élection du coordinateur
    for (i = 0; i < NUM_SERVERS; i++) {
        if (servers[i].id > coordinatorID) {
            // Un serveur avec un ID plus élevé a répondu
            printf("Server %d receives a response from Server %d.\n", servers[i].id, coordinatorID);
            coordinatorID = servers[i].id;
        }
    }

    // Annonce du coordinateur élu
    printf("Server %d becomes the new coordinator.\n", coordinatorID);

    // Mettre à jour les états des serveurs
    for (i = 0; i < NUM_SERVERS; i++) {
        servers[i].isCoordinator = (servers[i].id == coordinatorID);
    }
}

int main() {
    Server servers[NUM_SERVERS] = {
        {1, 1},  // Le serveur 1 est le coordinateur initial
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0}
    };

    // Simulation d'une défaillance du coordinateur initial (serveur 1)
    servers[0].isCoordinator = 0;

    // Lancer l'élection
    startElection(servers);

    return 0;
}