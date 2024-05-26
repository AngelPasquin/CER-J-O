//
// Cree par Angel PASQUIN le 13/05/2024
//
// Description: Déclaration des valeurs, structures et fonctions communes
//

#ifndef COMMON_H
#define COMMON_H

#define MAX_ATHLETES 100
#define MAX_NAME_LENGTH 50
#define DATE_LENGTH 11 // DD/MM/YYYY
#define MAX_TRAININGS 100

#if defined(_WIN32)
#include <windows.h>
#endif

// Définition des couleurs
#if defined(_WIN32)
#define BLANC 7
#define BLEU 9
#define ROUGE 12
#define VERT 10
#define JAUNE 14
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__) || defined(__CYGWIN__)
#define BLANC 0
#define BLEU 94
#define ROUGE 91
#define VERT 92
#define JAUNE 93
#endif

// Enumeration des types d'épreuves
typedef enum {RACE100M, RACE400M, RACE5000M, RACEMARATHON, RACE4X400MRELAY, ALLRACES} TypeEpreuve;

// Structure entraînement
typedef struct {
    unsigned long date;
    TypeEpreuve type_epreuve;
    float time;
    int position;
} Training;

// Structure athlète
typedef struct {
    char name[MAX_NAME_LENGTH];
    Training trainings[MAX_TRAININGS];
    int number_trainings;
} Athlete;

// Structure performances athlètes
typedef struct {
    char name[MAX_NAME_LENGTH];
    float mean_time;
} PerfAthlete;

unsigned long lireDate();
int afficherDate(unsigned long dateLong, char * dateStr);
bool existanceFichier(const char *filename);
int lireChaine(char *chaine, int longueur);
long lireLong();
float lirePerformanceS();
float lirePerformanceM();
float lirePerformanceL();
void triRapideDateEntrainements(Training tab[], int first, int last);
void triRapidePerfJO(PerfAthlete tab[], int first, int last);
int afficherPerformance(float performance, char * performanceStr);

#endif //COMMON_H