#include <stdlib.h>
#include <stdio.h>
#include "../headers/constante.h"
#include "../headers/carte.h"
#include "../headers/plateau.h"
#include "../headers/faction.h"

/**
 * Une fonction pour afficher le plateau de jeu.
 * @param p : le plateau de jeu à afficher.
 */
void afficher_plateau(plateau p)
{
    for(int x=get_min_x(p);x<=get_max_x(p);x++)
    {
        for(int y=get_min_y(p);x<=get_max_y(p);y++)
        {
            if(get_grille(p)[x][y]!=NULL)
            {
                printf("%d ",get_numero_plateau(grille[x][y]));
            }
            else 
            {
                printf("  ");
            }
        }
        printf("\n");
    }
};

/**
 * Une fonction pour afficher la main d'une faction.
 * @param f : La faction dont on va afficher la main.
 */
void afficher_main_faction(faction f)
{
    carte *main = get_main(f);
    int i=0;
    while(get_queue_liste_chainee(main)!=NULL)
    {
        i++;
        main = get_queue_liste_chainee(main);
        printf("%d : %s \n",i,get_valeur_tete_liste_chainee(main)->nom);
    }
};

/**
 * Une fonction pour demander à une faction si elle veut renouveller sa main.
 * @param f : la faction à laquelle on va demander si elle veut renouveller sa main.
 * @return booleen : VRAI si la faction veut vider sa main, mélanger sa pioche et repiocher, FAUX sinon.
 */
booleen demander_renouvellement_main(faction f)
{
    char rep = '';
    while(rep!='O' || rep!='N')
    {
        printf("Voulez vous renouveller votre main ? (O/N)");
        scanf("%c",rep);
    }
    return rep == 'O' ? VRAI : FAUX;
};

/**
 * Une fonction pour demander à une faction quelle carte de sa main elle veut poser face cachée.
 * @param f : la faction à laquelle on va demander quelle carte de sa main elle veut poser face cachée.
 * @return carte : la carte que la faction veut poser face cachée.
 */
carte demander_carte_poser_face_cachee(faction f)
{
    if(f != NULL)
    {
        afficher_main_faction(f);

        int numero_carte = 0;
        carte *main = get_main(f);
        carte clacarte = NULL;
        int i=0;

        while(numero_carte>taille_liste_chainee(main); && numero_carte<=0)
        {
            printf("Quelle carte voulez vous placer face cachée sur le plateau ?");
            scanf("%d",&numero_carte);
        }

        while(get_queue_liste_chainee(main)!=NULL)
        {
            i++;
            clacarte = get_valeur_tete_liste_chainee(main);
            main = get_queue_liste_chainee(main);
            if(i==numero_carte)
            {
                return clacarte;
            }
        }
    }
};

/**
 * Une fonction pour demander à une faction à quelle position elle veut poser sa carte face cachée qu'elle a choisie précédemment,
 * et faire des vérifications sur cette position choisie.
 * @param p : Le plateau de jeu sur lequel on va faire des vérifications pour la position choisie.
 * @param f : La faction à laquelle on va demander à quelle position elle veut poser sa carte.
 * @param c : La carte que l'on veut poser à une position que la faction va choisir.
 * @return position : Position en abscisse et en ordonnée de la carte à poser, calculée à partir des entrées de l'utilisateur.
 */
position demander_position_poser_carte(plateau p, faction f, carte c)
{
        int carte_a_coller = 69;
        direction dir = '';
        position pos_carte = {15,15};

        if(get_nombre_cartes_posees(p)==0)
        {
            return pos_carte;
        }
        do
        {
            printf("Tapez le numéro de la carte face cachée à côté de laquelle vous voulez vous placer ?\n");
            scanf("%d",&carte_a_coller);

            for(int x=get_min_x(p);x<=get_max_x(p);x++)
            {
                for(int y=get_min_y(p);x<=get_max_y(p);y++)
                {
                    if(carte_a_coller==get_numero_plateau(get_grille(p)[x][y]))
                    {
                        if(get_grille(p)[x+1][y]!=NULL && get_grille(p)[x-1][y]!=NULL && get_grille(p)[x][y-1]!=NULL && get_grille(p)[x][y+1]!=NULL)
                        {
                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, toute les places sont prises.\n");
                            carte_a_coller = 69;
                        }
                        else
                        {
                            do
                            {
                                printf("Quelle direction voulez vous placer votre carte ? (H/B/D/G)");
                                scanf("%c",&dir);

                                switch (dir)
                                {
                                case 'H':
                                    if(get_grille(p)[x+1][y]!=NULL)
                                    {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = '';
                                    }
                                    else
                                    {
                                        pos_carte.x = x+1;
                                        pos_carte.y = y;
                                        return pos_carte;
                                    }
                                    break;

                                case 'B': 
                                    if(get_grille(p)[x-1][y]!=NULL)
                                    {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = '';
                                    }
                                    else
                                    {
                                        pos_carte.x = x-1;
                                        pos_carte.y = y;
                                        return pos_carte;
                                    }
                                    break;

                                case 'D':
                                    if(get_grille(p)[x][y+1]!=NULL)
                                    {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = '';
                                    }
                                    else
                                    {
                                        pos_carte.x = x;
                                        pos_carte.y = y+1;
                                        return pos_carte;
                                    }
                                    break;

                                case 'G':
                                    if(get_grille(p)[x][y-1]!=NULL)
                                    {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = '';
                                    }
                                    else
                                    {
                                        pos_carte.x = x;
                                        pos_carte.y = y-1;
                                        return pos_carte;
                                    }
                                    break;
                                
                                default:
                                    break;
                                }
                            } while(dir!='H' && dir!='B' && dir!='D' && dir!='G');
                            
                        }
                    }
                    else
                    {
                        printf("Il pas de carte ici.\n");
                        carte_a_coller = 69;
                    }
                {
            }
        } while (carte_a_coller>get_nombre_cartes_posees(p) && carte_a_coller<=0);   
};

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param c : La carte dont on veut afficher l'effet.
 */
void afficher_effet_carte_retournee(carte c)
{
    printf("L'effet de la carte est : %s",c->effet);
};

/**
 * Une fonction pour afficher la faction victorieuse de la partie.
 * @param f : la faction victorieuse de la partie.
 */
void afficher_vainqueur(faction f)
{
    printf("La faction victorieuse est la faction : %s",f->nom);
};