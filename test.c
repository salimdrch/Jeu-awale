#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ligne 2
#define colonne 6

struct joueur
{
    char prenom[10];
    int nb_graine;
    int choix_ligne; // 0 si il prend la première ligne ! 1 sinon
    int choix_colonne; // choisit la case ou il veut prendre les graines ! 
};
typedef struct joueur joueur;

bool verifSaisieCase(joueur j){
    if (j.choix_colonne >= 0 && j.choix_colonne <= colonne)
    {
        return true;
    }
    return false;
}

bool verifCaseEstPasVide(int **plateau, joueur j){
    if(verifSaisieCase(j) && plateau[j.choix_ligne][j.choix_colonne] != 0){
        return true;
    }
    return false;
}

void affichePlateau(int **plateau){
    for(int i = 0; i < ligne; i++){
        for (int j = 0; j < colonne; j++)
        {
            printf("%d", plateau[i][j]);
        }
        printf("\n");
    }
}

void priseSimple(int **plateau, joueur j){
    int l = j.choix_ligne;
    int c = j.choix_colonne;    
    if(l == 1 && verifCaseEstPasVide(plateau,j)){
        int x = plateau[l][c];
        plateau[l][c] = 0;
        c++;
         
        if (l == 1 && c < colonne){   
            while(c < colonne && x != 0)
            {
                printf("Dans le if avec i : %d et x : %d\n", c,x);
                plateau[l][c]++;
                x--;
                affichePlateau(plateau);
                printf("\n");
                c++; 
            }
        }
        if(l == 1 && c >= colonne){
            l--;
            while (c > 0 && x !=0)
            {
                c--;
                printf("Dans le else avec i : %d\n", c);
                plateau[l][c]++;
                x--;
                affichePlateau(plateau);
                printf("\n"); 
            }   
        } 
        if (plateau[l][c] == 1 || plateau[l][c] == 2)
        {
            j.nb_graine = j.nb_graine + plateau[l][c];
        }            
    }
    
}




    
 

int main(void){
    /* Créer les 2 Joueurs */
    joueur j1;
    joueur j2;
    printf("Bienvenu ! Vous allez jouer au Jeu-Awale ! \n");
    /* Création du Joueur 1 */
    printf("Joueur 1 -> Veuillez saisir votre prenom : ");
    scanf("%s", j1.prenom);
    printf("\n%s -> Veuillez saisir votre côté en saisissant 0 ou 1 : ", j1.prenom);
    printf("\n%s -> Attention si 0 est votre choix vous commencerai : ", j1.prenom);
    scanf("%d", &j1.choix_ligne);
    while (j1.choix_ligne != 0 && j1.choix_ligne != 1)
    {
        printf("\n%s -> Veuillez ressaisir votre côté en saisissant 0 ou 1 : ", j1.prenom);
        scanf("%d", &j1.choix_ligne);
    }
    /* Création du Joueur 2 */
    printf("\nJoueur 2 -> Veuillez saisir votre prenom : ");
    scanf("%s", j2.prenom);
    if (j1.choix_ligne == 1)
    {
        j2.choix_ligne = 0;
    }else
    {
        j2.choix_ligne = 1;
    }
    printf("\n%s -> Vous avez le côté : %d ", j2.prenom,j2.choix_ligne);


    /* Creer le plateau */
    int **plateau = (int**) malloc(ligne * sizeof(int*));
    for(int i = 0; i < ligne; i++){
        plateau[i] = (int*) malloc(colonne * sizeof(int));
        for (int j = 0; j < colonne; j++)
        {
            plateau[i][j] = 4;
        }
    }

    /* Choisir la colonne */
    printf("\n%s -> Veuillez la case que vous voulez déplcer en saisissant le numColonne : ", j1.prenom);
    scanf("%d", &j1.choix_colonne);
    priseSimple(plateau,j1);
    printf("\n%s -> Veuillez la case que vous voulez déplcer en saisissant le numColonne : ", j1.prenom);
    scanf("%d", &j1.choix_colonne);
    priseSimple(plateau,j1);
    printf("\n%s -> Veuillez la case que vous voulez déplcer en saisissant le numColonne : ", j1.prenom);
    scanf("%d", &j1.choix_colonne);
    priseSimple(plateau,j1);

}