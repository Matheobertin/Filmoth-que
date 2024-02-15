#include "fonction.h"

//Fonction pour récuperer les informations de la ligne précisée
struct Film* LectureLigne(char* ligne) {
    struct Film* film = malloc(sizeof(struct Film));
    film->realisateur = strdup(strtok(ligne, ";"));
    film->titre = strdup(strtok(NULL, ";"));
    film->minutes = atoi(strtok(NULL, ";"));
    film->category = strdup(strtok(NULL, ";"));
    return film;
}

//Création des différents arbres
struct Film* buildFilmTree(char* fileName, int a) { //Fonction en partie écrite par ChatGPT
    FILE* file = fopen(fileName, "r");

    //Verification si le fichier est bien présent
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", fileName);
        return NULL;
    }

    struct Film* root = NULL;
    char ligne[100];
    bool verification = false;
    clock_t start = clock();

    //Creation de l'arbre en fonction des titres
    if(a==1){
        while (fgets(ligne, sizeof(ligne), file) != NULL) {
            struct Film* film = LectureLigne(ligne);
            root = insertFilm(root, film, a);
            verification = true;
        }
    }

    //Creation de l'arbre en fonction des realisateurs
    if(a==2){
        while (fgets(ligne, sizeof(ligne), file) != NULL) {
            struct Film* film = LectureLigne(ligne);
            root = insertFilm(root, film, a);
            verification = true;
        }
    }

    //Creation de l'arbre en fonction des durees
    if(a==3){
        while (fgets(ligne, sizeof(ligne), file) != NULL) {
            struct Film* film = LectureLigne(ligne);
            root = insertFilm(root, film, a);
            verification = true;
        }
        //Possible affichage des arbres
        //FILE *resultTrie = fopen("trie_name.txt", "w");
        //afficherArbre(root,a,resultTrie);
    }

    clock_t end = clock();

    //Calcule du temps pour effectuer l'arbre
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (verification) {
        printf("Le tri de l'arbre est terminé.\n");
        printf("Temps de tri : %f secondes.\n", cpu_time_used);
    }else{
        printf("Le tri de l'arbre n'est pas fait.\n");
    }
    fclose(file);
    return root;
}

//Fonction pour inserer des films dans l'arbre selectionné
struct Film* insertFilm(struct Film* root, struct Film* film, int a) { //Fonction en partie écrite par ChatGPT
    if (root == NULL) {
        return film;
    }

    //Insertion en fonction du titre
    if (a == 1) {
        int cmp = strcmp(film->titre, root->titre); //comparaison entre le taille des titres pour effectuer le tri
        if (cmp < 0) {
            root->left = insertFilm(root->left, film, a);
        } else if (cmp > 0) {
            root->right = insertFilm(root->right, film, a);
        } else {
            root->left = insertFilm(root->left, film, a);
        }

        return root;
    }

    //Insertion en fonction du réalisateur
    if (a == 2) {
        int cmp = strcmp(film->realisateur, root->realisateur); //comparaison entre le taille (nom) des realisateur pour effectuer le tri
        if (cmp < 0) {
            root->left = insertFilm(root->left, film, a);
        } else if (cmp > 0) {
            root->right = insertFilm(root->right, film, a);
        } else {
            root->left = insertFilm(root->left, film, a);
        }

        return root;
    }

    //Insertion en fonction du temps
    if (a == 3) { //comparaison en fonction du temps
        if (film->minutes == root->minutes) {
            root->left = insertFilm(root->left, film, a);
        } else if (film->minutes < root->minutes) {
            root->left = insertFilm(root->left, film, a);
        } else {
            root->right = insertFilm(root->right, film, a);
        }

        return root;
    }

    return root;
}
//Fonction pour afficher l'arbre dans un .txt (utilisé pour verification du tri)
void afficherArbre(struct Film* root, int a, FILE* resultFile) {
    if (root == NULL) {
        return;
    }

    if (a == 1) {
        //Afficher le sous arbre gauche
        afficherArbre(root->left, a, resultFile);

        //Afficher le noeud courant
        printf("%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);
        fprintf(resultFile, "%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);

        //Afficher le sous arbre droit
        afficherArbre(root->right, a, resultFile);
    } else if (a == 2) {
        //Afficher le sous arbre gauche
        afficherArbre(root->left, a, resultFile);

        //Afficher le noeud courant
        printf("%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);
        fprintf(resultFile, "%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);

        //Afficher le sous arbre droit
        afficherArbre(root->right, a, resultFile);
    } else if (a == 3) {
        //Afficher le sous arbre gauche
        afficherArbre(root->left, a, resultFile);

        //Afficher le noeud courant
        printf("%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);
        fprintf(resultFile, "%s;%s;%d;%s\n", root->realisateur, root->titre, root->minutes, root->category);

        //Afficher le sous arbre droit
        afficherArbre(root->right, a, resultFile);
    }
}