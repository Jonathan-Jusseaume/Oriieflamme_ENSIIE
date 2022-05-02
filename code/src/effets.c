#include "../headers/effets.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/structure.h"
#include <string.h>
#include "../headers/constante.h"

// ajoute (ou retire) points_a_ajouter points au score de la faction f
void ajoute_points_DDRS(faction f, int points_a_ajouter) {
    set_points_DDRS(f, get_points_DDRS(f) + points_a_ajouter);
}

booleen noms_de_cartes_identiques(carte c1, char *c2_nom) {
    if (strcmp(get_nom_carte(c1), c2_nom) == 0) {
        return VRAI;
    }
    return FAUX;
}

void retourner_carte_face_visible_sans_appliquer_effet(carte c) {
    set_est_face_cachee(c, FAUX);
}

void retourner_carte_face_cachee(carte c) {
    set_est_face_cachee(c, VRAI);
}

void fise(carte c, plateau p) {
    int nombre_points_a_ajouter = 1;
    ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
}

void fisa(carte c, plateau p) {
    int nombre_points_a_ajouter = 2;
    if (get_nombre_cartes_retournees(p) % 2 == 0) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    }
}

void fc(carte c, plateau p) {
    int nombre_points_a_ajouter = 4;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                (parcours_colonnes != get_position(c).abscisse || parcours_lignes != get_position(c).ordonnee) &&
                noms_de_cartes_identiques(carte_courante, nom_cartes[FC])) {
                ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
                return;
            }
        }
    }
}

void ecologiie(carte c, plateau p) {
    int nombre_points_a_ajouter = 1;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                (noms_de_cartes_identiques(carte_courante, nom_cartes[FISE]) ||
                 noms_de_cartes_identiques(carte_courante, nom_cartes[FISA]) ||
                 noms_de_cartes_identiques(carte_courante, nom_cartes[FC]))) {
                ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
            }
        }
    }
}

void liiens(carte c, plateau p) {
    liste_chainee_carte fisa_fise_fc = initialiser_liste_chainee();
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                (noms_de_cartes_identiques(carte_courante, nom_cartes[FISE]) ||
                 noms_de_cartes_identiques(carte_courante, nom_cartes[FISA]) ||
                 noms_de_cartes_identiques(carte_courante, nom_cartes[FC]))) {
                ajouter_tete_liste_chainee(&fisa_fise_fc, carte_courante);
                supprimer_carte_grille(get_grille(p), get_position(carte_courante).ordonnee,
                                       get_position(carte_courante).abscisse);
            }
        }
    }
    int taille_lc = taille_liste_chainee(fisa_fise_fc);
    srand(time(NULL));
    int valeur_aleatoire;
    position position_carte_haut_gauche_grille = get_position_carte_haut_gauche_grille(get_grille(p), FAUX);
    for (int parcours_liste = 0; parcours_liste < taille_lc; parcours_liste++) {
        valeur_aleatoire = rand() % (taille_lc - parcours_liste);
        carte carte_aleatoire_lc = supprimer_carte_liste_chainee(&fisa_fise_fc, valeur_aleatoire);
        retourner_carte_face_cachee(carte_aleatoire_lc);
        poser_carte_grille(get_grille(p), carte_aleatoire_lc, position_carte_haut_gauche_grille.ordonnee,
                           position_carte_haut_gauche_grille.abscisse - parcours_liste - 1);
    }
    liberer_liste_chainee(fisa_fise_fc);
}

void soirees_sans_alcool(carte c, plateau p) {
    int nombre_points_a_ajouter = 5;
    booleen alcool_trouve = FAUX;
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    liste_chainee_carte fisa_fise_fc = initialiser_liste_chainee();
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Alcool])) {
                    alcool_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[FISE]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[FISA]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[FC])) {
                    ajouter_tete_liste_chainee(&fisa_fise_fc, carte_courante);
                }
            }
        }
    }
    if (alcool_trouve) {
        int taille_lc = taille_liste_chainee(fisa_fise_fc);
        grille_carte gc = get_grille(p);
        for (int parcours_lc = taille_lc - 1; parcours_lc >= 0; parcours_lc--) {
            carte carte_courante_lc = supprimer_carte_liste_chainee(&fisa_fise_fc, parcours_lc);
            ajouter_tete_liste_chainee(&cartes_supprimees,
                                       supprimer_carte_grille(gc, get_position(carte_courante_lc).ordonnee,
                                                              get_position(carte_courante_lc).abscisse));
        }
        // gc = get_grille(p); // Utile de faire ça pour refresh la grille après suppression des cartes FISA/FISE/FC ?
        int premiere_ligne = get_min_y_grille(gc);
        int derniere_ligne = get_max_y_grille(gc);
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            // Inutile de vérifier si cette position de la grille est déjà nulle ou non
            // car cela revient tout de même à faire 1 opération, tout comme si on supprimait directement une carte.
            if (get_carte_grille(gc, premiere_ligne, parcours_colonnes) != NULL) {
                ajouter_tete_liste_chainee(&cartes_supprimees,
                                           supprimer_carte_grille(gc, premiere_ligne, parcours_colonnes));
            }
            if (get_carte_grille(gc, derniere_ligne, parcours_colonnes) != NULL) {
                ajouter_tete_liste_chainee(&cartes_supprimees,
                                           supprimer_carte_grille(gc, derniere_ligne, parcours_colonnes));
            }
        }
        liberer_liste_chainee(fisa_fise_fc);
    } else {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void alcool(carte c, plateau p) {
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    if (get_carte_grille(get_grille(p), get_position(c).ordonnee + 1, get_position(c).abscisse) != NULL) {
        ajouter_tete_liste_chainee(&cartes_supprimees,
                                   supprimer_carte_grille(get_grille(p), get_position(c).ordonnee + 1,
                                                          get_position(c).abscisse));
    }
    if (get_carte_grille(get_grille(p), get_position(c).ordonnee - 1, get_position(c).abscisse) != NULL) {
        ajouter_tete_liste_chainee(&cartes_supprimees,
                                   supprimer_carte_grille(get_grille(p), get_position(c).ordonnee - 1,
                                                          get_position(c).abscisse));
    }
    if (get_carte_grille(get_grille(p), get_position(c).ordonnee, get_position(c).abscisse + 1) != NULL) {
        ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p), get_position(c).ordonnee,
                                                                              get_position(c).abscisse + 1));
    }
    if (get_carte_grille(get_grille(p), get_position(c).ordonnee, get_position(c).abscisse - 1) != NULL) {
        ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p), get_position(c).ordonnee,
                                                                              get_position(c).abscisse - 1));
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void cafe(carte c, plateau p) {
    int nombre_points_a_ajouter = 1;
    booleen ecocup_trouve = FAUX;
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (ecocup_trouve == FAUX && noms_de_cartes_identiques(carte_courante, nom_cartes[Ecocup])) {
                    ecocup_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[The]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Alcool])) {
                    ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p), get_position(
                                                                                                  carte_courante).ordonnee,
                                                                                          get_position(
                                                                                                  carte_courante).abscisse));
                }
            }
        }
    }
    if (ecocup_trouve == VRAI) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    } else {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], -1 * nombre_points_a_ajouter);
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void the(carte c, plateau p) {
    int nombre_points_a_ajouter = 1;
    booleen ecocup_trouve = FAUX;
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (ecocup_trouve == FAUX && noms_de_cartes_identiques(carte_courante, nom_cartes[Ecocup])) {
                    ecocup_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Cafe]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Alcool])) {
                    ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p), get_position(
                                                                                                  carte_courante).ordonnee,
                                                                                          get_position(
                                                                                                  carte_courante).abscisse));
                }
            }
        }
    }
    if (ecocup_trouve == VRAI) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    } else {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], -1 * nombre_points_a_ajouter);
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void ecocup(carte c, plateau p) {
    // NE FAIT RIEN
}

booleen liste_contient_carte(liste_chainee_carte lc_carte_deja_etudiees, carte carte_a_chercher) {
    for (int parcours_liste = 0; parcours_liste < taille_liste_chainee(lc_carte_deja_etudiees); parcours_liste++) {
        if (noms_de_cartes_identiques(get_carte_liste_chainee(lc_carte_deja_etudiees, parcours_liste),
                                      get_nom_carte(carte_a_chercher))) {
            return VRAI;
        }
    }
    return FAUX;
}

int nombre_occurrences_carte_retournee_plateau(carte c, plateau p) {
    int nombre_occurrences_carte = 0;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                noms_de_cartes_identiques(carte_courante, get_nom_carte(c))) {
                nombre_occurrences_carte++;
            }
        }
    }
    return nombre_occurrences_carte;
}

void reprographie(carte c, plateau p) {
    int nombre_points_a_ajouter = 0; // Variable qui peut évoluer dans la fonction
    liste_chainee_carte liste_chainee_carte_deja_etudiees = initialiser_liste_chainee();
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                !liste_contient_carte(liste_chainee_carte_deja_etudiees, carte_courante) &&
                (nombre_points_a_ajouter = nombre_occurrences_carte_retournee_plateau(carte_courante, p)) > 2) {
                ajouter_tete_liste_chainee(&liste_chainee_carte_deja_etudiees, c);
                if (get_identifiant_faction_carte(c) == FACTION1) {
                    ajoute_points_DDRS(get_factions(p)[FACTION2],
                                       -1 * nombre_points_a_ajouter); // Plutôt une combinaison
                } else {
                    ajoute_points_DDRS(get_factions(p)[FACTION1], -1 * nombre_points_a_ajouter);
                }
            }
        }
    }
}

void isolation_batiment(carte c, plateau p) {
    int nombre_points_a_ajouter = 1;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && get_est_face_cachee(carte_courante)) {
                ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(carte_courante)],
                                   nombre_points_a_ajouter);
            }
        }
    }
}

void parcours_sobriete_numerique(carte c, plateau p) {
    grille_carte gc = get_grille(p);
    booleen carte_gauche_face_cachee_trouvee;
    booleen carte_droite_face_cachee_trouvee;
    for (int parcours_lignes = get_min_y_grille(gc); parcours_lignes <= get_max_y_grille(gc); parcours_lignes++) {
        carte_gauche_face_cachee_trouvee = FAUX;
        carte_droite_face_cachee_trouvee = FAUX;
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)) &&
             !carte_gauche_face_cachee_trouvee; parcours_colonnes++) {
            carte carte_courante = get_carte_grille(gc, parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && get_est_face_cachee(carte_courante)) {
                retourner_carte_face_visible_sans_appliquer_effet(carte_courante);
                carte_gauche_face_cachee_trouvee = VRAI;
            }
        }
        for (int parcours_colonnes = get_max_x_grille(get_grille(p));
             parcours_colonnes >= get_min_x_grille(get_grille(p)) &&
             !carte_droite_face_cachee_trouvee; parcours_colonnes--) {
            carte carte_courante = get_carte_grille(gc, parcours_lignes, get_max_x_grille(gc));
            if (carte_courante != NULL && get_est_face_cachee(carte_courante)) {
                retourner_carte_face_visible_sans_appliquer_effet(carte_courante);
                carte_droite_face_cachee_trouvee = VRAI;
            }
        }
    }
}

void heures_supplementaires(carte c, plateau p) {
    int nombre_points_a_ajouter = -3;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                noms_de_cartes_identiques(carte_courante, nom_cartes[Heures_supplementaires])) {
                if (get_identifiant_faction_carte(carte_courante) == FACTION1) {
                    ajoute_points_DDRS(get_factions(p)[FACTION2], nombre_points_a_ajouter);
                } else {
                    ajoute_points_DDRS(get_factions(p)[FACTION1], nombre_points_a_ajouter);
                }
            }
        }
    }
}

void kahina_bouchama(carte c, plateau p) {
    grille_carte gc = get_grille(p);
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    srand(time(NULL));
    liste_chainee_carte lc = initialiser_liste_chainee();
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && get_est_face_cachee(carte_courante)) {
                ajouter_tete_liste_chainee(&lc, carte_courante);
            }
        }
    }
    int taille_lc = taille_liste_chainee(lc);
    if (taille_lc > 0) {
        int valeur_aleatoire_lc = rand() % taille_lc;
        carte carte_aleatoire = supprimer_carte_liste_chainee(&lc, valeur_aleatoire_lc);
        ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(gc, get_position(carte_aleatoire).ordonnee,
                                                                              get_position(carte_aleatoire).abscisse));

        // On vide et libère la liste chainée
        for (int parcours_liste = taille_lc - 1; parcours_liste >= 0; parcours_liste--) {
            supprimer_carte_liste_chainee(&lc, parcours_liste);
        }
    }
    liberer_liste_chainee(lc);
    set_cartes_supprimees(p, cartes_supprimees);
}

void kevin_goilard(carte c, plateau p) {
    int nombre_points_a_ajouter = 2;
    grille_carte gc = get_grille(p);
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    srand(time(NULL));
    int valeur_aleatoire_y = (rand() % ((get_max_y_grille(gc) + 1) - get_min_y_grille(gc) + 1)) + get_min_y_grille(gc);
    for (int parcours_colonnes = get_min_x_grille(get_grille(p));
         parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
        carte c_supprimee = supprimer_carte_grille(get_grille(p), valeur_aleatoire_y, parcours_colonnes);
        if (c_supprimee != NULL) {
            ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
            ajouter_tete_liste_chainee(&cartes_supprimees, c_supprimee);
        }
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void massinissa_merabet(carte c, plateau p) {
    if (get_derniere_carte_retournee(p) != NULL &&
        !noms_de_cartes_identiques(get_derniere_carte_retournee(p), nom_cartes[Massinissa_Merabet])) {
        booleen identifiant_derniere_carte_retournee_a_changer = (get_identifiant_faction_carte(c) !=
                                                                  get_identifiant_faction_carte(
                                                                          get_derniere_carte_retournee(p)));
        // On inverse temporairement la faction possédant la carte c
        if (identifiant_derniere_carte_retournee_a_changer) {
            if (get_identifiant_faction_carte(c) == FACTION1) {
                set_identifiant_faction_carte(get_derniere_carte_retournee(p), FACTION1);
            } else {
                set_identifiant_faction_carte(get_derniere_carte_retournee(p), FACTION2);
            }

            (get_effet_fonction(get_derniere_carte_retournee(p)))(get_derniere_carte_retournee(p), p);


            // On récupère la possession initiale de la carte
            if (get_identifiant_faction_carte(c) == FACTION1) {
                set_identifiant_faction_carte(get_derniere_carte_retournee(p), FACTION2);
            } else {
                set_identifiant_faction_carte(get_derniere_carte_retournee(p), FACTION1);
            }
        } else {
            (get_effet_fonction(get_derniere_carte_retournee(p)))(get_derniere_carte_retournee(p), p);
        }
    }
}

void vitera_y(carte c, plateau p) {
    int nombre_points_a_ajouter = 3;
    if (get_points_DDRS(get_factions(p)[FACTION1]) < get_points_DDRS(get_factions(p)[FACTION2])) {
        ajoute_points_DDRS(get_factions(p)[FACTION1], nombre_points_a_ajouter);
    } else if (get_points_DDRS(get_factions(p)[FACTION2]) < get_points_DDRS(get_factions(p)[FACTION1])) {
        ajoute_points_DDRS(get_factions(p)[FACTION2], nombre_points_a_ajouter);
    }
}

void jonas_senizergues(carte c, plateau p) {
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                noms_de_cartes_identiques(carte_courante, nom_cartes[Heures_supplementaires])) {
                ajouter_tete_liste_chainee(&cartes_supprimees,
                                           supprimer_carte_grille(get_grille(p), get_position(carte_courante).ordonnee,
                                                                  get_position(carte_courante).abscisse));
            }
        }
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void fetia_bannour(carte c, plateau p) {
    int nombre_points_a_ajouter = 0; // Peut varier
    booleen heures_supp_retournee_trouvee = FAUX;
    int compteur_cartes_a_recenser = 0;
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Heures_supplementaires])) {
                    heures_supp_retournee_trouvee = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Catherine_Dubois]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Anne_Laure_Ligozat]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Guillaume_Burel]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Christophe_Mouilleron]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Thomas_Lim]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Julien_Forest]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Dimitri_Watel])) {
                    compteur_cartes_a_recenser++;
                }
            }
        }
    }
    if (heures_supp_retournee_trouvee) {
        grille_carte gc = get_grille(p);
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(gc, get_position(c).ordonnee, parcours_colonnes);
            if (carte_courante != NULL) {
                ajouter_tete_liste_chainee(&cartes_supprimees,
                                           supprimer_carte_grille(gc, get_position(carte_courante).ordonnee,
                                                                  get_position(carte_courante).abscisse));
                // Faut-il supprimer les cartes de la liste chainee ou je laisse faire liberer liste chainee ?
            }
        }
        gc = get_grille(p); // Utile de faire ça pour refresh la grille après suppression des cartes ?
        for (int parcours_lignes = get_min_y_grille(get_grille(p));
             parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
            carte carte_courante = get_carte_grille(gc, parcours_lignes, get_position(c).abscisse);
            if (carte_courante != NULL) {
                ajouter_tete_liste_chainee(&cartes_supprimees,
                                           supprimer_carte_grille(gc, get_position(carte_courante).ordonnee,
                                                                  get_position(carte_courante).abscisse));
            }
            // Inutile de vérifier si cette position de la grille est déjà nulle ou non
            // car cela revient tout de même à faire 1 opération, tout comme si on supprimait directement une carte.
        }
    } else {
        nombre_points_a_ajouter = compteur_cartes_a_recenser;
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void catherine_dubois(carte c, plateau p) {
    grille_carte gc = get_grille(p);
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    int min_x, max_x;
    int min_y, max_y;
    min_y = get_min_y_grille(gc);
    max_y = get_max_y_grille(gc);
    min_x = get_min_x_grille(gc);
    max_x = get_max_x_grille(gc);
    ajouter_tete_liste_chainee(&cartes_supprimees,
                               supprimer_carte_grille(gc, get_position(c).ordonnee, max_x));
    ajouter_tete_liste_chainee(&cartes_supprimees,
                               supprimer_carte_grille(gc, get_position(c).ordonnee, min_x));
    ajouter_tete_liste_chainee(&cartes_supprimees,
                               supprimer_carte_grille(gc, max_y, get_position(c).abscisse));
    ajouter_tete_liste_chainee(&cartes_supprimees,
                               supprimer_carte_grille(gc, min_y, get_position(c).abscisse));
    set_cartes_supprimees(p, cartes_supprimees);
}

void anne_laure_ligozat(carte c, plateau p) {
    int nombre_points_a_ajouter = 3;
    booleen derniere_carte_supprimee = FAUX;
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            derniere_carte_supprimee = FAUX;
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[EcologIIE]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Ecocup]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Isolation_du_batiment]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Parcours_sobriete_numerique])) {
                    ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
                    for (int parcours_l = get_max_y_grille(get_grille(p));
                         parcours_l >= get_min_y_grille(get_grille(p)) && !derniere_carte_supprimee; parcours_l--) {
                        for (int parcours_c = get_max_x_grille(get_grille(p));
                             parcours_c >= get_min_x_grille(get_grille(p)) && !derniere_carte_supprimee; parcours_c--) {
                            carte courante_a_l_envers = get_carte_grille(get_grille(p), parcours_l, parcours_c);
                            if (courante_a_l_envers != NULL && get_est_face_cachee(courante_a_l_envers)) {
                                ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p),
                                                                                                      get_position(
                                                                                                              courante_a_l_envers).ordonnee,
                                                                                                      get_position(
                                                                                                              courante_a_l_envers).abscisse));
                                derniere_carte_supprimee = VRAI;
                            }
                        }
                    }
                }
            }
        }
    }
    set_cartes_supprimees(p, cartes_supprimees);
}

void guillaume_burel(carte c, plateau p) { // Pas sûr d"avoir bien compris la carte
    int nombre_points_a_ajouter = 3;
    if (get_identifiant_faction_carte(c) == FACTION1) { // Si la faction 1 a posé cette carte...
        if (get_points_DDRS(get_factions(p)[FACTION1]) < get_points_DDRS(get_factions(p)[FACTION2])) {
            ajoute_points_DDRS(get_factions(p)[FACTION1], nombre_points_a_ajouter);
            ajoute_points_DDRS(get_factions(p)[FACTION2], -1 * nombre_points_a_ajouter);
        }
    } else { // Si c'est la faction 2 qui a posé la carte...
        if (get_points_DDRS(get_factions(p)[FACTION2]) < get_points_DDRS(get_factions(p)[FACTION1])) {
            ajoute_points_DDRS(get_factions(p)[FACTION2], nombre_points_a_ajouter);
            ajoute_points_DDRS(get_factions(p)[FACTION1], -1 * nombre_points_a_ajouter);
        }
    }
}

void christophe_mouilleron(carte c, plateau p) {
    booleen heures_supp_trouve = FAUX;
    liste_chainee_carte lc = initialiser_liste_chainee();
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (!heures_supp_trouve &&
                    noms_de_cartes_identiques(carte_courante, nom_cartes[Heures_supplementaires])) {
                    heures_supp_trouve = VRAI;
                }
                if (!noms_de_cartes_identiques(carte_courante, nom_cartes[Christophe_Mouilleron]) &&
                    !noms_de_cartes_identiques(carte_courante, nom_cartes[Heures_supplementaires])) {
                    ajouter_tete_liste_chainee(&lc, carte_courante);
                }
            }
        }
    }
    int taille_lc = taille_liste_chainee(lc);
    if (heures_supp_trouve == VRAI) {
        for (int parcours_liste = 0; parcours_liste < taille_lc; parcours_liste++) {
            carte carte_courante_liste = get_carte_liste_chainee(lc, parcours_liste);
            ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p), get_position(
                                                                                          carte_courante_liste).ordonnee,
                                                                                  get_position(
                                                                                          carte_courante_liste).abscisse));
        }
    }
    for (int i = taille_lc - 1; i >= 0; i--) {
        supprimer_carte_liste_chainee(&lc, i);
    }
    liberer_liste_chainee(lc);
}

void thomas_lim(carte c, plateau p) {
    int nombre_points_a_ajouter = 3; // Peut varier (pour la faction adverse)
    booleen julien_forest_retournee_trouve = FAUX;
    int compteur_carte_fise = 0;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Julien_Forest])) {
                    julien_forest_retournee_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[FISE])) {
                    compteur_carte_fise++;
                }
            }
        }
    }
    if (julien_forest_retournee_trouve) {
        nombre_points_a_ajouter = compteur_carte_fise;
        if (get_identifiant_faction_carte(c) == FACTION1) { // Si la faction 1 a posé cette carte...
            ajoute_points_DDRS(get_factions(p)[FACTION2], -1 * nombre_points_a_ajouter);
        } else { // Si c'est la faction 2 qui a posé la carte...
            ajoute_points_DDRS(get_factions(p)[FACTION1], -1 * nombre_points_a_ajouter);
        }
    } else {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)],
                           compteur_carte_fise * nombre_points_a_ajouter);
    }
}

void julien_forest(carte c, plateau p) {
    int nombre_points_a_ajouter = 6; // Peut varier (pour la faction adverse)
    booleen cafe_retourne_trouve = FAUX;
    int compteur_carte_fise = 0;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[Cafe])) {
                    cafe_retourne_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[FISE])) {
                    compteur_carte_fise++;
                }
            }
        }
    }
    if (cafe_retourne_trouve == VRAI) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)],
                           compteur_carte_fise * nombre_points_a_ajouter);
    }
}

void dimitri_watel(carte c, plateau p) {
    int nombre_points_a_ajouter = 3; // Peut varier (pour la faction adverse)
    booleen the_retourne_trouve = FAUX;
    int compteur_carte_fisa_fc = 0;
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[The])) {
                    the_retourne_trouve = VRAI;
                }
                if (noms_de_cartes_identiques(carte_courante, nom_cartes[FISA]) ||
                    noms_de_cartes_identiques(carte_courante, nom_cartes[FC])) {
                    compteur_carte_fisa_fc++;
                }
            }
        }
    }
    if (the_retourne_trouve == VRAI) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)],
                           compteur_carte_fisa_fc * nombre_points_a_ajouter);
    }
}

void djibril_aurelien_dembele_cabot(carte c, plateau p) {
    int nombre_points_a_ajouter = 5;
    int compteur_cartes_retournee_sur_ligne = 0;
    int parcours_colonnes = get_min_x_grille(get_grille(p));
    int nombre_de_cartes_a_trouver_sur_la_ligne = 4;
    while (compteur_cartes_retournee_sur_ligne < nombre_de_cartes_a_trouver_sur_la_ligne &&
           parcours_colonnes <= get_max_x_grille(get_grille(p))) {
        carte carte_courante = get_carte_grille(get_grille(p), get_position(c).ordonnee, parcours_colonnes);
        if (carte_courante != NULL && !get_est_face_cachee(carte_courante)) {
            compteur_cartes_retournee_sur_ligne++;
        }
        parcours_colonnes++;
    }
    if (compteur_cartes_retournee_sur_ligne >= nombre_de_cartes_a_trouver_sur_la_ligne) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    }
}


void eric_lejeune(carte c, plateau p) {
    liste_chainee_carte lc_cartes_retournees = initialiser_liste_chainee();
    liste_chainee_carte liste_chainee_finale = initialiser_liste_chainee();
    liste_chainee_carte cartes_supprimees = get_cartes_supprimees(p);
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)); parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)); parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
                (get_position(carte_courante).ordonnee != get_position(c).ordonnee || get_position(carte_courante).abscisse != get_position(c).abscisse)) {
                ajouter_tete_liste_chainee(&lc_cartes_retournees, carte_courante);
            }
        }
    }
    int taille_lc = taille_liste_chainee(lc_cartes_retournees);
    booleen tirer_au_sort = FAUX;
    srand(time(NULL));
    for (int nombre_repetition = 0; nombre_repetition < taille_lc && nombre_repetition < 5; nombre_repetition++) {
        int valeur_aleatoire = rand() % (taille_lc - nombre_repetition);
        carte carte_courante = supprimer_carte_liste_chainee(&lc_cartes_retournees, valeur_aleatoire);
        ajouter_tete_liste_chainee(&liste_chainee_finale, carte_courante);
        if (noms_de_cartes_identiques(carte_courante, nom_cartes[Catherine_Dubois]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Anne_Laure_Ligozat]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Guillaume_Burel]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Christophe_Mouilleron]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Thomas_Lim]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Julien_Forest]) ||
            noms_de_cartes_identiques(carte_courante, nom_cartes[Dimitri_Watel])) {
            tirer_au_sort = VRAI;
        }
    }
    taille_lc = taille_liste_chainee(lc_cartes_retournees);
    for (int i = taille_lc - 1; i >= 0; i--) {
        supprimer_carte_liste_chainee(&lc_cartes_retournees, i);
    }
    if (tirer_au_sort) {
        int taille_lc_finale = taille_liste_chainee(liste_chainee_finale);
        position pos_carte_haut_gauche_grille = get_position_carte_haut_gauche_grille(get_grille(p), FAUX);
        for (int parcours_liste = taille_lc_finale - 1, parcours = 0; parcours_liste >= 0; parcours_liste--, parcours++) {
            carte carte_aleatoire_lc_finale = supprimer_carte_liste_chainee(&liste_chainee_finale, parcours_liste);
            retourner_carte_face_cachee(carte_aleatoire_lc_finale);
            carte courante = supprimer_carte_grille(get_grille(p), get_position(carte_aleatoire_lc_finale).ordonnee,
                                                    get_position(carte_aleatoire_lc_finale).abscisse);
            poser_carte_grille(get_grille(p), courante, pos_carte_haut_gauche_grille.ordonnee,
                               pos_carte_haut_gauche_grille.abscisse - parcours - 1);
        }
    } else {
        int taille = taille_liste_chainee(liste_chainee_finale);
        for (int parcours_liste = taille - 1; parcours_liste >= 0; parcours_liste--) {
            carte carte_aleatoire_lc_finale = supprimer_carte_liste_chainee(&liste_chainee_finale, parcours_liste);
            ajouter_tete_liste_chainee(&cartes_supprimees, supprimer_carte_grille(get_grille(p),
                                                                                  get_position(carte_aleatoire_lc_finale).ordonnee,
                                                                                  get_position(carte_aleatoire_lc_finale).abscisse));
        }
    }
    // On libère les listes chainées utilisées
    liberer_liste_chainee(lc_cartes_retournees);
    liberer_liste_chainee(liste_chainee_finale);
    set_cartes_supprimees(p, cartes_supprimees);
}

void lucienne_pacave(carte c, plateau p) {
    int nombre_points_a_ajouter = 5;
    booleen carte_fisa_retournee_trouvee = FAUX;
    int parcours_lignes = get_min_y_grille(get_grille(p));
    int max_y_grille = get_max_y_grille(get_grille(p));
    while (carte_fisa_retournee_trouvee != VRAI && parcours_lignes <= max_y_grille) {
        carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, get_position(c).abscisse);
        if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
            noms_de_cartes_identiques(carte_courante, nom_cartes[FISA])) {
            carte_fisa_retournee_trouvee = VRAI;
        }
        parcours_lignes++;
    }
    int parcours_colonnes = get_min_x_grille(get_grille(p));
    int max_x_grille = get_max_x_grille(get_grille(p));
    while (carte_fisa_retournee_trouvee != VRAI && parcours_colonnes <= max_x_grille) {
        carte carte_courante = get_carte_grille(get_grille(p), get_position(c).ordonnee, parcours_colonnes);
        if (carte_courante != NULL && !get_est_face_cachee(carte_courante) &&
            noms_de_cartes_identiques(carte_courante, nom_cartes[FISA])) {
            carte_fisa_retournee_trouvee = VRAI;
        }
        parcours_colonnes++;
    }
    if (carte_fisa_retournee_trouvee) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    }
}

void katrin_salhab(carte c, plateau p) {
    int nombre_points_a_ajouter = 10;
    booleen carte_lucienne_pacave_retournee_trouvee = FAUX;
    booleen carte_djibril_aurelien_retournee_trouvee = FAUX;
    booleen carte_eric_lejeune_retournee_trouvee = FAUX;
    booleen lucienne_eric_djibril_retournees_trouvees = FAUX;
    liste_chainee_carte lc = initialiser_liste_chainee();
    for (int parcours_lignes = get_min_y_grille(get_grille(p));
         parcours_lignes <= get_max_y_grille(get_grille(p)) &&
         !(lucienne_eric_djibril_retournees_trouvees = carte_lucienne_pacave_retournee_trouvee &&
                                                       carte_djibril_aurelien_retournee_trouvee &&
                                                       carte_eric_lejeune_retournee_trouvee);
         parcours_lignes++) {
        for (int parcours_colonnes = get_min_x_grille(get_grille(p));
             parcours_colonnes <= get_max_x_grille(get_grille(p)) &&
             !(lucienne_eric_djibril_retournees_trouvees = carte_lucienne_pacave_retournee_trouvee &&
                                                           carte_djibril_aurelien_retournee_trouvee &&
                                                           carte_eric_lejeune_retournee_trouvee);
             parcours_colonnes++) {
            carte carte_courante = get_carte_grille(get_grille(p), parcours_lignes, parcours_colonnes);
            if (carte_courante != NULL) {
                if (!get_est_face_cachee(carte_courante)) {
                    if (noms_de_cartes_identiques(carte_courante, nom_cartes[Djibril_Aurelien_Dembele_Cabot])) {
                        carte_djibril_aurelien_retournee_trouvee = VRAI;
                    } else if (noms_de_cartes_identiques(carte_courante, nom_cartes[Eric_Lejeune])) {
                        carte_eric_lejeune_retournee_trouvee = VRAI;
                    } else if (noms_de_cartes_identiques(carte_courante, nom_cartes[Lucienne_Pacave])) {
                        carte_lucienne_pacave_retournee_trouvee = VRAI;
                    }
                } else {
                    if (get_position(carte_courante).ordonnee == get_position(c).ordonnee) {
                        ajouter_tete_liste_chainee(&lc, carte_courante);
                    }
                }
            }
        }
    }
    if (lucienne_eric_djibril_retournees_trouvees) {
        ajoute_points_DDRS(get_factions(p)[get_identifiant_faction_carte(c)], nombre_points_a_ajouter);
    } else {
        int taille_lc = taille_liste_chainee(lc);
        for (int parcours_lc = taille_lc - 1; parcours_lc >= 0; parcours_lc--) {
            retourner_carte_face_visible_sans_appliquer_effet(supprimer_carte_liste_chainee(&lc, parcours_lc));
        }
        liberer_liste_chainee(lc);
    }
}

void laurent_prevel(carte c, plateau p) {
    // Cet effet est géré par initialiser_manche() qui vérifie que la dernière carte retournée est Laurent Prével
}
