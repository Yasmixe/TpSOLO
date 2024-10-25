#include <stdio.h>
#include <stdlib.h>

// Structure pour les éléments du sac à dos
typedef struct {
    int profit;
    int poids;
} Element;

void ecrireLP(Element *elements, int n, int capacite, const char *nomFichierLP) {
    FILE *f = fopen(nomFichierLP, "w");
    if (f == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", nomFichierLP);
        return;
    }

    // Écriture de la fonction objectif
    fprintf(f, "Maximize\n obj: ");
    for (int i = 0; i < n; i++) {
        if (i > 0) fprintf(f, " + ");
        fprintf(f, "%d x%d", elements[i].profit, i+1);
    }
    fprintf(f, "\n");

    // Écriture des contraintes
    fprintf(f, "Subject To\n");
    fprintf(f, " c1: ");
    for (int i = 0; i < n; i++) {
        if (i > 0) fprintf(f, " + ");
        fprintf(f, "%d x%d", elements[i].poids, i+1);
    }
    fprintf(f, " <= %d\n", capacite);

    // Définir les variables binaires
    fprintf(f, "Binary\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, " x%d", i+1);
        if (i < n - 1) {
            fprintf(f, " ");
        }
    }
    fprintf(f, "\nEnd\n");

    fclose(f);
    printf("Fichier %s écrit avec succès.\n", nomFichierLP);
}

int main() {
    const char *nomFichierLP = "KP.lp";
    int n, capacite;

    // Lecture des données du fichier texte
    FILE *fichier = fopen("donnees.txt", "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier donnees.txt\n");
        return 1;
    }

    // Lecture du nombre d'éléments et de la capacité
    fscanf(fichier, "%d", &n);
    fscanf(fichier, "%d", &capacite);

    // Allocation de mémoire pour les éléments
    Element elements[n];

    // Lecture des profits et des poids des éléments
    for (int i = 0; i < n; i++) {
        fscanf(fichier, "%d %d", &elements[i].profit, &elements[i].poids);
    }

    fclose(fichier);

    // Écriture du fichier LP
    ecrireLP(elements, n, capacite, nomFichierLP);

    return 0;
}

