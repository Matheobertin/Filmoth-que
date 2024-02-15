#include "fonction.h"
//Initialisaton des structures
struct Film* FilmTreeTitre;
struct Film* FilmTreeRealisateur;
struct Film* FilmTreeDuree;

int main() {
    //Ouverture de la base en plusieurs exemplaire pour tous les arbres différents
    FilmTreeTitre = buildFilmTree("web.isen-ouest.fr_moodle_pluginfile.php_69214_mod_resource_content_0_BD_medium.txt",1);
    FilmTreeRealisateur = buildFilmTree("web.isen-ouest.fr_moodle_pluginfile.php_69214_mod_resource_content_0_BD_medium.txt",2);
    FilmTreeDuree = buildFilmTree("web.isen-ouest.fr_moodle_pluginfile.php_69214_mod_resource_content_0_BD_medium.txt",3);

    //Verification si l'arbre a bien été créé
    if (FilmTreeTitre == NULL) {
        printf("Erreur lors de la construction de l'arbre des films.\n");
        return 1;
    }

    //Verification si l'arbre a bien été créé
    if (FilmTreeRealisateur == NULL) {
        printf("Erreur lors de la construction de l'arbre des films.\n");
        return 1;
    }

    //Verification si l'arbre a bien été créé
    if (FilmTreeDuree == NULL) {
        printf("Erreur lors de la construction de l'arbre des films.\n");
        return 1;
    }

    struct FilmMax* realisateurMax = CalculerMax(FilmTreeRealisateur);
    if (realisateurMax != NULL) {
        printf("Directeur ayant réalisé le plus de films : %s avec %d Films\n", realisateurMax->realisateurMax->realisateur, realisateurMax->nombreMax);
    }

    //Boucle principal
    while (shutdown()){
        LectureRequest(FilmTreeTitre, FilmTreeRealisateur, FilmTreeDuree,realisateurMax);
    }

    //Free de tous les arbres
    deleteFilmTree(FilmTreeTitre);
    deleteFilmTree(FilmTreeRealisateur);
    deleteFilmTree(FilmTreeDuree);
    printf("Tout a bien été supprimé\n");
    return 0;
}