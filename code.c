#include "lib/libgraphique.h"
#include<stdio.h>

// Définition des variables constantes

#define L_FENETRE 1200
#define H_FENETRE 700

#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

#define TAB_HAUT 100
#define TAB_DROITE 400

#define NBOUTILS 1

// Prototypes des fonctions
int dansDessin(Point posSouris) ;
void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs, int outil) ;
void fill (Couleur couleur) ;
void affichage(void) ;
void chargement(void) ;
void menu(void) ;
void lancement(void) ;
void gestionOutils(void) ;
//void texte()

void cercleVide() ;
// Déclaration des variables globales

int outil ;

// Main

int main(int argc, char *argv[])
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE) ;
	
	chargement() ;
	//menu() ;
	
	int dansPaint = 1 ;
	
	while (dansPaint == 1)
		{
		gestionOutils() ;
		affichage() ;
		}
	
	//fin du programme
	
	//attendre_clic() ;
	fermer_fenetre() ;
	
	return 0 ;
	}

// Fonctions 

void fill(Couleur couleur)
	{
	Point coin = {0,0};
	dessiner_rectangle (coin, L_FENETRE, H_FENETRE, couleur) ;
	}

void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs, int outilSelect)
	{
	extern int outil ;
	Point coin = {x-l/2, y-h/2}, clic ;

	clic = clic_a_eu_lieu() ;
	
	if (posSouris.x > coin.x && posSouris.x < coin.x + l && posSouris.y > coin.y && posSouris.y < coin.y + h)
		{
		dessiner_rectangle(coin, l, h, cs) ;
		
		if (clic.x != -1 && clic.y != -1)
			{
			outil = outilSelect ;
			}
		}
	else 
		dessiner_rectangle(coin, l, h, cb) ;
	}

void chargement(void)
	{
	int progression = 0;
	//char chargement[12] = "CHARGEMENT\0";
	
	Point milieu = {L_FENETRE/2 - 250, H_FENETRE/2 - 50} ;
	Point logo = {milieu.x + 250, milieu.y + 130} ;

	fill(noir) ;
	afficher_texte("a\0", 20, milieu, blanc) ;
	while (progression < 500)
		{
		afficher_image("logoCpaint.bmp", logo) ;
		dessiner_rectangle(milieu, progression, 100, rouge) ;
		actualiser() ;
		progression ++ ;
		attente(3) ;
		}
	}

/*
void menu(void)
	{
	extern int dansMenu ;
	dansMenu = 1 ;
	while (dansMenu == 1)
		{
		fill(blanc) ;
		traiter_evenements() ;
		Point posSouris = deplacement_souris_a_eu_lieu() ;	
		bouton(posSouris, 500, 300, 200, 100, violet, violetlight, lancement) ;
		reinitialiser_evenements() ;
		actualiser() ;
		}
	}

void lancement(void)
	{
	extern int dansMenu ;
	dansMenu = 0 ;
	}
*/

void affichage(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	fill (navajowhite) ;
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	actualiser() ;
	}

void gestionOutils(void)
	{
	extern int outil ;
	
	Point coin1 = {TAB_DROITE, TAB_HAUT} ;
	
	}

int dansDessin(Point posSouris)
	{
	//if (posSouris.x >= 0 && posSouris.x <= ZONE_DESSIN_LONGUEUR)
	}
