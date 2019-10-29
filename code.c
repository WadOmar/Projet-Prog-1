#include "lib/libgraphique.h"
#include<stdio.h>

#define L_FENETRE 1200
#define H_FENETRE 900

#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

#define TAB_HAUT 100
#define TAB_BAS 100
#define TAB_DROITE 400


void affichage(void) ;

int main(void)
    {
    ouvrir_fenetre(L_FENETRE, H_FENETRE);
	
    affichage() ;
 
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }

void affichage(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	actualiser() ;
	}


