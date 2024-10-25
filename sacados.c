#include <stdio.h>
#include <stdlib.h>

// Structure pour les �l�ments du sac � dos
typedef struct {
    int profit;
    int poids;
} Element;

void ecrireLP(Element *elements, int n, int capacite, const char *nomFichierLP) {
    FILE *f = fopen(nomFichierLP, "w");
    if (f == NULL) {
        printf("Erreur � l'ouverture du fichier %s\n", nomFichierLP);
        return;
    }

    // �criture de la fonction objectif
    fprintf(f, "Maximize\n obj: ");
    for (int i = 0; i < n; i++) {
        if (i > 0) fprintf(f, " + ");
        fprintf(f, "%d x%d", elements[i].profit, i+1);
    }
    fprintf(f, "\n");

    // �criture des contraintes
    fprintf(f, "Subject To\n");
    fprintf(f, " c1: ");
    for (int i = 0; i < n; i++) {
        if (i > 0) fprintf(f, " + ");
        fprintf(f, "%d x%d", elements[i].poids, i+1);
    }
    fprintf(f, " <= %d\n", capacite);

    // D�finir les variables binaires
    fprintf(f, "Binary\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, " x%d", i+1);
        if (i < n - 1) {
            fprintf(f, " ");
        }
    }
    fprintf(f, "\nEnd\n");

    fclose(f);
    printf("Fichier %s �crit avec succ�s.\n", nomFichierLP);
}

int main() {
    const char *nomFichierLP = "KP.lp";
    int n, capacite;

    // Lecture des donn�es du fichier texte
    FILE *fichier = fopen("donnees.txt", "r");
    if (fichier == NULL) {
        printf("Erreur � l'ouverture du fichier donnees.txt\n");
        return 1;
    }

    // Lecture du nombre d'�l�ments et de la capacit�
    fscanf(fichier, "%d", &n);
    fscanf(fichier, "%d", &capacite);

    // Allocation de m�moire pour les �l�ments
    Element elements[n];

    // Lecture des profits et des poids des �l�ments
    for (int i = 0; i < n; i++) {
        fscanf(fichier, "%d %d", &elements[i].profit, &elements[i].poids);
    }

    fclose(fichier);

    // �criture du fichier LP
    ecrireLP(elements, n, capacite, nomFichierLP);

    return 0;
}

