//
// Created by mathe on 08/06/2023.
//

#ifndef PROJETFINANNEE_FONCTION_H
#define PROJETFINANNEE_FONCTION_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

struct Film {
    char* realisateur;
    char* titre;
    int minutes;
    char* category;
    struct Film* left;
    struct Film* right;
};

struct FilmMax {
    struct Film* realisateurMax;
    int nombreMax;
};

struct Film* LectureLigne(char* ligne);
struct Film* buildFilmTree(char* fileName, int a);
struct Film* insertFilm(struct Film* root, struct Film* film, int a);

void LectureRequest(struct Film* FilmTreeTitre, struct Film* FilmTreeRealisateur, struct Film* FilmTreeDuree, struct FilmMax* realisateurMax);
void recherche(struct Film* FilmTreeTitre, struct Film* FilmTreeRealisateur, struct Film* FilmTreeDuree, char* fonction, char* valeur, FILE* resultFile);
void rechercheRealisateur(struct Film* FilmTreeRealisateur, char* valeur, FILE* resultFile);
void rechercheDuree(struct Film* FilmTreeDuree, char* valeur, FILE* resultFile);
void rechercheTitre(struct Film* FilmTreeTitre, char* valeur, FILE* resultFile);
void deleteFilmTree(struct Film* root);
void afficherArbre(struct Film* root, int a, FILE* resultFile);

struct FilmMax* CalculerMax(struct Film* FilmTreeRealisateur);
void ParcourirFilms(struct Film* FilmTreeRealisateur, struct FilmMax* Info);
int CompterFilmsRacine(struct Film* FilmTreeRealisateur, const char* Realisateur);
bool shutdown();


#endif //PROJETFINANNEE_FONCTION_H
