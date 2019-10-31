#include "lib/libgraphique.h"
#include<stdio.h>

#define L_FENETRE 1200
#define H_FENETRE 700

#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

#define TAB_HAUT 100
#define TAB_DROITE 400

void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs) ;
void fill (Couleur couleur) ;
void affichage(void) ;
void chargement(void) ;
void menu(void) ;

int main(void)
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE);
	
	chargement() ;
	//menu() ;
	affichage() ;

	//fin du programme
	attendre_clic() ;
	fermer_fenetre() ;
	return 0 ;
	}

void fill(Couleur couleur)
	{
	Point coin = {0,0};
	dessiner_rectangle (coin, L_FENETRE, H_FENETRE, couleur) ;
	}

void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs)
	{
	Point coin = {x-l/2, y-h/2}, clic;

	clic = clic_a_eu_lieu() ;
	
	if (posSouris.x > coin.x && posSouris.x < coin.x + l && posSouris.y > coin.y && posSouris.y < coin.y + h)
		{
		dessiner_rectangle(coin, l, h, cs) ;
		
		if (clic.x != -1 && clic.y != -1)
			printf ("clic") ;
		}
	else 
		dessiner_rectangle(coin, l, h, cb) ;
	}

void chargement(void)
	{
	int progression = 0;
	//char chargement[] = "CHARGEMENT";
	Point milieu = {L_FENETRE/2 - 250, H_FENETRE/2 - 50};
	fill(jaune) ;
	//afficher_texte(chargement, 20, milieu, blanc) ;
	while (progression < 500)
		{
		dessiner_rectangle(milieu, progression, 100, rouge) ;
		actualiser() ;
		progression ++ ;
		attente(1) ;
		}
	}

/*
void menu(void)
	{
	int dansMenu = 1 ;
	while (dansMenu == 1)
		{
		fill(blanc) ;
		traiter_evenements() ;
		Point posSouris = deplacement_souris_a_eu_lieu() ;	
		bouton(posSouris, 500, 300, 200, 100, violet, violetlight) ;
		reinitialiser_evenements() ;
		actualiser() ;
		}
	}
*/

void affichage(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	actualiser() ;
	}
