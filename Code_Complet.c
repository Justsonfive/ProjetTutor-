#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures de données
typedef struct {
    int numero;
    char nom[50];
    char profession[50];
} Client;

typedef struct {
    int code;
    char marque[50];
    char modele[50];
    int nbTotal;
    int nbDisponible;
    float tarif;
} Voiture;

typedef struct {
    int numeroClient;
    int codeVoiture;
    char dateDebut[11];
    int nbJours;
    float tarif;
    float coutTotal;
    char etat[20];
} Location;

// Prototypes des fonctions
void ajouterClient();
void afficherClients();
void ajouterVoiture();
void afficherVoitures();
void ajouterLocation();
void afficherLocations();
void chargerDonnees();
void sauvegarderDonnees();

// Variables globales
#define MAX_CLIENTS 100
#define MAX_VOITURES 100
#define MAX_LOCATIONS 100

Client clients[MAX_CLIENTS];
int nbClients = 0;

Voiture voitures[MAX_VOITURES];
int nbVoitures = 0;

Location locations[MAX_LOCATIONS];
int nbLocations = 0;

// Fonction pour ajouter un client
void ajouterClient() {
    if (nbClients >= MAX_CLIENTS) {
        printf("Erreur: Nombre maximum de clients atteint.\n");
        return;
    }
    Client nouveauClient;
    printf("Entrez le numéro du client: ");
    scanf("%d", &nouveauClient.numero);
    printf("Entrez le nom du client: ");
    scanf("%s", nouveauClient.nom);
    printf("Entrez la profession du client: ");
    scanf("%s", nouveauClient.profession);

    for (int i = 0; i < nbClients; i++) {
        if (clients[i].numero == nouveauClient.numero) {
            printf("Erreur: Numéro de client déjà utilisé.\n");
            return;
        }
    }

    clients[nbClients++] = nouveauClient;
    sauvegarderDonnees();
    printf("Client ajouté avec succès.\n");
}

// Fonction pour afficher les clients
void afficherClients() {
    if (nbClients == 0) {
        printf("Aucun client enregistré.\n");
        return;
    }
    for (int i = 0; i < nbClients; i++) {
        printf("Client Numéro: %d\n", clients[i].numero);
        printf("Nom: %s\n", clients[i].nom);
        printf("Profession: %s\n", clients[i].profession);
        printf("\n");
    }
}

// Fonction pour ajouter une voiture
void ajouterVoiture() {
    if (nbVoitures >= MAX_VOITURES) {
        printf("Erreur: Nombre maximum de voitures atteint.\n");
        return;
    }
    Voiture nouvelleVoiture;
    printf("Entrez le code de la voiture: ");
    scanf("%d", &nouvelleVoiture.code);
    printf("Entrez la marque de la voiture: ");
    scanf("%s", nouvelleVoiture.marque);
    printf("Entrez le modèle de la voiture: ");
    scanf("%s", nouvelleVoiture.modele);
    printf("Entrez le nombre total d'exemplaires: ");
    scanf("%d", &nouvelleVoiture.nbTotal);
    nouvelleVoiture.nbDisponible = nouvelleVoiture.nbTotal;
    printf("Entrez le tarif journalier: ");
    scanf("%f", &nouvelleVoiture.tarif);

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].code == nouvelleVoiture.code) {
            printf("Erreur: Code de voiture déjà utilisé.\n");
            return;
        }
    }

    voitures[nbVoitures++] = nouvelleVoiture;
    sauvegarderDonnees();
    printf("Voiture ajoutée avec succès.\n");
}

// Fonction pour afficher les voitures
void afficherVoitures() {
    if (nbVoitures == 0) {
        printf("Aucune voiture enregistrée.\n");
        return;
    }
    for (int i = 0; i < nbVoitures; i++) {
        printf("Voiture Code: %d\n", voitures[i].code);
        printf("Marque: %s\n", voitures[i].marque);
        printf("Modèle: %s\n", voitures[i].modele);
        printf("Nombre total d'exemplaires: %d\n", voitures[i].nbTotal);
        printf("Nombre d'exemplaires disponibles: %d\n", voitures[i].nbDisponible);
        printf("Tarif journalier: %.2f\n", voitures[i].tarif);
        printf("\n");
    }
}

// Fonction pour ajouter une location
void ajouterLocation() {
    if (nbLocations >= MAX_LOCATIONS) {
        printf("Erreur: Nombre maximum de locations atteint.\n");
        return;
    }
    Location nouvelleLocation;
    printf("Entrez le numéro du client: ");
    scanf("%d", &nouvelleLocation.numeroClient);
    printf("Entrez le code de la voiture: ");
    scanf("%d", &nouvelleLocation.codeVoiture);
    printf("Entrez la date de début (jj/mm/aaaa): ");
    scanf("%s", nouvelleLocation.dateDebut);
    printf("Entrez le nombre de jours: ");
    scanf("%d", &nouvelleLocation.nbJours);

    int clientExiste = 0;
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].numero == nouvelleLocation.numeroClient) {
            clientExiste = 1;
            break;
        }
    }
    if (!clientExiste) {
        printf("Erreur: Client inconnu.\n");
        return;
    }

    int voitureDisponible = 0;
    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].code == nouvelleLocation.codeVoiture && voitures[i].nbDisponible > 0) {
            voitureDisponible = 1;
            voitures[i].nbDisponible--;
            nouvelleLocation.tarif = voitures[i].tarif;
            nouvelleLocation.coutTotal = voitures[i].tarif * nouvelleLocation.nbJours;
            strcpy(nouvelleLocation.etat, "Réservée");
            break;
        }
    }
    if (!voitureDisponible) {
        printf("Erreur: Voiture non disponible.\n");
        return;
    }

    locations[nbLocations++] = nouvelleLocation;
    sauvegarderDonnees();
    printf("Location ajoutée avec succès.\n");
}

// Fonction pour afficher les locations
void afficherLocations() {
    if (nbLocations == 0) {
        printf("Aucune location enregistrée.\n");
        return;
    }
    for (int i = 0; i < nbLocations; i++) {
        printf("Location Numéro Client: %d\n", locations[i].numeroClient);
        printf("Code Voiture: %d\n", locations[i].codeVoiture);
        printf("Date de début: %s\n", locations[i].dateDebut);
        printf("Nombre de jours: %d\n", locations[i].nbJours);
        printf("Tarif journalier: %.2f\n", locations[i].tarif);
        printf("Coût total: %.2f\n", locations[i].coutTotal);
        printf("État: %s\n", locations[i].etat);
        printf("\n");
    }
}

// Fonction pour sauvegarder les données dans des fichiers
void sauvegarderDonnees() {
    FILE *fclients = fopen("clients.txt", "w");
    FILE *fvoitures = fopen("voitures.txt", "w");
    FILE *flocations = fopen("locations.txt", "w");

    if (!fclients || !fvoitures || !flocations) {
        printf("Erreur: Impossible d'ouvrir les fichiers pour la sauvegarde.\n");
        return;
    }

    for (int i = 0; i < nbClients; i++) {
        fprintf(fclients, "%d %s %s\n", clients[i].numero, clients[i].nom, clients[i].profession);
    }
    for (int i = 0; i < nbVoitures; i++) {
        fprintf(fvoitures, "%d %s %s %d %d %.2f\n", voitures[i].code, voitures[i].marque, voitures[i].modele,
                voitures[i].nbTotal, voitures[i].nbDisponible, voitures[i].tarif);
    }
    for (int i = 0; i < nbLocations; i++) {
        fprintf(flocations, "%d %d %s %d %.2f %.2f %s\n", locations[i].numeroClient, locations[i].codeVoiture,
                locations[i].dateDebut, locations[i].nbJours, locations[i].tarif, locations[i].coutTotal,
                locations[i].etat);
    }

    fclose(fclients);
    fclose(fvoitures);
    fclose(flocations);
}

// Fonction
