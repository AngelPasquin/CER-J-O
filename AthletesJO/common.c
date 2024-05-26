//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Fonctions communes
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

//
// Fonction: char * supprimerEspacesChaineCaract(char *string)
// Description: Suppression des caractères espaces
//
char * supprimerEspacesChaineCaract(char *string)
{
    char *p1;
    char *p2;

    p1 = string;
    p2 = string;
    while (*p1 && (*p1 == ' ' || *p1 == '\t')) {
        ++p1;
    }
    while (*p1 != '\0') {
        while (*p1 && (*p1 == ' ' || *p1 == '\t') && ((*(p1 + 1) && (*(p1 + 1) == ' ' || *(p1 + 1) == '\t')) || !(*(p1 + 1)))) {
            ++p1;
        }
        *p2++ = *p1++;
    }
    *p2 = '\0';
    return (string);
}

//
// Fonction: unsigned long lireDate()
// Description: Permet la saisie ce la date (format: DD/MM/YYYY) , vérifie si la date est valide et la retourne en format unsigned long (format : YYYYMMDD)
//
unsigned long lireDate()
{
    bool result = false;
    int dd = 0;
    int mm = 0;
    int yy = 0;
    const char * separators = "/";
    long resultatDate = 0;
    char dateTexte[DATE_LENGTH] = {0};

    if (lireChaine(dateTexte, DATE_LENGTH)) {
        char *strToken = strtok(dateTexte, separators);
        // Récupération du jour (JJ)
        if (strToken != NULL) {
            dd = (int) strtol(strToken, NULL, 10);
        } else {
            dd = 0;
        }

        // Récupération du mois (MM)
        strToken = strtok(NULL, separators);
        if (strToken != NULL) {
            mm = (int) strtol(strToken, NULL, 10);
        } else {
            mm = 0;
        }

        // Récupération de l'année (AAAA)
        strToken = strtok(NULL, separators);
        if (strToken != NULL) {
            yy = (int) strtol(strToken, NULL, 10);
        } else {
            yy = 0;
        }

        // Vérification de l'année
        if (yy >= 1900 && yy <= 9999) {
            // Vérification du mois
            if (mm >= 1 && mm <= 12) {
                // Vérificatino des jours
                if ((dd >= 1 && dd <= 31) &&
                    (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)) {
                    result = true;
                } else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) {
                    result = true;
                } else if ((dd >= 1 && dd <= 28) && (mm == 2)) {
                    result = true;
                } else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0))) {
                    result = true;
                } else {
                    printf("Le jour n'est pas valide\n");
                    result = false;
                }
            } else {
                printf("Le mois n'est pas valide\n");
                result = false;
            }
        } else {
            printf("La date n'est pas valide\n");
            result = false;
        }

        // Si la date est correcte
        if (result == true) {
            resultatDate = yy * 10000 + mm * 100 + dd;
        } else {
            resultatDate = 0;
        }
    }
    else {
        resultatDate = 0;
    }

    return resultatDate;
}

//
// Fonction: int afficherDate(unsigned long dateLong, char * dateStr)
// Description: Retourne la date au format "JJ/MM/AAAA" pour affichage
//
int afficherDate(unsigned long dateLong, char * dateStr) {
    int dd = 0;
    int mm = 0;
    int yy = 0;

    // Calcul année (AAAA)
    yy = (int)dateLong/10000;

    // Calcul du mois (MM)
    mm = (int)(dateLong-yy*10000)/100;

    // Calcul du jour (JJ)
    dd = (int)dateLong-(yy*10000)-(mm*100);

    // Met en forme la date au format "JJ/MM/AAAA"
    sprintf(dateStr, "%02d/%02d/%04d", dd, mm, yy);

    return 0;
}

//
// Fonction: bool existanceFichier(const char *filename)
// Description: Vérifie si le fichier existe
//
bool existanceFichier(const char *filename)
{
    // Ouvrir le fichier
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;

    if (fp != NULL)
    {
        is_exist = true;
        // Fermer le fichier
        fclose(fp);
    }
    return is_exist;
}

//
// Fonction: void viderBuffer()
// Description: Vide le buffer de saisie de caractères de l'entrée standard (clavier)
//
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//
// Fonction: int lireChaine(char *chaine, int longueur)
// Description: Permet la saisie d'une chaîne de caractères
//
int lireChaine(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }

        // Suppression des caractères espaces multiples
        supprimerEspacesChaineCaract(chaine);
        return 1;
    }
    else
    {
        // Suppression des caractères espaces multiples
        supprimerEspacesChaineCaract(chaine);
        viderBuffer();
        return 0;
    }
}

//
// Fonction:
// Description: Permet la saisie d'une valeur de type "long"
//
long lireLong()
{
    char *err_ptr = NULL;
    char nombreTexte[10] = {0};
    long result = 0;

    if (lireChaine(nombreTexte, 10))
    {
        // Si la lecture du texte est correcte, convertir le nombre en "long" et le retourner
        result = strtol(nombreTexte, &err_ptr, 10);
        if (*err_ptr != '\0') {
            // Si problème de lecture, retourner 0
            return 0;
        }
        return result;
    }
    else
    {
        // Si problème de lecture, retourner 0
        return 0;
    }
}

//
// Fonction: float lirePerformanceS()
// Description: Lire performance format "SS.mm"
//
float lirePerformanceS()
{
    char *err_ptr = NULL;
    char nombreTexte[20] = {0}; // 20 caracteres
    float result = 0.0f;

    // Récupérer la chaîne de caractères saisie
    if (lireChaine(nombreTexte, 20))
    {
        // Si la lecture du texte est correcte, convertir le nombre en "float" et le retourner
        result = strtof(nombreTexte, &err_ptr);
        if (*err_ptr != '\0') {
            // Si problème de lecture, retourner 0.0f
            return 0.0f;
        }

        // Retourner performance
        return result;
    }
    else
    {
        // Si problème de lecture, retourner 0.0f
        return 0.0f;
    }
}

//
// Fonction: float lirePerformanceM()
// Description: Lire performance format "MM:SS.mm"
//
float lirePerformanceM()
{
    char *err_ptr = NULL;
    char nombreTexte[20] = {0}; // 20 caracteres
    int MM = 0;
    float SSmm = 0.0f;
    const char *separators = ":";
    float result = 0.0f;

    // Récupérer la chaîne de caractères saisie
    if (lireChaine(nombreTexte, 20))
    {
        char * strToken_debut = strtok (nombreTexte, separators);
        // Récupérer les minutes (MM)
        if (strToken_debut != NULL) {
            MM = (int)strtol(strToken_debut, &err_ptr, 10);
            if (*err_ptr != '\0') {
                return 0.0f;
            }
        } else {
            MM = 0;
        }

        // Récupérer les secondes et ms (SS.mm)
        strToken_debut = strtok (NULL, separators);
        if (strToken_debut != NULL) {
            SSmm = strtof(strToken_debut, &err_ptr);
            if (*err_ptr != '\0') {
                //puts("Erreur de saisie performance\n");
                return 0.0f;
            }
        } else {
            SSmm = 0.0f;
        }

        // Calculer valeur performance
        result = (float)MM*60+SSmm;

        // Retourner performance
        return result;
    }
    else
    {
        // Si problème, retourner 0.0f
        return 0.0f;
    }
}


//
// Fonction: lirePerformanceL
// Description: Lire performance format "HH:MM:SS.mm"
//
float lirePerformanceL()
{
    char *err_ptr = NULL;
    char nombreTexte[20] = {0}; // 20 caracteres
    int HH = 0;
    int MM = 0;
    float SSmm = 0.0f;
    const char *separators = ":";
    float result = 0.0f;

    if (lireChaine(nombreTexte, 20))
    {
        // If reading the text ok, convert the number to float and return it

        char * strToken_debut = strtok (nombreTexte, separators);
        // Récupérer heures (HH)
        if (strToken_debut != NULL) {
            HH = (int)strtol(strToken_debut, &err_ptr, 10);
            if (*err_ptr != '\0') {
                //puts("Erreur de saisie performance\n");
                return 0.0f;
            }
        } else {
            HH = 0;
        }

        // Récupérer minutes (MM)
        strToken_debut = strtok (NULL, separators);
        if (strToken_debut != NULL) {
            MM = (int)strtol(strToken_debut, &err_ptr, 10);
            if (*err_ptr != '\0') {
                return 0.0f;
            }
        } else {
            MM = 0;
        }

        // Récupérer secondes et ms (SS.mm)
        strToken_debut = strtok (NULL, separators);
        if (strToken_debut != NULL) {
            SSmm = strtof(strToken_debut, &err_ptr);
            if (*err_ptr != '\0') {
                //puts("Erreur de saisie performance\n");
                return 0.0f;
            }
        } else {
            SSmm = 0.0f;
        }

        // Calculer valeur performance
        result = (float)HH*3600+(float)MM*60+SSmm;

        // Retourner performance
        return result;
    }
    else
    {
        // If reading problem, return 0
        return 0.0f;
    }
}

//
// Fonction: void permuterEntrainements(Training *a, Training *b)
// Description: Fonction de permutation utilisée par le tri rapide pour le tableau des entraînements
//
void permuterEntrainements(Training *a, Training *b) {
    Training tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//
// Fonction: void triRapideDateEntrainements(Training tab[], int first, int last)
// Description: Fonction de tri rapide du tableau des entraînements
//
void triRapideDateEntrainements(Training tab[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i].date <= tab[pivot].date && i < last)
                i++;
            while(tab[j].date > tab[pivot].date)
                j--;
            if(i < j) {
                permuterEntrainements(&tab[i], &tab[j]);
            }
        }
        permuterEntrainements(&tab[pivot], &tab[j]);
        triRapideDateEntrainements(tab, first, j - 1);
        triRapideDateEntrainements(tab, j + 1, last);
    }
}


//
// Fonction: void permuterPerfJO(PerfAthlete *a, PerfAthlete *b)
// Description: Fonction de permutation utilisée par le tri rapide pour le classement des performances JO
//
void permuterPerfJO(PerfAthlete *a, PerfAthlete *b) {
    PerfAthlete tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//
// Fonction: void triRapidePerfJO(PerfAthlete tab[], int first, int last)
// Description: Fonction de tri rapide du tableau de classement des performances JO
//
void triRapidePerfJO(PerfAthlete tab[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i].mean_time <= tab[pivot].mean_time && i < last)
                i++;
            while(tab[j].mean_time > tab[pivot].mean_time)
                j--;
            if(i < j) {
                permuterPerfJO(&tab[i], &tab[j]);
            }
        }
        permuterPerfJO(&tab[pivot], &tab[j]);
        triRapidePerfJO(tab, first, j - 1);
        triRapidePerfJO(tab, j + 1, last);
    }
}

//
// Fonction: int afficherPerformance(float performance, char * performanceStr)
// Description: Fonction d'affichage des performances
//
int afficherPerformance(float performance, char * performanceStr) {
    int HH = 0;
    int MM = 0;
    float SSmm = 0.0f;

    HH = (int)performance/3600;
    MM = (int)performance/60;

    // Si existance heure, alors format "HH:MM:SS.mm"
    if (HH != 0) {
        MM = (int)((int)performance - (HH*3600))/60;
        SSmm = (float)performance - (float)(HH*3600) - (float)(MM*60);
        sprintf(performanceStr, "%d:%02d:%02.2f", HH, MM, SSmm);
    }
    else if (MM != 0) {
        // Si existance minute, alors format "MM:SS.mm"
        SSmm = performance - (float)(MM*60);
        sprintf(performanceStr, "%d:%02.2f", MM, SSmm);
    } else {
        // Sinon format "SS.mm"
        sprintf(performanceStr, "%.2f", performance);
    }
    return 0;
}