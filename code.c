#include "lib/libgraphique.h"
#include<stdio.h>

#define L_FENETRE 1200
#define H_FENETRE 700

#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

#define TAB_HAUT 100
#define TAB_DROITE 400

void bouton(Point posSouris, int x, int y, int l, int h, Couleur cs, Couleur cc) ;
void affichage(void) ;
void chargement(void) ;
void menu(void) ;

int main(void)
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE);
	
	chargement() ;
	menu() ;
	
	affichage() ;

	//fin du programme
	attendre_clic() ;
	fermer_fenetre() ;
	return 0 ;
	}

void bouton(Point posSouris, int x, int y, int l, int h, Couleur cs, Couleur cc)
	{
	printf("Bouton") ;
	}
void chargement(void)
	{
	int progression = 0;
	//char chargement[] = "CHARGEMENT";
	Point coin0 = {0,0}, milieu = {L_FENETRE/2 - 250, H_FENETRE/2 - 50};
	dessiner_rectangle(coin0, L_FENETRE, H_FENETRE, jaune) ;
	//afficher_texte(chargement, 20, milieu, blanc) ;
	while (progression < 500)
		{
		dessiner_rectangle(milieu, progression, 100, rouge) ;
		actualiser() ;
		progression ++ ;
		attente(3) ;
		}
	}

void menu(void)
	{
	traiter_evenements() ;
	Point posSouris = deplacement_souris_a_eu_lieu() ;	
 	reinitialiser_evenements() ;
	}

void affichage(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	actualiser() ;
	}
