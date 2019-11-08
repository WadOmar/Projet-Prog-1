#include "lib/libgraphique.h"
#include<stdio.h>

// Définition des variables constantes

#define L_FENETRE 1200
#define H_FENETRE 700

#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

#define TAB_HAUT 100
#define TAB_DROITE 400

#define XB1 1000
#define YB1 150
#define XB2 1000 
#define YB2 200
#define XB3 1000
#define YB3 250
#define XB4 1000
#define YB4 250

// Prototypes des fonctions
void initialisation(void) ;
int dansDessin(Point posSouris) ;
void bouton(Point posSouris, int x, int y, int l, int h, Couleur cb, Couleur cs, int outilSelect) ;
void fill (Couleur couleur) ;
void affichage(void) ;
void chargement(void) ;
void menu(void) ;
void gestionOutils(void) ;
//void texte()
void dessinBoutons(void) ;
void afficherAide(char *aide, int taille) ;

void segment(void) ;
void rectangleVide(void) ;
void cercleVide(void) ;
void polygoneVide(void) ;
// Déclaration des variables globales

static int outil = -1;
static int couleur = -1;

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
	initialisation();
	int dansPaint = 1 ;
	
	while (dansPaint == 1)
		{
			affichage();
			gestionOutils();
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
	Point pSeg1 = {XB1 + 10, YB1 + 10}, pSeg2 =  {XB1 + 30, YB1 + 40} ;
	Point pRect1 = {XB2 + 10, YB2 + 10}, pRect2 =  {XB2 + 30, YB2 + 30};
	Point pRect3 = {XB2 + 30, YB2 + 40}, pRect4 = {XB2 + 10, YB2 + 40};
	clic = clic_a_eu_lieu() ;


	if (posSouris.x > coin.x && posSouris.x < coin.x + l && posSouris.y > coin.y && posSouris.y < coin.y + h)
		{
		dessiner_rectangle(coin, l, h, cs);
		
		if (clic.x != -1 && clic.y != -1)
			{
			outil = outilSelect ;
			
			if (outilSelect == 666)
				initialisation () ;
			}
		}
	else 
		dessiner_rectangle(coin, l, h, cb) ;
	
	switch (outilSelect)
		{
		case 0 :
			dessiner_ligne (pSeg1, pSeg2, blanc) ;
			break ;		
		case 1 :
			dessiner_ligne (pRect1, pRect2, blanc) ;
			dessiner_ligne (pRect2, pRect3, blanc) ;
			dessiner_ligne (pRect3, pRect4, blanc) ;
			dessiner_ligne (pRect4, pRect1, blanc) ;
			break ;
		case 2 :
			
			break ;
		case 3 :
			
			break ;
		}
	}
void chargement(void)
	{
	int progression = 0;
	//char chargement[12] = "CHARGEMENT\0";
	
	Point milieu = {L_FENETRE/2 - 250, H_FENETRE/2 - 50} ;
	Point logo = {milieu.x + 250, milieu.y + 130} ;

	fill(palegreen) ;
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
void initialisation(void)
	{
	Point coin0 = {0,0}, coin1 = {0,150}, coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	
	fill (navajowhite) ;
	dessiner_rectangle(coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(coin2, TAB_DROITE, TAB_HAUT, rouge) ;	
	}

void affichage(void)
	{
	dessinBoutons();
	actualiser() ;
	}

void dessinBoutons(void)
	{
	traiter_evenements() ;
	Point posSouris = deplacement_souris_a_eu_lieu() ;
	
	bouton(posSouris, ZONE_DESSIN_LONGUEUR, 0, TAB_DROITE, TAB_HAUT, darkred, red, 666) ;	
	
	bouton(posSouris, XB1, YB1, 50, 50, violet, violetlight, (int)SEGMENT) ;
	bouton(posSouris, XB2, YB2 + 100, 50, 50, violet, violetlight, (int)RECTANGLE_VIDE) ;
	bouton(posSouris, XB3, YB3 + 200, 50, 50, violet, violetlight, (int)CERCLE_VIDE) ;
	bouton(posSouris, XB4, YB4 + 300, 50, 50, violet,	violetlight, (int)POLYGONE_VIDE) ;
	reinitialiser_evenements() ;
	}

void gestionOutils(void)
	{
	switch (outil)
		{
		case 0 :
			afficherAide("Ceci est un segment", 20) ;
			segment() ;
			break ;		
		case 1 :
			rectangleVide() ;
			break ;
		case 2 :
			cercleVide() ;
			break ;
		case 3 :
			polygoneVide() ;
			break ;
		}
	}

void afficherAide(char *aide, int taille)
	{
	Point coin = {0,TAB_HAUT} ;
	dessiner_rectangle(coin, ZONE_DESSIN_LONGUEUR, 50, noir) ;
	//afficher_texte(aide, taille, coin, blanc) ;
	actualiser () ;
	}
int dansDessin(Point posSouris)
	{
	if (posSouris.x >= 0 && posSouris.x <= ZONE_DESSIN_LONGUEUR && posSouris.y >= (TAB_HAUT + 50) && posSouris.y <= ZONE_DESSIN_LARGEUR)
		return 1 ;
	else
		return 0 ;
	}

void segment (void)
	{
	Point p1, p2 ;	
	p1 = attendre_clic();
	p2 = attendre_clic();
	if (dansDessin(p1) == 1 && dansDessin(p2) == 1)
		dessiner_ligne(p1,p2, vert);
	outil = -1 ;
	}

void rectangleVide (void)
	{
	Point p1, p2, p3, p4;
	p1 = attendre_clic();
	p2 = attendre_clic();
	p3.x = p2.x;
	p3.y = p1.y;
	p4.x = p1.x;
	p4.y = p2.y;
	
	if (dansDessin(p1) == 1 && dansDessin(p2) == 1 && dansDessin(p3) == 1 && dansDessin(p4) == 1)
		{
		dessiner_ligne(p1, p3, bleu);
		dessiner_ligne(p1, p4, bleu);
		dessiner_ligne(p2, p4, bleu);
		dessiner_ligne(p3, p2, bleu);
		}
	outil = -1 ;
	}

void cercleVide(void)
	{

	}

void polygoneVide(void)
	{
	Point p1, p2, p3;
	int clicDroit = 0 ;
	
	p1 = attendre_clic_gauche_droite() ;
	p2 = attendre_clic_gauche_droite() ;
	
	if (dansDessin(p1) == 1 && dansDessin(p2) == 1)
		{
		dessiner_ligne(p1, p2, bleu) ;
		actualiser () ;
		while (clicDroit == 0)
			{
			p3 = attendre_clic_gauche_droite() ;
			if (p3.x < 0)
				{
				p3.x = -p3.x ;
				p3.y = -p3.y ;
				dessiner_ligne (p2, p1, bleu) ;
				clicDroit = 1 ;
				outil = -1 ;
				}
			else
				dessiner_ligne (p2, p3, bleu) ;
			
			actualiser () ;
				
			p2.x = p3.x;
			p2.y = p3.y ;
			}
		}

	}
