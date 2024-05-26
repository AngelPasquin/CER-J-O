//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Gestion des statistiques des performances des entraînements des athlètes
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "statistics.h"

// Tableau contenant les performances des athlètes pour les différents entraînements
extern Athlete athletes[MAX_ATHLETES];

// Tableau contenant les libellés des épreuves, ce tableau est utilisé pour l'affichage
extern char tabEpreuves[][20];

//
// Foncrtion: void performancesAthlete()
// Description: Affiche les statistiques de performances (meilleure, pire, moyenne) de l'athlète pour un type d'épreuve
//
void performancesAthlete() {
    #if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    char athlete_name[MAX_NAME_LENGTH] = {0};
    TypeEpreuve type_epreuve;
    long choixEpreuve = 0;
    bool isRaceChoosen = false;
    bool isNameChoosen = false;
    char afficher_meilleure_performance[20] = {0};
    char afficher_pire_performance[20] = {0};
    char afficher_moyenne_performance[20] = {0};

    // Choisir un athlète
    do {
        printf("Nom de l'athlete: ");
        lireChaine(athlete_name, MAX_NAME_LENGTH);
        if (strcmp(athlete_name,"") != 0) {
            isNameChoosen = true;
        } else {
            printf("Valeur non valide, veuillez ressayer !\n");
        }
    } while(isNameChoosen == false);

    // Choisir un type d'épreuve
    isRaceChoosen = false;
    do {
        printf("Type d'epreuve:\n");
        printf("(1) 100m\n");
        printf("(2) 400m\n");
        printf("(3) 5000m\n");
        printf("(4) Marathon\n");
        printf("(5) Relais 4*400m\n");
        printf("Choix: ");
        // Appel à la fonction permettant de saisir une valeur (type long)
        choixEpreuve = lireLong();

        switch (choixEpreuve) {
            case 1:
                type_epreuve = RACE100M;
                isRaceChoosen = true;
                break;
            case 2:
                type_epreuve = RACE400M;
                isRaceChoosen = true;
                break;
            case 3:
                type_epreuve = RACE5000M;
                isRaceChoosen = true;
                break;
            case 4:
                type_epreuve = RACEMARATHON;
                isRaceChoosen = true;
                break;
            case 5:
                type_epreuve = RACE4X400MRELAY;
                isRaceChoosen = true;
                break;
            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    } while(isRaceChoosen == false);

    int num_athletes = 0;
    bool athlete_found = false;
    float best_time = 0.0f;
    float worst_time = 0.0f;
    float mean_time = 0.0f;

    // Rechercher l'athlète dans le tableau "athletes"
    while (strcmp(athletes[num_athletes].name, "") != 0 && !athlete_found)  {
        if (strcmp(athletes[num_athletes].name, athlete_name) == 0)
        {
            int j = 0;

            // Additionner les temps (performances) en filtrant sur le type d'épreuve choisi
            for (int i = 0; i < athletes[num_athletes].number_trainings; i++) {
                if (athletes[num_athletes].trainings[i].type_epreuve == type_epreuve) {
                    if (athletes[num_athletes].trainings[i].time < best_time || best_time == 0.0) {
                        best_time = athletes[num_athletes].trainings[i].time;
                    }
                    if (athletes[num_athletes].trainings[i].time > worst_time || worst_time == 0.0) {
                        worst_time = athletes[num_athletes].trainings[i].time;
                    }
                    mean_time = mean_time + athletes[num_athletes].trainings[i].time;
                    j++;
                }
            }

            // S'il y a au moins une valeur, calculer la moyenne des performances
            if (j != 0) {
                mean_time = mean_time/(float)j;

                // Mise en forme de la meilleure performance pour affichage
                afficherPerformance(best_time, afficher_meilleure_performance);

                // Mise en forme de la pire performance pour affichage
                afficherPerformance(worst_time, afficher_pire_performance);

                // Mise en forme de la moyenne des performances pour affichage
                afficherPerformance(mean_time, afficher_moyenne_performance);

                #if defined(_WIN32)
                printf("Nom de l'athlete: ");
                SetConsoleTextAttribute(hConsole, BLEU);
                printf("%s", athletes[num_athletes].name);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", Epreuve: ");
                SetConsoleTextAttribute(hConsole, BLEU);
                printf("%s", tabEpreuves[type_epreuve]);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", Perf.[meilleure: ");
                SetConsoleTextAttribute(hConsole, VERT);
                printf("%s", afficher_meilleure_performance);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", pire: ");
                SetConsoleTextAttribute(hConsole, ROUGE);
                printf("%s", afficher_pire_performance);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", moyenne: ");
                SetConsoleTextAttribute(hConsole, BLEU);
                printf("%s", afficher_moyenne_performance);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf("]\n");
                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                printf("Nom de l'athlete: \033[%dm%s\033[m, Epreuve: \033[%dm%s\033[m, Perf.[meilleure: \033[%dm%s\033[m, pire: \033[%dm%s\033[m, moyenne: \033[%dm%s\033[m]\n",
                       BLEU, athletes[num_athletes].name,
                       BLEU, tabEpreuves[type_epreuve],
                       VERT, afficher_meilleure_performance,
                       ROUGE, afficher_pire_performance,
                       BLEU, afficher_moyenne_performance);
                #endif
            }
            else {
                printf("Pas de resultat pour cette epreuve !\n");
            }

            athlete_found = true;
        }
        else {
            num_athletes++;
        }
    }
    // Si l'athlète n'a pas été trouvé
    if (!athlete_found) {
        printf("Athlete %s introuvable !\n", athlete_name);
    }
}

//
// Fonction: void performancesJO()
// Description: Affiche le classement des athletes pour les JO pour un type d'épreuve donné
//
void performancesJO() {
    #if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    TypeEpreuve type_epreuve;
    // Classement athletes pour JO
    PerfAthlete athletesjo[MAX_ATHLETES];
    long choixEpreuve = 0;
    bool isRaceChoosen = false;
    char afficher_moyenne_performance[20] = {0};
    int indice_tab = 0;

    // Choisir le type d'épreuve
    isRaceChoosen = false;
    do {
        printf("Type d'epreuve:\n");
        printf("\t(1) 100m\n");
        printf("\t(2) 400m\n");
        printf("\t(3) 5000m\n");
        printf("\t(4) Marathon\n");
        printf("\t(5) Relais 4*400m\n");
        printf("\tChoix: ");
        // Appel à la fonction permettant de saisir une valeur (type long)
        choixEpreuve = lireLong();

        switch (choixEpreuve) {
            case 1:
                type_epreuve = RACE100M;
                isRaceChoosen = true;
                break;
            case 2:
                type_epreuve = RACE400M;
                isRaceChoosen = true;
                break;
            case 3:
                type_epreuve = RACE5000M;
                isRaceChoosen = true;
                break;
            case 4:
                type_epreuve = RACEMARATHON;
                isRaceChoosen = true;
                break;
            case 5:
                type_epreuve = RACE4X400MRELAY;
                isRaceChoosen = true;
                break;
            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    } while(isRaceChoosen == false);

    int num_athletes = 0;

    // Pour tous les athlètes
    while (strcmp(athletes[num_athletes].name, "") != 0)  {
        int j = 0;
        float mean_time = 0.0f;

        // Somme de toutes les performances de l'athlète pour le type d'epreuve recherche
        for (int i = 0; i < athletes[num_athletes].number_trainings; i++) {
            if (athletes[num_athletes].trainings[i].type_epreuve == type_epreuve) {
                mean_time = mean_time + athletes[num_athletes].trainings[i].time;
                j++;
            }
        }

        // S'il y a au moins une valeur de performance
        if (j != 0) {
            // Calculer la moyenne des performances
            mean_time = mean_time / (float) j;

            // Copier nom et moyenne perf.
            strcpy(athletesjo[indice_tab].name, athletes[num_athletes].name);
            athletesjo[indice_tab].mean_time = mean_time;

            // Incrémenter indice du tableau JO
            indice_tab++;
        }

        num_athletes++;
    }

    // Réaliser un tri du tableau des moyennes des athlètes pour ce type d'épreuve
    triRapidePerfJO(athletesjo, 0, indice_tab-1);

    int l = 0;
    bool stop = false;

    #if defined(_WIN32)
    printf("Classement des athletes pour l'epreuve: ");
    SetConsoleTextAttribute(hConsole, BLEU);
    printf("%s\n", tabEpreuves[type_epreuve]);
    SetConsoleTextAttribute(hConsole, BLANC);
    #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux_) || defined(__CYGWIN__)
    printf("Classement des athletes pour l'epreuve: \033[%dm%s\033[m\n", BLEU, tabEpreuves[type_epreuve]);
    #endif

    // Vérifie si aucun athlète n'a été trouvé
    if (indice_tab == 0) {
        printf("Personne n'a ete trouvee pour cette epreuve !\n");
        stop = true;
    }

    // Afficher le classement (3 premiers) pour l'épreuve choisie
    while (l < 3 && !stop) {
        // Mise en forme de la performance pour affichage
        afficherPerformance(athletesjo[l].mean_time, afficher_moyenne_performance);

        #if defined(_WIN32)
        SetConsoleTextAttribute(hConsole, VERT);
        printf("\t#%d", l+1);
        SetConsoleTextAttribute(hConsole, BLANC);
        printf(", nom athlete: ");
        SetConsoleTextAttribute(hConsole, BLEU);
        printf("%s", athletesjo[l].name);
        SetConsoleTextAttribute(hConsole, BLANC);
        printf(", moyenne perf.: ");
        SetConsoleTextAttribute(hConsole, VERT);
        printf("%s\n", afficher_moyenne_performance);
        SetConsoleTextAttribute(hConsole, BLANC);
        #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux_) || defined(__CYGWIN__)
        printf("\t\033[%dm#%d\033[m, nom athlete: \033[%dm%s\033[m, moyenne perf.: \033[%dm%s\033[m\n", VERT, l+1, BLEU, athletesjo[l].name, VERT, afficher_moyenne_performance);
        #endif
        l++;

        // Teste s'il reste encore des athlètes dans le tableau
        if (l > indice_tab-1) {
            stop = true;
        }
    }
}

//
// Fonction: void progressionAthlete()
// Description: Affiche la progression de l'athlète pour entre 2 dates d'entrainemnets
//
void progressionAthlete() {
    #if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    char athlete_name[MAX_NAME_LENGTH];
    TypeEpreuve type_epreuve;
    unsigned long starting_date;
    unsigned long ending_date;
    long choixEpreuve;
    bool isRaceChoosen = false;
    bool isNameChoosen = false;

    // Choisir athlète
    do {
        printf("Nom de l'athlete: ");
        lireChaine(athlete_name, MAX_NAME_LENGTH);
        if (strcmp(athlete_name,"") != 0) {
            isNameChoosen = true;
        } else {
            printf("Valeur non valide. Reessayer.\n");
        }
    } while(isNameChoosen == false);

    // Choisir type d'épreuve
    isRaceChoosen = false;
    do {
        printf("Type d'epreuve:\n");
        printf("(1) 100m\n");
        printf("(2) 400m\n");
        printf("(3) 5000m\n");
        printf("(4) Marathon\n");
        printf("(5) Relais 4*400m\n");
        printf("Choix: ");
        choixEpreuve = lireLong();
        switch (choixEpreuve) {
            case 1:
                type_epreuve = RACE100M;
                isRaceChoosen = true;
                break;
            case 2:
                type_epreuve = RACE400M;
                isRaceChoosen = true;
                break;
            case 3:
                type_epreuve = RACE5000M;
                isRaceChoosen = true;
                break;
            case 4:
                type_epreuve = RACEMARATHON;
                isRaceChoosen = true;
                break;
            case 5:
                type_epreuve = RACE4X400MRELAY;
                isRaceChoosen = true;
                break;
            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    } while(isRaceChoosen == false);

    do {
        printf("Date de debut (format JJ/MM/AAAA): ");
        starting_date = lireDate();
    } while(starting_date == 0);

    do {
        printf("Date de fin (format JJ/MM/AAAA): ");
        ending_date = lireDate();
    } while(ending_date == 0 || starting_date > ending_date);

    int num_athletes = 0;
    bool athlete_found = false;

    while (strcmp(athletes[num_athletes].name, "") != 0 && !athlete_found)  {
        if (strcmp(athletes[num_athletes].name, athlete_name) == 0)
        {
            // Affiche en bleu du nom de l'athlète
            #if defined(_WIN32)
            SetConsoleTextAttribute(hConsole, BLANC);
            printf("Nom de l'athlete: ");
            SetConsoleTextAttribute(hConsole, BLEU);
            printf("%s\n", athlete_name);
            SetConsoleTextAttribute(hConsole, BLANC);
            #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
            printf("Nom de l'athlete: \033[%dm%s\033[m\n", BLEU, athlete_name);
            #endif
            float starting_perf = 0.0f;
            float ending_perf =0.0f;

            for (int i = 0; i < athletes[num_athletes].number_trainings; i++) {
                if (athletes[num_athletes].trainings[i].type_epreuve == type_epreuve) {
                    if (athletes[num_athletes].trainings[i].date == starting_date) {
                        if (starting_perf == 0.0 || starting_perf > athletes[num_athletes].trainings[i].time) {
                            starting_perf = athletes[num_athletes].trainings[i].time;
                        }
                    }

                    if (athletes[num_athletes].trainings[i].date == ending_date) {
                        if (ending_perf == 0.0 || ending_perf > athletes[num_athletes].trainings[i].time) {
                            ending_perf = athletes[num_athletes].trainings[i].time;
                        }
                    }
                }
            }

            if (starting_perf == 0.0 || ending_perf == 0.0) {
                printf("Pas possible d'estimer perf. delta, car manque mesures de performances\n");
            }
            else {
                float delta_time = ending_perf - starting_perf;
                // Affichage en bleu des performances
                #if defined(_WIN32)
                SetConsoleTextAttribute(hConsole, BLANC);
                printf("\tPerf. de debut: ");
                SetConsoleTextAttribute(hConsole, BLEU);
                printf("%.2fs", starting_perf);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", Perf. de fin: ");
                SetConsoleTextAttribute(hConsole, BLEU);
                printf("%.2fs", ending_perf);
                SetConsoleTextAttribute(hConsole, BLANC);
                printf(", Delta perf.: ");
                #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                printf("\tPerf. de debut: \033[%dm%.2fs\033[m, Perf. de fin: \033[%dm%.2fs\033[m, Delta perf: ", BLEU, starting_perf, BLEU, ending_perf);
                #endif
                if (delta_time > 0) {
                    // Affichage en rouge du delta performance
                    #if defined(_WIN32)
                    SetConsoleTextAttribute(hConsole, ROUGE);
                    printf("+%.2fs\n", delta_time);
                    SetConsoleTextAttribute(hConsole, BLANC);
                    #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                    printf("\033[%dm+%.2fs\033[m\n", ROUGE, delta_time);
                    #endif
                } else {
                    // Affichage en vert du delta performance
                    #if defined(_WIN32)
                    SetConsoleTextAttribute(hConsole, VERT);
                    printf("%.2fs\n", delta_time);
                    SetConsoleTextAttribute(hConsole, BLANC);
                    #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
                    printf("\033[%dm%.2fs\033[m\n", VERT, delta_time);
                    #endif
                }
            }
            athlete_found = true;
        }
        else {
            num_athletes++;
        }
    }
    if (athlete_found == false) {
        printf("Athlete introuvable: %s\n", athlete_name);
    }
}

//
// Fonction: void visualiserStatistiques()
// Description: Gestion du menu des statistiques
//
void visualiserStatistiques() {
    long choix = 0;
    bool exit = false;

    while (!exit) {
        printf("Menu des statistiques:\n");
        printf("\t(1) Synthese des performances d'un athlete pour une epreuve donnee\n");
        printf("\t(2) Qui envoyer aux Jeux Olympiques : les trois meilleurs athletes d'une discipline\n");
        printf("\t(3) Progression de l'athlete entre deux dates pour une epreuve donnee\n");
        printf("\t(4) Quitter le menu des statistiques\n");
        printf("\tChoix: ");
        // Appel à la fonction permettant de saisir une valeur (type long)
        choix = lireLong();

        switch (choix) {
            case 1:
                // Appel à la fonction de consultation des performances des entrainements d'un athlete
                performancesAthlete();
                break;

            case 2:
                // Appel à la fonction de consultation du classement des athletes pour les JO
                performancesJO();
                break;

            case 3:
                // Appel à la fonction de consultation de la progression d'un athlete
                progressionAthlete();
                break;

            case 4:
                exit = true;
                break;

            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    }
}