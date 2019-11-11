/* Directives de preprocesseur*/
#include "lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

/* Constantes de préprocesseur */

/* Dimensions de la fenetre */
#define L_FENETRE 1200
#define H_FENETRE 700

/* Dimensions de la zone consacree au dessin */
#define ZONE_DESSIN_LONGUEUR 1000
#define ZONE_DESSIN_LARGEUR 800

/* Dimensions des differents onglets */
#define TAB_HAUT 100
#define TAB_DROITE 400

/* Positions (x;y) des boutons */
#define XB1 1035
#define YB1 170
#define XB2 1010 
#define YB2 240
#define XB3 1050
#define YB3 310
#define XB4 1085
#define YB4 170
#define XB5 1060
#define YB5 240
#define XB6 1060
#define YB6 310
#define XB7 1100
#define YB7 450
#define XB8 1110
#define YB8 240

/* Positions (x;y) des palettes de couleurs */
#define XP1 600
#define YP1 5
#define XP2 900
#define YP2 5

/* Positions (x;y) des tailles des traits */
#define XT1 100
#define YT1 60
#define XT2 170
#define YT2 60
#define XT3 240
#define YT3 60

/* Taille des traits */
#define TAILLE_PETIT 0
#define TAILLE_MOYEN 1
#define TAILLE_GRAND 2


/* Prototypes des fonctions */

void bouton(int x, int y, int l, int h, Couleur cb, Couleur cs, int i_outilSelect) ;
void boutonT(int x, int y, int l, int h, Couleur cb, Couleur cs) ;
void tailleTraits(int x, int y, int i_tailleTrait) ;
void afficherAide(char *aide, int taille) ;
int dansDessin(Point P_point) ;
void fill (Couleur couleur) ;
void gestionCouleurs(void) ;
void initialisation(void) ;
void gestionOutils(void) ;
void dessinBoutons(void) ;
void dessinBoutonsTraits(void) ;
void chargement(void) ;
void affichage(void) ;
void menu(void) ;
//void texte()

void gomme(void) ;
void segment(void) ;
void rectangleVide(void) ;
void cercleVide(void) ;
void polygoneVide(void) ;
void rectanglePlein(void) ;
void cerclePlein(void) ;
void rectangleRaye(void) ;
void remplissage(int x, int y, Couleur ac, Couleur nc) ;

/* Déclaration et initialistion des variables globales */

static Couleur C_couleurTrait = blanc; 
static Couleur C_couleurRemp = blanc;
static Point P_posSouris ;
static int i_outil = -1 ; // Correspond à l'outil selectionné
static Point P_clic ;
static int b_esc ;
static int b_clicGauche ;
static int i_tailleTrait ;

/* Déclaration des nouveaux types */

typedef enum
	{
	REMPLISSAGE = 0,
	SEGMENT,
	RECTANGLE_VIDE,
	CERCLE_VIDE,
	POLYGONE_VIDE,
	RECTANGLE_PLEIN,
	CERCLE_PLEIN,
	RECTANGLE_RAYE
	} i_outils ;

int main(int argc, char *argv[])
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE) ;

	chargement() ;
	//menu() ;
	initialisation() ;
	int i_dansPaint = 1 ;
	
	while (i_dansPaint == 1)
		{
		traiter_evenements() ;

		P_clic = clic_a_eu_lieu() ;
		P_posSouris = deplacement_souris_a_eu_lieu() ;
		b_esc = touche_a_ete_pressee(SDLK_SPACE) ;
		b_clicGauche = touche_a_ete_pressee(SDLK_SPACE) ;
		affichage() ;
		gestionOutils() ;
		gestionCouleurs() ;

		reinitialiser_evenements() ;
		}
	
	//fin du programme

	fermer_fenetre() ;
	
	return 0 ;
	}

// Fonctions 

void fill(Couleur couleur)
	{
	Point p_coin = {0,0} ;
	dessiner_rectangle (p_coin, L_FENETRE, H_FENETRE, couleur) ;
	}

void bouton(int x, int y, int l, int h, Couleur cb, Couleur cs, int i_outilSelect)
	{
	Point p_coin = {x, y};

	if (P_posSouris.x > p_coin.x && P_posSouris.x < p_coin.x + l && P_posSouris.y > p_coin.y && P_posSouris.y < p_coin.y + h)
		{
		dessiner_rectangle(p_coin, l, h, cs) ;
		
		if (P_clic.x != -1 && P_clic.y != -1)
			{
			i_outil = i_outilSelect ;
			
			if (i_outilSelect == 666)
				initialisation () ;
			}
		}
	else 
		dessiner_rectangle(p_coin, l, h, cb) ;
	}

void boutonT(int x, int y, int l, int h, Couleur cb, Couleur cs)
	{	
	Point p_coin = {x, y};

	if (P_posSouris.x > p_coin.x && P_posSouris.x < p_coin.x + l && P_posSouris.y > p_coin.y && P_posSouris.y < p_coin.y + h)
		dessiner_rectangle(p_coin, l, h, cs) ;
	else
		dessiner_rectangle(p_coin, l, h, cb) ;
	}
	
void tailleTraits(int x, int y, int i_tailleTrait)
	{
	Point p_coin1 = {x , y};
	
	if (P_clic.x == XT1  && P_clic.y == YT1)
		i_tailleTrait == 0;
	else if (P_clic.x == XT2  && P_clic.y == YT2)
		i_tailleTrait == 1;
	else if (P_clic.x == XT3  && P_clic.y == YT3)
		i_tailleTrait == 2;
	}

void chargement(void)
	{
	int i_progression = 0 ;
	
	Point p_milieu = {L_FENETRE/2 - 250, H_FENETRE/2} ;
	Point p_logo = {p_milieu.x + 250, p_milieu.y + 130} ;
	Point p_chargement = {p_milieu.x + 150, p_milieu.y + 20} , p_fake = {p_chargement.x, p_chargement.y + 50};
	fill(noir) ;
	afficher_texte("CHARGEMENT", 30, p_chargement, blanc) ;
	while (i_progression < 500)
		{
		afficher_image("images/logoCpaint.bmp", p_logo) ;
		dessiner_rectangle(p_milieu, i_progression, 20, rouge) ;
		actualiser() ;
		i_progression ++ ;
		attente(3) ;
		if (i_progression == 250)
			afficher_texte("C'est faux (:", 30, p_fake, palegreen) ;
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
	Point p_coin0 = {0,0}, p_coin1 = {0,150}, p_coin2 = {ZONE_DESSIN_LONGUEUR, 0} ;
	Point p_palette1 = {XP1, YP1}, p_palette2 = {XP2, YP2} ;
	Point p_txtP1 = {XP1 - 110, YP1 + 32}, p_txtP2 = {XP2 - 180, YP2 + 32} ;

	fill (navajowhite) ;
	dessiner_rectangle(p_coin0, ZONE_DESSIN_LONGUEUR, TAB_HAUT, gris) ;
	dessiner_rectangle(p_coin1, ZONE_DESSIN_LONGUEUR, ZONE_DESSIN_LARGEUR, blanc) ;
	dessiner_rectangle(p_coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	afficher_texte("Couleur trait :", 15, p_txtP1, khaki) ;
	afficher_image("images/roue_chromatique.bmp", p_palette1) ;
	afficher_texte("Couleur remplissage :", 15, p_txtP2, khaki) ;
	afficher_image("images/roue_chromatique.bmp", p_palette2) ;
	}

void affichage(void)
	{
	dessinBoutons() ;
	dessinBoutonsTraits() ;
	actualiser() ;
	}

void dessinBoutons(void)
	{
	Point p_rect1 = {XB2 + 5, YB2 + 12}, p_rect2 =  {XB2 + 45, YB2 + 12}, p_rect3 = {XB2 + 45, YB2 + 38}, p_rect4 = {XB2 + 5, YB2 + 38} ;
	Point p_pol1 = {XB4 + 15, YB4 + 10}, p_pol2 =  {XB4 + 30, YB4 + 12}, p_pol3 = {XB4 + 40, YB4 + 25} ;
	Point p_pol4 =  {XB4 + 25, YB4 + 40}, p_pol5 = {XB4 + 13, YB4 + 35} ;
	Point p_seg1 = {XB1 + 10, YB1 + 10}, p_seg2 =  {XB1 + 30, YB1 + 40} ;
	Point p_cercleV = {XB3 + 25, YB3 + 25} ;
	Point p_rectP1 = {XB5 + 5, YB5 + 12}, p_rectP2 = {p_rectP1.x + 1, p_rectP1.y + 1} ;
	Point p_cercleP = {XB6 + 20, YB6 + 25} ;

	/*CLEAR : */
	bouton(ZONE_DESSIN_LONGUEUR, 0, TAB_DROITE, TAB_HAUT, darkred, red, 666) ;	

	/*SEGMENT : */
	bouton(XB1, YB1, 50, 50, violet, violetlight, (int)SEGMENT) ;
	dessiner_ligne (p_seg1, p_seg2, C_couleurTrait) ;
	
	/*RECTANGLE_VIDE : */
	bouton(XB2, YB2, 50, 50, violet, violetlight, (int)RECTANGLE_VIDE) ;
	dessiner_ligne (p_rect1, p_rect2, C_couleurTrait) ;
	dessiner_ligne (p_rect2, p_rect3, C_couleurTrait) ;
	dessiner_ligne (p_rect3, p_rect4, C_couleurTrait) ;
	dessiner_ligne (p_rect4, p_rect1, C_couleurTrait) ;

	/*CERCLE_VIDE : */
	bouton(XB3, YB3, 50, 50, violet, violetlight, (int)CERCLE_VIDE) ;
	dessiner_cercle (p_cercleV, 15, C_couleurTrait) ;

	/*POLYGONE_VIDE : */
	bouton(XB4, YB4, 50, 50, violet, violetlight, (int)POLYGONE_VIDE) ;
	dessiner_ligne (p_pol1, p_pol2, C_couleurTrait) ;
	dessiner_ligne (p_pol2, p_pol3, C_couleurTrait) ;
	dessiner_ligne (p_pol3, p_pol4, C_couleurTrait) ;
	dessiner_ligne (p_pol4, p_pol5, C_couleurTrait) ;
	dessiner_ligne (p_pol5, p_pol1, C_couleurTrait) ;

	/*RECTANGLE_PLEIN : */
	bouton(XB5, YB5, 50, 50, violet, violetlight, (int)RECTANGLE_PLEIN) ;
	dessiner_rectangle(p_rectP1, 40, 26, C_couleurTrait) ;
	dessiner_rectangle(p_rectP2, 38, 24, C_couleurRemp) ;

	/*CERCLE_PLEIN : */
	bouton(XB6, YB6, 50, 50, violet, violetlight, (int)CERCLE_PLEIN) ;
	dessiner_disque (p_cercleP, 15, C_couleurTrait) ;
	dessiner_disque (p_cercleP, 14, C_couleurRemp) ;	
	
	/*RECTANGLE_RAYE : */
	bouton(XB8, YB8, 50, 50, violet, violetlight, (int)RECTANGLE_RAYE) ;
	
	/*REMPLISSAGE : */
	bouton(XB7, YB7, 66, 66, violet, violetlight, (int)REMPLISSAGE) ;
	}

void dessinBoutonsTraits(void)
	{
	boutonT(XT1, YT1, 70, 25, violet, violetlight);
	boutonT(XT2, YT2, 70, 25, violet, violetlight);
	boutonT(XT3, YT3, 70, 25, violet, violetlight);
	}	

void gestionOutils(void)
	{
	Point clic ;
	switch (i_outil)
		{
		case (int)SEGMENT :
			afficherAide("Choissisez 2 points pour dessiner un segment", 20) ;
			segment() ;
			break ;		
		case (int)RECTANGLE_VIDE :
			afficherAide("Choissisez 2 points pour dessiner un rectangle vide", 20) ;
			rectangleVide() ;
			break ;
		case (int)CERCLE_VIDE :
			afficherAide("Choissisez 2 points, le premier definira le centre, le deuxieme definira le rayon", 20) ;
			cercleVide() ;
			break ;
		case (int)POLYGONE_VIDE :
			afficherAide("Le clic gauche definit les sommets, le clic droit permet de fermer le polygone", 20) ;
			polygoneVide() ;
			break ;
		case (int)RECTANGLE_PLEIN :
			afficherAide("Choissisez 2 points pour dessiner un rectangle plein", 20) ;
			rectanglePlein() ;
			break ;
		case (int)CERCLE_PLEIN:
			afficherAide("Choissisez 2 points, le premier definira le centre, le deuxieme definira le rayon", 20) ;
			cerclePlein() ;
			break ;
		case (int)RECTANGLE_RAYE:
			rectangleRaye() ;
			break ;
		case (int)REMPLISSAGE:
			afficherAide("Appuyez n'importe ou dans la zone de dessin, et votre forme se remplira de la couleur de remplissage", 18) ;
			clic = attendre_clic() ;
			Couleur ac = couleur_point (clic), nc = C_couleurRemp;
			remplissage(clic.x, clic.y, ac, nc) ;
			i_outil = -1 ;
			break ;
		}
	}

void gestionCouleurs (void)
	{
	if (P_clic.x >= XP1 && P_clic.x <= XP1 + 90 && P_clic.y >= YP1 && P_clic.y <= YP1 + 90)
		C_couleurTrait = couleur_point (P_clic) ;
	else if (P_clic.x >= XP2 && P_clic.x <= XP2 + 90 && P_clic.y >= YP2 && P_clic.y <= YP2 + 90)
		C_couleurRemp = couleur_point (P_clic) ;
	}

void afficherAide(char *aide, int taille)
	{
	Point p_coin = {0,TAB_HAUT} ;
	dessiner_rectangle(p_coin, ZONE_DESSIN_LONGUEUR, 50, noir) ;
	afficher_texte(aide, taille, p_coin, blanc) ;
	actualiser() ;
	}

int dansDessin(Point P_point)
	{
	if (P_point.x < 0)
		{
		P_point.x = -P_point.x ;
		P_point.y = -P_point.y ;
		}	
	if (P_point.x >= 0 && P_point.x <= ZONE_DESSIN_LONGUEUR && P_point.y >= (TAB_HAUT + 50) && P_point.y <= H_FENETRE)
		return 1 ;
	else
		return 0 ;
	}

void remplissage (int x, int y, Couleur ac, Couleur nc)
	{
	Point p = {x, y} ;
	if( couleur_point (p) != ac || dansDessin(p) == 0)
		return ;

	changer_pixel(p, nc);

	remplissage(x+1, y, ac, nc);
	remplissage(x-1, y, ac, nc);
	remplissage(x, y+1, ac, nc);
	remplissage(x, y-1, ac, nc);
	}

void segment (void)
	{
	Point p_p1, p_p2 ;	
	p_p1 = attendre_clic() ;
	p_p2 = attendre_clic() ;
	if (dansDessin(p_p1) == 1 && dansDessin(p_p2) == 1)
		if (i_tailleTrait == 0)
			dessiner_ligne(p_p1,p_p2, C_couleurTrait) ;
		else if (i_tailleTrait == 1)
			{
			dessiner_ligne(p_p1,p_p2, C_couleurTrait) ;
			dessiner_ligne(p_p1 + 1,p_p2 + 1, C_couleurTrait) ;
			}
		else if (i_tailleTrait == 2)
			{
			dessiner_ligne(p_p1,p_p2, C_couleurTrait) ;
			dessiner_ligne(p_p1 + 1,p_p2 + 1, C_couleurTrait) ;
			dessiner_ligne(p_p1 + 2,p_p2 + 2, C_couleurTrait) ;
			}
	i_outil = -1 ;
	}

void rectangleVide (void)
	{
	Point p_p1, p_p2, p_p3, p_p4 ;
	p_p1 = attendre_clic() ;
	p_p2 = attendre_clic() ;
	p_p3.x = p_p2.x ;
	p_p3.y = p_p1.y ;
	p_p4.x = p_p1.x ;
	p_p4.y = p_p2.y ;
	
	if (dansDessin(p_p1) == 1 && dansDessin(p_p2) == 1)
		{
		dessiner_ligne(p_p1, p_p3, C_couleurTrait) ;
		dessiner_ligne(p_p1, p_p4, C_couleurTrait) ;
		dessiner_ligne(p_p2, p_p4, C_couleurTrait) ;
		dessiner_ligne(p_p3, p_p2, C_couleurTrait) ;
		}
	i_outil = -1 ;
	}

void cercleVide(void)
	{
	Point p_p1 = attendre_clic() ;
	Point p_p2 = attendre_clic() ;

	int rayon = sqrt(pow((p_p2.x - p_p1.x),2) + pow((p_p2.y - p_p1.y),2)) ;

	Point p_limiteHaut = {p_p1.x, p_p1.y - rayon}, p_limiteBas = {p_p1.x, p_p1.y + rayon} ;
	Point p_limiteDroite = {p_p1.x + rayon, p_p1.y}, p_limiteGauche = {p_p1.x - rayon, p_p1.y} ;
	if (dansDessin(p_limiteHaut) == 1 && dansDessin(p_limiteBas) == 1 && dansDessin(p_limiteDroite) == 1 && dansDessin(p_limiteGauche) == 1)
		dessiner_cercle (p_p1, rayon, C_couleurTrait) ;

	i_outil = -1 ;
	}

void polygoneVide(void)
	{
	Point p_p1, p_p2, p_p3 ;
	int p_clicDroit = 0 ;
	
	p_p1 = attendre_clic_gauche_droite() ;
	p_p2 = attendre_clic_gauche_droite() ;
	
	if (dansDessin(p_p1) == 1 && dansDessin(p_p2) == 1)
		{
		dessiner_ligne(p_p1, p_p2, C_couleurTrait) ;
		actualiser () ;
		while (p_clicDroit == 0)
			{
			p_p3 = attendre_clic_gauche_droite() ;
			if (dansDessin(p_p3) == 1)
				{
				if (p_p3.x < 0)
					{
					p_p3.x = -p_p3.x ;
					p_p3.y = -p_p3.y ;
					dessiner_ligne (p_p2, p_p1, C_couleurTrait) ;
					p_clicDroit = 1 ;
					}
				else
					dessiner_ligne (p_p2, p_p3, C_couleurTrait) ;
				
				actualiser () ;
					
				p_p2.x = p_p3.x ;
				p_p2.y = p_p3.y ;
				}
			}
		}
	i_outil = -1 ;
	}

void rectanglePlein(void)
	{
	Point p_p1 = attendre_clic() ;
	Point p_p2 = attendre_clic() ;
	int i_largeur = abs(p_p2.x - p_p1.x), i_hauteur = abs(p_p2.y - p_p1.y) ;
	Point p_coin ;

	if (dansDessin(p_p1) == 1 && dansDessin(p_p2) == 1)	
		{	
		if (p_p1.x < p_p2.x && p_p1.y < p_p2.y)		
			p_coin = p_p1 ;
		else if (p_p1.x < p_p2.x && p_p1.y > p_p2.y)
			{
			p_coin.x = p_p1.x ;
			p_coin.y = p_p2.y ;
			}
		else if (p_p1.x > p_p2.x && p_p1.y < p_p2.y)
			{
			p_coin.x = p_p2.x ;
			p_coin.y = p_p1.y ;
			}
		else 
			p_coin = p_p2 ;

		Point p_coinInt = {p_coin.x + 2, p_coin.y + 2} ;
		dessiner_rectangle (p_coin, i_largeur, i_hauteur, C_couleurTrait) ;
		dessiner_rectangle (p_coinInt, i_largeur - 4, i_hauteur - 4, C_couleurRemp) ;		
		}
	i_outil = -1 ;
	}

void cerclePlein(void)
	{
	Point p_p1 = attendre_clic() ;
	Point p_p2 = attendre_clic() ;

	int rayon = sqrt(pow((p_p2.x - p_p1.x),2) + pow((p_p2.y - p_p1.y),2)) ;
	
	Point p_limiteHaut = {p_p1.x, p_p1.y - rayon}, p_limiteBas = {p_p1.x, p_p1.y + rayon} ;
	Point p_limiteDroite = {p_p1.x + rayon, p_p1.y}, p_limiteGauche = {p_p1.x - rayon, p_p1.y} ;
	if (dansDessin(p_limiteHaut) == 1 && dansDessin(p_limiteBas) == 1 && dansDessin(p_limiteDroite) == 1 && dansDessin(p_limiteGauche) == 1)
		{	
		dessiner_disque (p_p1, rayon, C_couleurTrait) ;
		dessiner_disque (p_p1, rayon - 2, C_couleurRemp) ;
		}
	i_outil = -1 ;
	}

void rectangleRaye(void)
	{
	Point p_p1, p_p2, p_p3, p_p4, p_r1, p_r2 ;
	p_p1 = attendre_clic() ;
	p_p2 = attendre_clic() ;
	
	int i_longueur = abs(p_p2.x - p_p1.x) ;

	p_p3.x = p_p2.x ;
	p_p3.y = p_p1.y ;
	p_p4.x = p_p1.x ;
	p_p4.y = p_p2.y ;
	

	p_r1.y = p_p1.y ;
	p_r2.y = p_p2.y ;

	if (dansDessin(p_p1) == 1 && dansDessin(p_p2) == 1)
		{
		dessiner_ligne(p_p1, p_p3, C_couleurTrait) ;
		dessiner_ligne(p_p1, p_p4, C_couleurTrait) ;
		dessiner_ligne(p_p2, p_p4, C_couleurTrait) ;
		dessiner_ligne(p_p3, p_p2, C_couleurTrait) ;
		}

	for (int iX = p_p1.x; iX < i_longueur; iX += 20)
		{
		p_r1.x = iX ;
		p_r2.x = iX ;
		
		dessiner_ligne (p_r1, p_r2, C_couleurRemp) ;
		}

	i_outil = -1 ;
	}
