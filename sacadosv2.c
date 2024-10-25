#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 500
#define MAX_INCOMPATIBLE 12503

// Structure pour stocker les informations des �l�ments et des couples incompatibles
typedef struct {
    int profit;
    int weight;
} Item;

typedef struct {
    int item1;
    int item2;
} IncompatiblePair;

int main() {
    int itemCount, incompatibleCount, capacity;
    Item items[MAX_ITEMS];
    IncompatiblePair incompatiblePairs[MAX_INCOMPATIBLE];

    // Lecture des donn�es
    FILE *inputFile = fopen("knap.txt", "r");
    if (!inputFile) {
        printf("Erreur lors de l'ouverture du fichier de donn�es.\n");
        return 1;
    }

    fscanf(inputFile, "%d %d %d", &itemCount, &incompatibleCount, &capacity);

    // Lire les profits et les poids
    for (int i = 0; i < itemCount; i++) {
        fscanf(inputFile, "%d", &items[i].profit);
    }
    for (int i = 0; i < itemCount; i++) {
        fscanf(inputFile, "%d", &items[i].weight);
    }

    // Lire les couples non compatibles
    for (int i = 0; i < incompatibleCount; i++) {
        fscanf(inputFile, "%d %d", &incompatiblePairs[i].item1, &incompatiblePairs[i].item2);
    }
    fclose(inputFile);

    // G�n�rer le fichier .lp
    FILE *lpFile = fopen("knapsack.lp", "w");
    if (!lpFile) {
        printf("Erreur lors de la cr�ation du fichier .lp.\n");
        return 1;
    }

    // �criture de la fonction objective
    fprintf(lpFile, "Maximize\n");
    fprintf(lpFile, " obj: ");
    for (int i = 0; i < itemCount; i++) {
        fprintf(lpFile, "%s%d x%d", (i == 0) ? "" : " + ", items[i].profit, i + 1);
    }
    fprintf(lpFile, "\n\n");

    // Contraintes de capacit�
    fprintf(lpFile, "Subject To\n");
    fprintf(lpFile, " c1: ");
    for (int i = 0; i < itemCount; i++) {
        fprintf(lpFile, "%s%d x%d", (i == 0) ? "" : " + ", items[i].weight, i + 1);
    }
    fprintf(lpFile, " <= %d\n", capacity);

    // Contraintes d'incompatibilit�
    for (int i = 0; i < incompatibleCount; i++) {
        fprintf(lpFile, " c%d: x%d + x%d <= 1\n", i + 2, incompatiblePairs[i].item1, incompatiblePairs[i].item2);
    }

    // Contraintes de variables binaires
    fprintf(lpFile, "Binary\n");
    for (int i = 0; i < itemCount; i++) {
        fprintf(lpFile, " x%d\n", i + 1);
    }

    // Fin du fichier
    fprintf(lpFile, "End\n");
    fclose(lpFile);

    printf("Fichier knapsack.lp g�n�r� avec succ�s.\n");
    return 0;
}

