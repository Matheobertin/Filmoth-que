#include "fonction.h"

//Fonction pour vérifié si le .txt est présent dans le dossier. Si oui on retourne false pour stopper la boucle sinon on retourne true et la boucle continue
bool shutdown(){
    //Ouvrir le fichier en mode lecture
    FILE *file = fopen("shutdown.txt", "r");
    if (file == NULL) {
        //printf("Impossible d'ouvrir le fichier shutdown.txt\n");
        return true;
    }
    remove("shutdown.txt");
    return false;
}

//Fonction pour free la totalité de l'arbre
void deleteFilmTree(struct Film* root) {
    if (root == NULL) {
        return;
    }

    deleteFilmTree(root->left);
    deleteFilmTree(root->right);

    free(root->titre);
    free(root->realisateur);
    free(root->category);
    free(root);
}