#include "fonction.h"

//Fonction pour lire la requete envoyé par le client
void LectureRequest(struct Film* FilmTreeTitre, struct Film* FilmTreeRealisateur, struct Film* FilmTreeDuree, struct FilmMax* realisateurMax){
    //Ouvrir le fichier en mode lecture
    FILE *file = fopen("request.txt", "r");
    if (file == NULL) {
        //printf("Impossible d'ouvrir le fichier request.txt.\n");
        return;
    }
    //On supprime tous les anciens .txt
    remove("../../projetfrontv3/result.txt");
    remove("../../projetfrontv3/ready.txt");

    //Lire la ligne contenant les informations
    char ligne[100];

    //Verification si request.txt est bien rempli
    if (fgets(ligne, sizeof(ligne), file) == NULL) {
        printf("Erreur lors de la lecture des informations dans le fichier.\n");
        fclose(file);
        return;
    }

    //Extraire les informations à partir de la ligne et alloue de la mémoire pour stocker les informations
    char *fonction = strdup(strtok(ligne, ";"));
    char *valeur = strdup(strtok(NULL, ";"));

    if(valeur == NULL){ //Vérification si une valeur est rentrée
        return;
    }

    //Ouvre le fichier de résultat en mode écriture
    FILE *resultFile = fopen("../../projetfrontv3/result.txt", "w");

    //Verification si result.txt s'ouvre bien
    if (resultFile == NULL) {
        printf("Impossible d'ouvrir le fichier result.txt pour l'enregistrement des résultats.\n");
        fclose(file);
        return;
    }
    clock_t start = clock();

    //Appel de la fonction recherche
    recherche(FilmTreeTitre, FilmTreeRealisateur, FilmTreeDuree, fonction, valeur, resultFile);

    clock_t end = clock();

    //Calcul du temps de recherche, d'écriture dans le fichier
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Temps de recherche : %f secondes.\n", cpu_time_used);

    //Ecris dans le result.txt le temps de recherche et d'écriture
    fprintf(resultFile,"%f;\n", cpu_time_used);
    //Ecris dans le result.txt le realisateur ayant fait le plus de film et le nombre de films
    fprintf(resultFile,"%s;%d;\n", realisateurMax->realisateurMax->realisateur, realisateurMax->nombreMax);

    //Ouvre le fichier de résultat en mode écriture
    FILE *file1 = fopen("../../projetfrontv3/ready.txt", "w");

    //Libérer la mémoire et fermer les fichiers
    free(fonction);
    free(valeur);
    fclose(file);
    fclose(file1);
    fclose(resultFile);
    remove("request.txt");
}

//Fonction recherche qui va renvoyer par la suite vers les autres fonctions demandées
void recherche(struct Film* FilmTreeTitre, struct Film* FilmTreeRealisateur, struct Film* FilmTreeDuree, char* fonction, char* valeur, FILE* resultFile) {
    //comparaison entre la fonction du request (la catégorie que le client cherche) et les différentes valeurs pour les recherches
    if (strcmp(fonction, "nom") == 0) {
        rechercheTitre(FilmTreeTitre, valeur, resultFile); //renvoie vers la fonction rechercheNom
    } else if (strcmp(fonction, "directeur") == 0) {
        rechercheRealisateur(FilmTreeRealisateur, valeur, resultFile); //renvoie vers la fonction rechercheRealisateur
    } else if (strcmp(fonction, "duree") == 0) {
        rechercheDuree(FilmTreeDuree, valeur, resultFile); //renvoie vers la fonction rechercheDuree
    }
}

//Fonction rechercheRealisateur qui remplir le result.txt avec les valeurs en fonction des realisateurs
void rechercheRealisateur(struct Film* FilmTreeRealisateur, char* valeur, FILE* resultFile) { //Correction de la fonction en partie écrite par ChatGPT
    //Verification si l'arbre est bien remplit
    if (FilmTreeRealisateur == NULL) {
        return;
    }

    //Convertir les chaînes en minuscules pour une comparaison sans problème de majuscule
    //Création d'une copie de chaques (FilmTreeRealisateur->realisateur)
    /*char tab[strlen(FilmTreeRealisateur->realisateur)];
    for (int i = 0; FilmTreeRealisateur->realisateur[i] != '\0'; i++) {
        tab[i] = tolower(FilmTreeRealisateur->realisateur[i]); //tolower met en minuscule chaque lettre
    }
    tab[strlen(FilmTreeRealisateur->realisateur)] = '\0';*/

    //Convertir les chaînes en minuscules pour une comparaison sans problème de majuscule
    //Création d'une copie de chaques (valeur)
    /*for (int i = 0; valeur[i] != '\0'; i++) {
        valeur[i] = tolower(valeur[i]);
    }
    valeur[strlen(valeur)] = '\0';*/

    int cmp = strncasecmp(FilmTreeRealisateur->realisateur, valeur,strlen(valeur)); //comparaison entre tab et valeur pour voir ou placer valeur

    if (cmp >= 0) {
        if (cmp == 0) {
            //printf("%s;%s;%d;%s\n", FilmTreeRealisateur->realisateur, FilmTreeRealisateur->titre, FilmTreeRealisateur->minutes, FilmTreeRealisateur->category);
            fprintf(resultFile, "%s;%s;%d;%s\n", FilmTreeRealisateur->realisateur, FilmTreeRealisateur->titre, FilmTreeRealisateur->minutes, FilmTreeRealisateur->category);
        }
        rechercheRealisateur(FilmTreeRealisateur->left, valeur, resultFile);
    } else {
        rechercheRealisateur(FilmTreeRealisateur->right, valeur, resultFile);
    }
}

//Fonction rechercheNom qui remplir le result.txt avec les valeurs en fonction des noms
void rechercheTitre(struct Film* FilmTreeTitre, char* valeur, FILE* resultFile) {
    //Verification si l'arbre est bien remplit
    if (FilmTreeTitre == NULL) {
        return;
    }

    //Convertir les chaînes en minuscules pour une comparaison sans problème de majuscule
    //Création d'une copie de chaques (FilmTreeRealisateur->realisateur)
    /*char tab[strlen(FilmTreeTitre->titre)];
    for (int i = 0; FilmTreeTitre->titre[i] != '\0'; i++) {
        tab[i] = tolower(FilmTreeTitre->titre[i]);
    }
    tab[strlen(FilmTreeTitre->titre)] = '\0';*/

    //Convertir les chaînes en minuscules pour une comparaison sans problème de majuscule
    //Création d'une copie de chaques (valeur)
    /*for (int i = 0; valeur[i] != '\0'; i++) {
        valeur[i] = tolower(valeur[i]);
    }*/

    //strncasecmp fait une comparaison ou selon lui 'abc' == 'ABC' donc plus besoin de mettre en minuscule
    int cmp = strncasecmp(FilmTreeTitre->titre, valeur, strlen(valeur)); //comparaison entre tab et valeur pour voir ou placer valeur

    if (cmp >= 0) {
        if (cmp == 0) {
            //printf("%s;%s;%d;%s\n", FilmTreeTitre->realisateur, FilmTreeTitre->titre, FilmTreeTitre->minutes, FilmTreeTitre->category);
            fprintf(resultFile, "%s;%s;%d;%s\n", FilmTreeTitre->realisateur, FilmTreeTitre->titre, FilmTreeTitre->minutes, FilmTreeTitre->category);
        }
        rechercheTitre(FilmTreeTitre->left, valeur, resultFile);
    }else{
        rechercheTitre(FilmTreeTitre->right, valeur, resultFile);
    }
}

//Fonction rechercheNom qui remplir le result.txt avec les valeurs en fonction des noms
void rechercheDuree(struct Film* FilmTreeDuree, char* valeur, FILE* resultFile) {
    //Verification si l'arbre est bien remplit
    if (FilmTreeDuree == NULL) {
        return;
    }

    int minutes = atoi(valeur);

    if (FilmTreeDuree->minutes == minutes) { //comparaison entre FilmTreeDuree->minutes et minutes pour voir ou placer minutes
        //printf("%s;%s;%d;%s\n", FilmTreeDuree->realisateur, FilmTreeDuree->titre, FilmTreeDuree->minutes, FilmTreeDuree->category);
        fprintf(resultFile, "%s;%s;%d;%s\n", FilmTreeDuree->realisateur, FilmTreeDuree->titre, FilmTreeDuree->minutes, FilmTreeDuree->category);
    }

    rechercheDuree(FilmTreeDuree->left, valeur, resultFile);
    rechercheDuree(FilmTreeDuree->right, valeur, resultFile);
}

//Fonction pour trouver le realisateur ayant fait le plus de film et le nombre de film
struct FilmMax* CalculerMax(struct Film* FilmTreeRealisateur) {
    struct FilmMax* Info = malloc(sizeof(struct FilmMax));
    Info->realisateurMax = NULL;
    Info->nombreMax = 0;

    ParcourirFilms(FilmTreeRealisateur, Info);

    return Info;
}

//Fonction pour parcourir l'arbre et comparer chaque réalisateur entre eu jusqu'à la fin pour avoir celui qui a fait le plus de film
void ParcourirFilms(struct Film* FilmTreeRealisateur, struct FilmMax* Info) { //Fonction en partie écrite par ChatGPT
    //Verification si l'arbre est bien remplit
    if (FilmTreeRealisateur == NULL) {
        return;
    }

    //Verifier si le realisateur actuel a un nombre de films superieur au maximum actuel
    int nombreFilms = CompterFilmsRacine(FilmTreeRealisateur, FilmTreeRealisateur->realisateur);
    if (nombreFilms > Info->nombreMax) {
        Info->nombreMax = nombreFilms;
        Info->realisateurMax = FilmTreeRealisateur;
    }

    ParcourirFilms(FilmTreeRealisateur->left, Info);
    ParcourirFilms(FilmTreeRealisateur->right, Info);
}

//Fonction pour compter le nombre de film en fonction du realisateur
int CompterFilmsRacine(struct Film* FilmTreeRealisateur, const char* realisateur) { //Fonction en partie écrite par ChatGPT
    //Verification si l'arbre est bien remplit
    if (FilmTreeRealisateur == NULL) {
        return 0;
    }

    int count = 0;
    if (strcmp(FilmTreeRealisateur->realisateur, realisateur) == 0) {
        count++;
    }

    count += CompterFilmsRacine(FilmTreeRealisateur->left, realisateur);
    count += CompterFilmsRacine(FilmTreeRealisateur->right, realisateur);

    return count;
}
