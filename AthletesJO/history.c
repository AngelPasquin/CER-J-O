//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Gestion de l'historique des performances des entrainements des athlètes
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "history.h"
#include "common.h"

// Valeur de date pour récuperer toutes les dates
const unsigned long allDates = 99990101;

// Tableau contenant les performances des athlètes pour les différents entraînements
extern Athlete athletes[MAX_ATHLETES];

// Tableau contenant les libellés des épreuves
extern char tabEpreuves[][20];

//
// Fonction: void visualiserHistorique()
// Description: Visualisation de l'historique des performances des entraînements des athlètes
//
void visualiserHistorique() {
    #if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    char athlete_name[MAX_NAME_LENGTH];
    TypeEpreuve type_epreuve;
    long choixEpreuve = 0;
    bool isNameChosen = false;
    bool isRaceChosen = false;
    unsigned long date_training = 0;
    char display_date_training[DATE_LENGTH] = {0};
    char afficher_performance[20] = {0};

    // Choisir l'athlète
    do {
        printf("Nom de l'athlete (si vous voulez tous les noms, tapez ALL): ");
        lireChaine(athlete_name, MAX_NAME_LENGTH);
        if (strcmp(athlete_name,"") != 0) {
            isNameChosen = true;
        } else {
            printf("Valeur non valide, veuillez reessayer !\n");
        }
    } while(isNameChosen == false);

    // Choisir l'épreuve
    isRaceChosen = false;
    do {
        printf("Type d'epreuve (si vous voulez consulter toutes les epreuves, tapez 6):\n");
        printf("\t(1) 100m\n");
        printf("\t(2) 400m\n");
        printf("\t(3) 5000m\n");
        printf("\t(4) Marathon\n");
        printf("\t(5) 4*400m Relay\n");
        printf("\t(6) Toutes les epreuves\n");
        printf("\tChoix: ");

        // Appel à la fonction permettant de saisir une valeur (type long)
        choixEpreuve = lireLong();

        switch (choixEpreuve) {
            case 1:
                type_epreuve = RACE100M;
                isRaceChosen = true;
                break;
            case 2:
                type_epreuve = RACE400M;
                isRaceChosen = true;
                break;
            case 3:
                type_epreuve = RACE5000M;
                isRaceChosen = true;
                break;
            case 4:
                type_epreuve = RACEMARATHON;
                isRaceChosen = true;
                break;
            case 5:
                type_epreuve = RACE4X400MRELAY;
                isRaceChosen = true;
                break;
            case 6:
                type_epreuve = ALLRACES;
                isRaceChosen = true;
                break;
            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    } while(isRaceChosen == false);

    // Choisir la date
    do {
        printf("Date (format JJ/MM/AAAA, si vous voulez toutes les dates, tapez 01/01/9999): ");
        date_training = lireDate();
    } while(date_training == 0);
    
    int num_athletes = 0; 
    bool athlete_found = false;

    while (strcmp(athletes[num_athletes].name, "") != 0 && !athlete_found)  {
        if (strcmp(athlete_name, "ALL") != 0) {
            // Rechercher le nom de l'athlète dans le tableau "athletes"
            if (strcmp(athletes[num_athletes].name, athlete_name) == 0) {
                if (strcmp(athletes[num_athletes].name, athlete_name) == 0)
                {
                    int num_trainings = athletes[num_athletes].number_trainings;
                    int i;

                    for (i = 0; i < num_trainings; i++) {
                        if (athletes[num_athletes].trainings[i].type_epreuve == type_epreuve || type_epreuve == ALLRACES) {
                            // Mise en forme de la date pour affichage
                            afficherDate(athletes[num_athletes].trainings[i].date, display_date_training);

                            // Mise en forme de la performance pour affichage
                            afficherPerformance(athletes[num_athletes].trainings[i].time, afficher_performance);

                            // Affichage si type epreuve est le relais 4*400m
                            if (athletes[num_athletes].trainings[i].type_epreuve == RACE4X400MRELAY) {
                                #if defined(_WIN32)
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf("Nom de l'athlete ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", athletes[num_athletes].name);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", date de l'entrainement: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", display_date_training);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", epreuve: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve]);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", perf.: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", afficher_performance);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", position: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                 printf("%d\n", athletes[num_athletes].trainings[i].position);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                                printf("Nom de l'athlete \033[%dm%s\033[m, date de l'entrainement: \033[%dm%s\033[m, epreuve: \033[%dm%s\033[m, perf.: \033[%dm%s\033[m, position: \033[%dm%d\033[m\n",
                                       BLEU, athletes[num_athletes].name,
                                       BLEU, display_date_training,
                                       BLEU, tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve],
                                       BLEU, afficher_performance,
                                       BLEU, athletes[num_athletes].trainings[i].position);
                                #endif
                            } else {
                                #if defined(_WIN32)
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf("Nom de l'athlete ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", athletes[num_athletes].name);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", date de l'entrainement: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", display_date_training);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", epreuve: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve]);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", perf.: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s\n", afficher_performance);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                                printf("Nom de l'athlete \033[%dm%s\033[m, date de l'entrainement: \033[%dm%s\033[m, epreuve: \033[%dm%s\033[m, perf.: \033[%dm%s\033[m\n",
                                       BLEU, athletes[num_athletes].name,
                                       BLEU, display_date_training,
                                       BLEU, tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve],
                                       BLEU, afficher_performance);
                                #endif
                            }
                        }
                    }
                    athlete_found = true;
                }
                else {
                    printf("Athlete introuvable: %s\n", athlete_name);
                }    
            }
            else {
                printf("Athlete introuvable: %s\n", athlete_name);
            }
        }
        else {
            // Cas tous les athlètes demandés
            int num_trainings = athletes[num_athletes].number_trainings;
            int i;

                for (i = 0; i < num_trainings; i++) {
                    if (athletes[num_athletes].trainings[i].type_epreuve == type_epreuve || type_epreuve == ALLRACES) {
                        // Mise en forme de la date pour affichage
                        afficherDate(athletes[num_athletes].trainings[i].date, display_date_training);

                        // Mise en forme de la performance pour affichage
                        afficherPerformance(athletes[num_athletes].trainings[i].time, afficher_performance);

                        if (athletes[num_athletes].trainings[i].date == date_training || date_training == allDates) {
                            // Affichage si le type de l'épreuve est le relais 4*400m
                            if (athletes[num_athletes].trainings[i].type_epreuve == RACE4X400MRELAY) {
                                #if defined(_WIN32)
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf("Nom de l'athlete ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", athletes[num_athletes].name);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", date de l'entrainement: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", display_date_training);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", epreuve: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve]);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", perf.: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", afficher_performance);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", position: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                 printf("%d\n", athletes[num_athletes].trainings[i].position);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                                printf("Nom de l'athlete \033[%dm%s\033[m, date de l'entrainement: \033[%dm%s\033[m, epreuve: \033[%dm%s\033[m, perf.: \033[%dm%s\033[m, position: \033[%dm%d\033[m\n",
                                       BLEU, athletes[num_athletes].name,
                                       BLEU, display_date_training,
                                       BLEU, tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve],
                                       BLEU, afficher_performance,
                                       BLEU, athletes[num_athletes].trainings[i].position);
                                #endif
                            } else {
                                #if defined(_WIN32)
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf("Nom de l'athlete ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", athletes[num_athletes].name);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", date de l'entrainement: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", display_date_training);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", epreuve: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s", tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve]);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                printf(", perf.: ");
                                SetConsoleTextAttribute(hConsole, BLEU);
                                printf("%s\n", afficher_performance);
                                SetConsoleTextAttribute(hConsole, BLANC);
                                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                                printf("Nom de l'athlete \033[%dm%s\033[m, date de l'entrainement: \033[%dm%s\033[m, epreuve: \033[%dm%s\033[m, perf.: \033[%dm%s\033[m\n",
                                       BLEU, athletes[num_athletes].name,
                                       BLEU, display_date_training,
                                       BLEU, tabEpreuves[athletes[num_athletes].trainings[i].type_epreuve],
                                       BLEU, afficher_performance);
                                #endif
                            }
                        }
                    }
                }
        }
        num_athletes++;
    }
}