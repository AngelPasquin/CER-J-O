//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Gestion des écritures et des lectures des données de performances des entraînements des athlètes
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

#include "common.h"
#include "manageAthletesData.h"

// Nom du repertoire contenant les données de performances des entraînements des athlètes
const char *directoryData = "./data/";
// Extension du nom des fichiers
const char *extensionFilename = ".txt";

// Tableau contenant les performances des athlètes pour les différents entraînements
Athlete athletes[MAX_ATHLETES];

// Tableau contenant les libellés des épreuves, ce tableau est utilisé pour l'affichage
char tabEpreuves[][20] = {
        "100m",
        "400m",
        "5000m",
        "marathon",
        "relais 4x400m",
};

//
// Fonction: int enregistrerPerformancesEntrainementsAthletes()
// Description: Enregistre dans le répertoire "./data" les performances des entraînements d'un athlète
//
int enregistrerPerformancesEntrainementsAthletes() {
    FILE *file;
    char file_name[MAX_NAME_LENGTH] = {0};
    char athlete_name[MAX_NAME_LENGTH] = {0};
    Training training;
    long choixEpreuve = 0;
    int position = 0;
    bool isNameChosen = false;
    bool isRaceChosen = false;
    bool isPerfChosen = false;
    bool isPositionChosen = false;
    int num_training = 0;
    bool isTabRetrie = false;

    // Choisir l'athlète
    do {
        printf("Nom de l'athlete: ");

        // Récupérer le nom de l'athlète
        lireChaine(athlete_name, MAX_NAME_LENGTH);
        if (strcmp(athlete_name,"") != 0) {
            isNameChosen = true;
        } else {
            printf("Valeur non valide, veuillez reessayer !\n");
        }
    } while(isNameChosen == false);

    do {
        printf("Date (format JJ/MM/AAAA) : ");

        // Récupérer la date
        training.date = lireDate();
    } while(training.date == 0);

    isRaceChosen = false;
    do {
        printf("Type d'epreuve:\n");
        printf("\t(1) 100m\n");
        printf("\t(2) 400m\n");
        printf("\t(3) 5000m\n");
        printf("\t(4) Marathon\n");
        printf("\t(5) Relais 4*400m\n");
        printf("\tChoix: ");

        // Récupérer le type d"épreuve
        choixEpreuve = lireLong();

        switch (choixEpreuve) {
            case 1:
                training.type_epreuve = RACE100M;
                isRaceChosen = true;
                break;
            case 2:
                training.type_epreuve = RACE400M;
                isRaceChosen = true;
                break;
            case 3:
                training.type_epreuve = RACE5000M;
                isRaceChosen = true;
                break;
            case 4:
                training.type_epreuve = RACEMARATHON;
                isRaceChosen = true;
                break;
            case 5:
                training.type_epreuve = RACE4X400MRELAY;
                isRaceChosen = true;
                break;
            default:
                printf("Choix non valide, veuillez reessayer !\n");
                break;
        }
    } while(isRaceChosen == false);

    isPerfChosen = false;
    do {
        // Suivant le type de l'épreuve le format de saisie de la performance est différent
        switch (choixEpreuve) {
            case 1:
                // 100m
                printf("Performance (format SS.mm): ");
                training.time = lirePerformanceS();
                break;
            case 2:
                // 400m
                printf("Performance (format MM:SS.mm): ");
                training.time = lirePerformanceM();
                break;
            case 3:
                // 5000m
                printf("Performance (format MM:SS.mm): ");
                training.time = lirePerformanceM();
                break;
            case 4:
                // Marathon
                printf("Performance (format HH:MM:SS.mm): ");
                training.time = lirePerformanceL();
                break;
            case 5:
                // Relais 4*400m
                printf("Performance (format MM:SS.mm): ");
                training.time = lirePerformanceM();
                break;
        }

        if (training.time != 0.0) {
            isPerfChosen = true;
        } else {
            printf("Valeur non valide, veuillez reessayer !\n");
        }
    } while(isPerfChosen == false);

    // Cas particulier de l'épreuve de relais 4*400m nécessitant la saisie de la position de l'athlète dans la course
    if (training.type_epreuve == RACE4X400MRELAY) {
        do {
            printf("Position (1-4): ");

            // Récupérer la position de l'athlète dans la course
            position = (int)lireLong();
            if (position >=1 && position <=4) {
                isPositionChosen = true;
            } else {
                printf("Valeur non valide, veuillez reessayer !\n");
            }
        } while(isPositionChosen == false);
        training.position = position;
    } else {
        training.position = 0;
    }

    // Ajouter l'entraînement dans le tableau
    int num_athletes = 0;
    bool athlete_found = false;

    // Rechercher le nom de l'athlète
    while (strcmp(athletes[num_athletes].name, "") != 0 && !athlete_found)  {
        if (strcmp(athletes[num_athletes].name, athlete_name) == 0)
        {
            athlete_found = true;
        }
        else {
            num_athletes++;
        }
    }

    // Si l'athlète n'est pas trouvé dans le tableau alors ajouter son nom
    if (athlete_found == false) {
        strcpy(athletes[num_athletes].name, athlete_name);
    }

    // Ajouter la performance dans le tableau
    if (num_athletes < MAX_ATHLETES) {
        num_training = athletes[num_athletes].number_trainings;

        athletes[num_athletes].trainings[num_training].date = training.date;
        athletes[num_athletes].trainings[num_training].type_epreuve = training.type_epreuve;
        athletes[num_athletes].trainings[num_training].time = training.time;
        athletes[num_athletes].trainings[num_training].position = training.position;

        athletes[num_athletes].number_trainings = num_training + 1;
    }

    // Vérifier si la date saisie est supérieure ou égale à la dernière date saisie
    if (num_training > 0) {
        if (athletes[num_athletes].trainings[num_training -1].date > athletes[num_athletes].trainings[num_training].date) {
            // Retrier le tableau des entrainements
            triRapideDateEntrainements(athletes[num_athletes].trainings, 0, athletes[num_athletes].number_trainings-1);
            // Le tableau a été retrié
            isTabRetrie = true;
        }
    }

    // Vérifier si le répertoire existe
    DIR *d;
    d = opendir(directoryData);
    if (d == NULL) // Si le répertoire n'existe, alors il est nécessaire de le créer
    {
        printf("Creer un repertoire %s\n", directoryData);
        #if defined(_WIN32)
        if (mkdir(directoryData) == -1) {
            printf("Impossible de creer un repertoire %s\n", directoryData);
            exit(1);
        }
        #elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
        if (mkdir(directoryData, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
            printf("Impossible de creer le repertoire %s\n", directoryData);
            exit(1);
        }
        #endif
    }

    strcpy(file_name, directoryData);
    strcat(file_name, athlete_name);
    strcat(file_name, extensionFilename);

    // Si tableau retrié
    if (isTabRetrie) {
        // Ouverture du flux en écriture. Si le fichier existe, il sera alors écrasé. Sinon le fichier sera créé.
        file = fopen(file_name, "w");

        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier %s\n", athlete_name);
            return (-1);
        }

        // Ecriture dans le fichier
        for (int i = 0; i <= num_training; i++) {
            fprintf(file, "%lu;", athletes[num_athletes].trainings[i].date);
            fprintf(file, "%d;", athletes[num_athletes].trainings[i].type_epreuve);
            fprintf(file, "%.2f;", athletes[num_athletes].trainings[i].time);
            fprintf(file, "%d\n", athletes[num_athletes].trainings[i].position);
        }
    } else {
        // Ouverture du flux en mode ajout. Si le fichier n'existe pas, il sera alors créé. Sinon, son contenu sera conservé et la position courante sera à la fin du fichier.
        file = fopen(file_name, "a");

        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier %s\n", athlete_name);
            return (-1);
        }
        fprintf(file, "%lu;", athletes[num_athletes].trainings[num_training].date);
        fprintf(file, "%d;", athletes[num_athletes].trainings[num_training].type_epreuve);
        fprintf(file, "%.2f;", athletes[num_athletes].trainings[num_training].time);
        fprintf(file, "%d\n", athletes[num_athletes].trainings[num_training].position);
    }
    fclose(file);

    printf("Performance et entrainement de %s ont ete enregistrees dans le fichier %s\n", athlete_name, file_name);

    return(0);
}

//
// Fonction : int chargerPerformancesEntrainementsAthletes()
// Description : Lecture des données des fichiers de performances des entraînements des athlètes et chargement en mémoire
//
int chargerPerformancesEntrainementsAthletes() {
    char athlete_name[MAX_NAME_LENGTH];
    int num_athletes = 0;

    DIR *d;
    struct dirent *dir;
    FILE *file;
    // Chemin complet d'accès au fichier
    char full_path[100] = {0};
    char entrainement[100] = {0};
    const char * separators = ";";
    int num_training = 0;

    // Ouverture du répertoire
    d = opendir(directoryData);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // Vérifie s'il s'agit d'un fichier standard
            if(strcmp(dir->d_name, ".") !=0 && strcmp(dir->d_name, "..") !=0){
                full_path[0]='\0';
                strcat(full_path, directoryData);
                strcat(full_path,dir->d_name);

                // Supprimer ".txt" du fichier nom athlète
                size_t size_athlete_name = strlen(dir->d_name);
                if (size_athlete_name > 4) {
                    strncpy(athlete_name, dir->d_name, size_athlete_name - 4);
                    athlete_name[size_athlete_name - 4]= '\0';
                }
                else {
                    return 1;
                }

                // Si le fichier existe
                if (existanceFichier(full_path)) {
                    file = fopen(full_path, "r");

                    strcpy(athletes[num_athletes].name, athlete_name);
                    num_training = 0;

                    // Récupération des enregistrements des performances, récupération des différentes données et chargement dans le tableau "athletes"
                    while (fgets(entrainement, 100, file) != NULL) {
                        char *strToken = strtok(entrainement, separators);

                        if (strToken != NULL) {
                            // Récupération de la date
                            athletes[num_athletes].trainings[num_training].date = (unsigned long) strtol(strToken, NULL, 10);
                        }

                        strToken = strtok(NULL, separators);
                        if (strToken != NULL) {
                            // Récupération du type d'épreuve
                            athletes[num_athletes].trainings[num_training].type_epreuve = (int) strtol(strToken, NULL, 10);
                        }

                        strToken = strtok(NULL, separators);
                        if (strToken != NULL) {
                            // Récupération de la performance
                            athletes[num_athletes].trainings[num_training].time = strtof(strToken, NULL);
                        }

                        strToken = strtok(NULL, separators);
                        if (strToken != NULL) {
                            // Récupération de la position (relais 4*400m)
                            athletes[num_athletes].trainings[num_training].position = (int) strtol(strToken, NULL, 10);
                        }

                        num_training++;
                    }

                    athletes[num_athletes].number_trainings = num_training;

                    // Fermeture du fichier
                    fclose(file);
                } else {
                    return 1;
                }

                num_athletes++;
            }
        }
        // Fermeture du répertoire
        closedir(d);
        printf("Donnees athletes chargees !\n");
    } else {
        printf("Repertoire non trouve !\n");
    }
    return 0;
}