//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Programme principal de CER-J-O
//
#include <stdio.h>
#include <stdbool.h>

#include "common.h"
#include "manageAthletesData.h"
#include "history.h"
#include "statistics.h"

// Tableau contenant les performances des athletes pour les differents entrainements
extern Athlete athletes[MAX_ATHLETES];

// Numero de version du programme
const float version_prg = 1.0f;

//
// Fonction: int main()
// Description: Programme principal de CER-JO
//
int main() {
    long choix;

#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    // Affichage du nom et de la version du programme
    #if defined(_WIN32)
    SetConsoleTextAttribute(hConsole, BLANC);
    printf("Programme ");
    SetConsoleTextAttribute(hConsole, BLEU);
    printf("C");
    SetConsoleTextAttribute(hConsole, JAUNE);
    printf("E");
    SetConsoleTextAttribute(hConsole, BLANC);
    printf("R-");
    SetConsoleTextAttribute(hConsole, VERT);
    printf("J");
    SetConsoleTextAttribute(hConsole, BLANC);
    printf("-");
    SetConsoleTextAttribute(hConsole, ROUGE);
    printf("O");
    SetConsoleTextAttribute(hConsole, BLANC);
    printf(", version: %.2f\n", version_prg);
    #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
    printf("Programme \033[%dmC\033[m\033[%dmE\033[mR-\033[%dmJ\033[m-\033[%dmO\033[m, version: %.2f\n", BLEU, JAUNE, VERT, ROUGE, version_prg);
    #endif
    printf("Groupe: Angel PASQUIN, Jean-Paul ALPHONSERAJ, Mohammed MOUBTAKIR\n\n");

    // Charge les données existantes stockées dans le répertoire "./data"
    chargerPerformancesEntrainementsAthletes();

    // Affiche le menu principal et attend les saisies de l'utilisateur
    while (true) {
        printf("Menu principal:\n");
        printf("\t(1) Remplir et sauvegarder les performances des entrainements\n");
        printf("\t(2) Voir l'historique d'entrainement\n");
        printf("\t(3) Consulter les statistiques de performance de chaque athlete\n");
        printf("\t(4) Quitter le menu principal\n");
        printf("\tChoix: ");
        // Appel à la fonction permettant de saisir une valeur (type long)
        choix = lireLong();

        switch (choix) {
            case 1:
                // Appel à la fonction d'enregistrement des performances
                enregistrerPerformancesEntrainementsAthletes();
                break;
            case 2:
                // Appel à la fonction de visualisation de l'historique
                visualiserHistorique();
                break;
            case 3:
                // Appel à la fonction de visualisation des statistiques
                visualiserStatistiques();
                break;
            case 4:
                // Sortie du programme
                printf("Au revoir!\n");
                return 0;
            default:
                // Affiche choix invalide lorsque la valeur saisie est incorrecte
                printf("Choix non valide, veuillez ressayer !\n");
                break;
        }
    }
}