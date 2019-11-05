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
void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs, int outilSelect) ;
void fill (Couleur couleur) ;
void affichage(void) ;
void chargement(void) ;
void menu(void) ;
void gestionOutils(void) ;
//void texte()
void dessinBoutons(void) ;

void cercleVide() ;
// Déclaration des variables globales

static int outil = -1;

typedef enum
	{
	SEGMENT = 0,
	RECTANGLE_VIDE,
	CERCLE_VIDE,
	POLYGONE_VIDE,
	RECTANGLE_PLEIN,
	CERCLE_PLEIN,
	POLYGONE_PLEIN
	} outils ;
// Main

int main(int argc, char *argv[])
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE) ;
	
	chargement() ;
	//menu() ;
	
	int dansPaint = 1 ;
	
	while (dansPaint == 1)
		{
			gestionOutils();
			affichage();
			
		}
	
	//fin du programme

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
	Point coin = {x, y}, clic ;

	clic = clic_a_eu_lieu() ;


	if (posSouris.x > coin.x && posSouris.x < coin.x + l && posSouris.y > coin.y && posSouris.y < coin.y + h)
		{
		printf("(%d, %d) (%d, %d)\n", x, y, clic.x, clic.y);
		dessiner_rectangle(coin, l, h, cs);
		
		if (clic.x != -1 && clic.y != -1)
			{
			outil = outilSelect ;
			printf("clic !\n") ;
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
	//afficher_texte("a\0", 20, milieu, blanc) ;
	while (progression < 500)
		{
		afficher_image("logoCpaint.bmp", logo) ;
		dessiner_rectangle(milieu, progression, 100, rouge) ;
		actualiser() ;
		progression ++ ;
		attente(1) ;
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
		attendre_touche() ;
		actualiser() ;
		}
	}
*/

void affichage(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	fill (navajowhite) ;
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;

	dessinBoutons();


	actualiser() ;
	}

void dessinBoutons(void)
	{
	//reinitialiser_evenements() ;
	traiter_evenements() ;
	Point posSouris = deplacement_souris_a_eu_lieu() ;
	bouton(posSouris, ZONE_DESSIN_LONGUEUR, TAB_HAUT, 50, 50, violet, violetlight, (int)SEGMENT) ;
	bouton(posSouris, ZONE_DESSIN_LONGUEUR, TAB_HAUT + 100, 50, 50, violet, violetlight, (int)RECTANGLE_VIDE) ;
	bouton(posSouris, ZONE_DESSIN_LONGUEUR, TAB_HAUT + 200, 50, 50, violet, violetlight, (int)CERCLE_VIDE) ;
	bouton(posSouris, ZONE_DESSIN_LONGUEUR, TAB_HAUT + 300, 50, 50, violet,	violetlight, (int)POLYGONE_VIDE) ;
	}

void gestionOutils(void)
	{
	switch (outil)
		{
		case 0 :
			printf("segment\n") ;	
			//dessinerSegment();
			break ;		
		case 1 :
			printf("rectangle Vide\n") ;
			break ;
		case 2 :
			printf("cercle vide\n");
			break ;
		case 3 :
			printf("polygone\n");
			break ;
		}
	}

int dansDessin(Point posSouris)
	{
	if (posSouris.x >= 0 && posSouris.x <= ZONE_DESSIN_LONGUEUR && posSouris.y >= 0 && posSouris.y <= ZONE_DESSIN_LARGEUR)
		return 1 ;
	else
		return 0 ;
	}
