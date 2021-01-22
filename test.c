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
    if (j.choix_colonne >= 0 && j.choix_colonne < colonne)
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

bool estCaseDepart(joueur j, int l, int c){
    if (l == j.choix_ligne && c == j.choix_colonne)
    {
        return true;
    }
    return false;
}

joueur changeJoueur(joueur j, joueur j1, joueur j2){
    if (j.choix_ligne == j1.choix_ligne)
    {
        return j2;
    }else
    {
        return j1;
    }
}



void priseSimple(int **plateau, joueur j){
    int l = j.choix_ligne;
    int c = j.choix_colonne;
    j.nb_graine = 0;    
    if(verifCaseEstPasVide(plateau,j)){
        int x = plateau[l][c];
        plateau[l][c] = 0;
        if (l == 1)
        {
            c++;
        }else
        {
            c--;
        }
        
        while (x != 0)
        {        
            if (l == 1 && c < colonne){   
                while(c < colonne && x != 0)
                {
                    if (estCaseDepart(j,l,c))
                    {
                        c++;
                    }else
                    {
                        printf("l : %d c : %d et x : %d\n",l,c,x);
                        plateau[l][c]++;
                        x--;
                        affichePlateau(plateau);
                        printf("\n");
                        c++;   
                    }
                    
                }
            }
            if(l == 1 && c >= colonne){
                l = 0;
                c--; 
            }
            // ca commence ici le probleme !
            if(l == 0 && c < colonne){
                while (c >= 0 && x != 0) // revoir cette ligne probleme au niveau du comptage !! 
                {   
                    if (estCaseDepart(j,l,c))
                    {
                        c--;
                    }else{
                        printf("l : %d c : %d et x : %d\n",l,c,x);
                        plateau[l][c]++;
                        c--; 
                        x--;
                        affichePlateau(plateau);
                        printf("\n"); 
                    }
                }   
            }
            if(l == 0 && c < 0){
                l = 1;
                c++; // lorsque la c = -1 c'est impossible parce qu'il y a pas d'indice -1 du coup tu fais c++ -> p[1][0]    
            }
        }
        if (plateau[l][c] == 1 || plateau[l][c] == 2)
        {
            int v = plateau[l][c];
            j.nb_graine = j.nb_graine + v;
            plateau[l][c] = 0;
            printf("\nligne : %d, colonne : %d",l,c);
            printf("\ncase final : %d",plateau[l][c]);
            printf("\npoints : %d\n",j.nb_graine);
            affichePlateau(plateau);
        } 

    }else
    {
        printf("La case saisie est invalide !! ");
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
    printf("\n%s -> Attention si 0 est votre choix vous commencerez : ", j1.prenom);
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

    joueur j = j1; // intialisation du joueur 1 par default
    /* Choisir la colonne */
    for (int y = 0; y < 50; y++)
    {
        printf("\n%s -> Veuillez choisir la case que vous voulez déplcer en saisissant le numColonne : ", j.prenom);
        scanf("%d", &j.choix_colonne);
        priseSimple(plateau,j);
        j = changeJoueur(j,j1,j2);
    }

}

// faire une function bool PartieFinie
