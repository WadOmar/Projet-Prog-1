/************************************************************************************************/
/*			cPAINT 					OUADRHIRI - SPINU, Info 1A	*/
/************************************************************************************************/

/* Directives de preprocesseur                                                                  */

#include "lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

/* Constantes de préprocesseur 									*/

/* Dimensions de la fenetre */
#define L_FENETRE 1200
#define H_FENETRE 700

/* Dimensions de la zone consacree au dessin */
#define L_DESSIN 1000
#define H_DESSIN 550

/* Dimensions des differents onglets */
#define TAB_HAUT 100
#define TAB_DROITE 200

/* Positions (x;y) des boutons */
#define X_B_SEGMENT 1050
#define Y_B_SEGMENT 170
#define X_B_POLY_V 1100
#define Y_B_POLY_V 170
#define X_B_RECT_V 1025 
#define Y_B_RECT_V 240
#define X_B_RECT_P 1075
#define Y_B_RECT_P 240
#define X_B_RECT_R 1125
#define Y_B_RECT_R 240
#define X_B_CERCLE_V 1050
#define Y_B_CERCLE_V 310
#define X_B_CERCLE_P 1100
#define Y_B_CERCLE_P 310
#define X_B_REMPL 1000
#define Y_B_REMPL 450
#define X_B_SAUVEGARDE 1000
#define Y_B_SAUVEGARDE 600
#define X_B_LOAD_SAUVEGARDE 1000
#define Y_B_LOAD_SAUVEGARDE 650
#define X_B_TEXTE 1000
#define Y_B_TEXTE 500
#define X_B_GOMME 1000
#define Y_B_GOMME 550

/* Positions (x;y) des palettes de couleurs */
#define XP1 600
#define YP1 5
#define XP2 900
#define YP2 5

/* Prototypes des fonctions 									*/

void bouton(int x, int y, int l, int h, Couleur cb, Couleur cs, int i_outilSelect) ;
void afficherAide(char *aide, int taille) ;
int dansDessin(Point P_point) ;
void fill (Couleur couleur) ;
void gestionCouleurs(void) ;
void initialisation(void) ;
void gestionOutils(void) ;
void dessinBoutons(void) ;
void chargement(void) ;
void affichage(void) ;

void gomme(void) ;
void segment(void) ;
void rectangleVide(void) ;
void cercleVide(void) ;
void polygoneVide(void) ;
void rectanglePlein(void) ;
void cerclePlein(void) ;
void rectangleRaye(void) ;
void remplissage(int x, int y, Couleur ac, Couleur nc) ;
void sauvegarde(void) ;
void loadSauvegarde(void);
void texte(void) ;

/* Déclaration et initialistion des variables globales 						*/

static Couleur C_couleurTrait = noir; 
static Couleur C_couleurRemp = noir;
static Point P_posSouris ;
static int i_outil = -1 ; // Correspond à l'outil selectionné
static Point P_clic ;
static int i_tailleTrait = 1 ;

/* Déclaration des nouveaux types 								*/

typedef enum
	{
	REMPLISSAGE = 0,
	SEGMENT,
	RECTANGLE_VIDE,
	CERCLE_VIDE,
	POLYGONE_VIDE,
	RECTANGLE_PLEIN,
	CERCLE_PLEIN,
	RECTANGLE_RAYE,
	SAUVEGARDE,
	LOAD_SAUVEGARDE,
	TEXTE,
	GOMME
	} i_outils ;

/* MAIN												*/

int main(int argc, char *argv[])
	{
	ouvrir_fenetre(L_FENETRE, H_FENETRE) ;
	SDL_WM_SetCaption("cPaint (mieux que l'original)", NULL);
	SDL_WM_SetIcon(SDL_LoadBMP("images/logoCpaint.bmp"), NULL);

	chargement() ;

	initialisation() ;
	int i_dansPaint = 1 ;
	
	while (i_dansPaint == 1)
		{
		traiter_evenements() ;

		P_clic = clic_a_eu_lieu() ;
		P_posSouris = deplacement_souris_a_eu_lieu() ;
		affichage() ;
		gestionOutils() ;
		gestionCouleurs() ;

		reinitialiser_evenements() ;
		}
	
	//fin du programme

	fermer_fenetre() ;
	
	return 0 ;
	}

/* Fonctions											*/ 

void fill(Couleur couleur)
	{
	Point P_coin = {0,0} ;
	dessiner_rectangle (P_coin, L_FENETRE, H_FENETRE, couleur) ;
	}

void bouton(int x, int y, int l, int h, Couleur cb, Couleur cs, int i_outilSelect)
	{
	Point P_coin = {x, y};

	if (P_posSouris.x > P_coin.x && P_posSouris.x < P_coin.x + l && P_posSouris.y > P_coin.y && P_posSouris.y < P_coin.y + h)
		{
		dessiner_rectangle(P_coin, l, h, cs) ;
		
		if (P_clic.x != -1 && P_clic.y != -1)
			{
			i_outil = i_outilSelect ;
			
			if (i_outilSelect == 666)
				initialisation () ;
			}
		}
	else 
		dessiner_rectangle(P_coin, l, h, cb) ;
	
	}

void chargement(void)
	{
	int i_progression = 0 ;

	Point P_milieu = {L_FENETRE/2 - 250, H_FENETRE/2} ;
	Point P_chargement = {P_milieu.x + 150, P_milieu.y + 20} ;
	Point P_logo = {P_milieu.x + 250, P_milieu.y + 130} ;
	
	fill(noir) ;

	FILE* fichier = NULL ;
	char s_chaine[100] = "";
	int i_ligne = entier_aleatoire(10) ;

	fichier = fopen("quotes.txt", "r+") ;

	if (fichier != NULL)
		{
		for (int iLigne = 0; iLigne < i_ligne; iLigne++) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
			fgets(s_chaine, 100, fichier) ;

		fclose(fichier) ;
		}

	Point P_quote = {L_FENETRE/2 - (taille_texte(s_chaine, 30).x)/2, P_chargement.y + 50};
	Point taille_texte(char *texte, int taille);

	afficher_texte(s_chaine, 30, P_quote, jaune) ;
	afficher_texte("CHARGEMENT", 30, P_chargement, blanc) ;

	while (i_progression < 500)
		{
		afficher_image("images/logoCpaint.bmp", P_logo) ;
		dessiner_rectangle(P_milieu, i_progression, 20, rouge) ;
		actualiser() ;
		i_progression ++ ;
		attente(3) ;
		}
	}

void initialisation(void)
	{
	Point P_coin0 = {0,0}, P_coin1 = {0,150}, P_coin2 = {L_DESSIN, 0} ;
	Point P_palette1 = {XP1, YP1}, P_palette2 = {XP2, YP2} ;
	Point P_txtP1 = {XP1 - 110, YP1 + 32}, P_txtP2 = {XP2 - 180, YP2 + 32} ;

	fill (navajowhite) ;
	dessiner_rectangle(P_coin0, L_DESSIN, TAB_HAUT, gris) ;
	dessiner_rectangle(P_coin1, L_DESSIN, H_DESSIN, blanc) ;
	dessiner_rectangle(P_coin2, TAB_DROITE, TAB_HAUT, rouge) ;
	
	afficher_texte("Couleur trait :", 15, P_txtP1, khaki) ;
	afficher_image("images/roue_chromatique.bmp", P_palette1) ;
	afficher_texte("Couleur remplissage :", 15, P_txtP2, khaki) ;
	afficher_image("images/roue_chromatique.bmp", P_palette2) ;
	}

void affichage(void)
	{
	dessinBoutons() ;
	actualiser() ;
	}

void dessinBoutons(void)
	{
	Point P_rect1 = {X_B_RECT_V + 5, Y_B_RECT_V + 12}, P_rect2 =  {X_B_RECT_V + 45, Y_B_RECT_V + 12} ;
	Point P_rect3 = {X_B_RECT_V + 45, Y_B_RECT_V + 38}, P_rect4 = {X_B_RECT_V + 5, Y_B_RECT_V + 38} ;
	Point P_pol1 = {X_B_POLY_V + 15, Y_B_POLY_V + 10}, P_pol2 =  {X_B_POLY_V + 30, Y_B_POLY_V + 12} ;
	Point P_pol3 = {X_B_POLY_V + 40, Y_B_POLY_V + 25}, P_pol4 =  {X_B_POLY_V + 25, Y_B_POLY_V + 40} ;
	Point P_pol5 = {X_B_POLY_V + 13, Y_B_POLY_V + 35} ;
	Point P_seg1 = {X_B_SEGMENT + 10, Y_B_SEGMENT + 10}, P_seg2 =  {X_B_SEGMENT + 30, Y_B_SEGMENT + 40} ;
	Point P_cercleV = {X_B_CERCLE_V + 25, Y_B_CERCLE_V + 25} ;
	Point P_rectP1 = {X_B_RECT_P + 5, Y_B_RECT_P + 12}, P_rectP2 = {P_rectP1.x + 1, P_rectP1.y + 1} ;
	Point P_cercleP = {X_B_CERCLE_P + 25, Y_B_CERCLE_P + 25} ;
	Point P_rempl = {X_B_REMPL + 30, Y_B_REMPL + 10} ;
	Point P_sauv = {X_B_SAUVEGARDE + 30, Y_B_SAUVEGARDE + 10} ;
	Point P_loadSauv = {X_B_LOAD_SAUVEGARDE + 10, Y_B_LOAD_SAUVEGARDE + 10} ;
	Point P_texte = {X_B_TEXTE + 30, Y_B_TEXTE + 10} ;
	Point P_gomme = {X_B_GOMME + 30, Y_B_GOMME + 10} ;
	
	/*CLEAR : */
	bouton(L_DESSIN, 0, TAB_DROITE, TAB_HAUT, darkred, red, 666) ;	

	/*SEGMENT : */
	bouton(X_B_SEGMENT, Y_B_SEGMENT, 50, 50, violet, violetlight, (int)SEGMENT) ;
	dessiner_ligne (P_seg1, P_seg2, C_couleurTrait) ;
	
	/*RECTANGLE_VIDE : */
	bouton(X_B_RECT_V, Y_B_RECT_V, 50, 50, violet, violetlight, (int)RECTANGLE_VIDE) ;
	dessiner_ligne (P_rect1, P_rect2, C_couleurTrait) ;
	dessiner_ligne (P_rect2, P_rect3, C_couleurTrait) ;
	dessiner_ligne (P_rect3, P_rect4, C_couleurTrait) ;
	dessiner_ligne (P_rect4, P_rect1, C_couleurTrait) ;

	/*CERCLE_VIDE : */
	bouton(X_B_CERCLE_V, Y_B_CERCLE_V, 50, 50, violet, violetlight, (int)CERCLE_VIDE) ;
	dessiner_cercle (P_cercleV, 15, C_couleurTrait) ;

	/*POLYGONE_VIDE : */
	bouton(X_B_POLY_V, Y_B_POLY_V, 50, 50, violet, violetlight, (int)POLYGONE_VIDE) ;
	dessiner_ligne (P_pol1, P_pol2, C_couleurTrait) ;
	dessiner_ligne (P_pol2, P_pol3, C_couleurTrait) ;
	dessiner_ligne (P_pol3, P_pol4, C_couleurTrait) ;
	dessiner_ligne (P_pol4, P_pol5, C_couleurTrait) ;
	dessiner_ligne (P_pol5, P_pol1, C_couleurTrait) ;

	/*RECTANGLE_PLEIN : */
	bouton(X_B_RECT_P, Y_B_RECT_P, 50, 50, violet, violetlight, (int)RECTANGLE_PLEIN) ;
	dessiner_rectangle(P_rectP1, 40, 26, C_couleurTrait) ;
	dessiner_rectangle(P_rectP2, 38, 24, C_couleurRemp) ;

	/*CERCLE_PLEIN : */
	bouton(X_B_CERCLE_P, Y_B_CERCLE_P, 50, 50, violet, violetlight, (int)CERCLE_PLEIN) ;
	dessiner_disque (P_cercleP, 15, C_couleurTrait) ;
	dessiner_disque (P_cercleP, 14, C_couleurRemp) ;	
	
	/*RECTANGLE_RAYE : */
	bouton(X_B_RECT_R, Y_B_RECT_R, 50, 50, violet, violetlight, (int)RECTANGLE_RAYE) ;
	
	/*REMPLISSAGE : */
	bouton(X_B_REMPL, Y_B_REMPL, 200, 50, noir, darkgray, (int)REMPLISSAGE) ;
	afficher_texte("REMPLISSAGE", 17, P_rempl, blanc) ;

	/*SAUVEGARDE : */
	bouton(X_B_SAUVEGARDE, Y_B_SAUVEGARDE, 200, 50, darkgreen, green, (int)SAUVEGARDE) ;
	afficher_texte("SAUVEGARDE", 17, P_sauv, blanc) ;
	
	/*LOAD_SAUVEGARDE : */
	bouton(X_B_LOAD_SAUVEGARDE, Y_B_LOAD_SAUVEGARDE, 200, 50, darkgreen, green, (int)LOAD_SAUVEGARDE) ;
	afficher_texte("IMPORTER SAUVEGARDE", 13, P_loadSauv, blanc) ;

	/*TEXTE : */
	bouton(X_B_TEXTE, Y_B_TEXTE, 200, 50, blue, lightblue, (int)TEXTE) ;
	afficher_texte("TEXTE", 20, P_texte, blanc) ;

	/*GOMME : */
	bouton(X_B_GOMME, Y_B_GOMME, 200, 50, blue, lightblue, (int)GOMME) ;
	afficher_texte("GOMME", 20, P_gomme, blanc) ;
	}

void gestionOutils(void)
	{
	Point clic ;
	switch (i_outil)
		{
		case -1 :
			afficherAide("Selectionnez vos couleurs, puis l'outil qui vous plait", 20) ;
			break ;
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
		case (int)SAUVEGARDE:
			afficherAide("Donnez un nom a votre fichier sur la console.", 18) ;
			sauvegarde() ;
			break ;
		case (int)LOAD_SAUVEGARDE:
			afficherAide("Inserez le nom de votre fichier sur la console.", 18) ;
			loadSauvegarde() ;
			break ;
		case (int)TEXTE:
			afficherAide("Cliquez là ou vous voulez afficher votre texte, puis allez sur la console", 15) ;
			texte() ;
			break ;
		case (int)GOMME:
			afficherAide("Cliquez pour commencer a gommer, recliquez pour arreter.", 18) ;
			gomme() ;
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
	Point P_coin = {0,TAB_HAUT} ;
	dessiner_rectangle(P_coin, L_DESSIN, 50, noir) ;
	afficher_texte(aide, taille, P_coin, blanc) ;
	actualiser() ;
	}

int dansDessin(Point P_point)
	{
	if (P_point.x < 0)
		{
		P_point.x = -P_point.x ;
		P_point.y = -P_point.y ;
		}	
	if (P_point.x >= 0 && P_point.x <= L_DESSIN && P_point.y >= (TAB_HAUT + 50) && P_point.y <= H_FENETRE)
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
	Point P_p1, P_p2 ;	
	P_p1 = attendre_clic() ;
	P_p2 = attendre_clic() ;
	if (dansDessin(P_p1) == 1 && dansDessin(P_p2) == 1)
		dessiner_ligne(P_p1,P_p2, C_couleurTrait) ;
	i_outil = -1 ;
	}

void rectangleVide (void)
	{
	Point P_p1, P_p2, P_p3, P_p4 ;
	P_p1 = attendre_clic() ;
	P_p2 = attendre_clic() ;
	P_p3.x = P_p2.x ;
	P_p3.y = P_p1.y ;
	P_p4.x = P_p1.x ;
	P_p4.y = P_p2.y ;
	
	if (dansDessin(P_p1) == 1 && dansDessin(P_p2) == 1)
		{
		dessiner_ligne(P_p1, P_p3, C_couleurTrait) ;
		dessiner_ligne(P_p1, P_p4, C_couleurTrait) ;
		dessiner_ligne(P_p2, P_p4, C_couleurTrait) ;
		dessiner_ligne(P_p3, P_p2, C_couleurTrait) ;
		}
	i_outil = -1 ;
	}

void cercleVide(void)
	{
	Point P_p1 = attendre_clic() ;
	Point P_p2 = attendre_clic() ;

	int rayon = sqrt(pow((P_p2.x - P_p1.x),2) + pow((P_p2.y - P_p1.y),2)) ;

	Point P_limiteHaut = {P_p1.x, P_p1.y - rayon}, P_limiteBas = {P_p1.x, P_p1.y + rayon} ;
	Point P_limiteDroite = {P_p1.x + rayon, P_p1.y}, P_limiteGauche = {P_p1.x - rayon, P_p1.y} ;
	if (dansDessin(P_limiteHaut) == 1 && dansDessin(P_limiteBas) == 1 && dansDessin(P_limiteDroite) == 1 && dansDessin(P_limiteGauche) == 1)
		dessiner_cercle (P_p1, rayon, C_couleurTrait) ;

	i_outil = -1 ;
	}

void polygoneVide(void)
	{
	Point P_p1, P_p2, P_p3 ;
	int P_clicDroit = 0 ;
	
	P_p1 = attendre_clic_gauche_droite() ;
	P_p2 = attendre_clic_gauche_droite() ;
	
	if (dansDessin(P_p1) == 1 && dansDessin(P_p2) == 1)
		{
		dessiner_ligne(P_p1, P_p2, C_couleurTrait) ;
		actualiser () ;
		while (P_clicDroit == 0)
			{
			P_p3 = attendre_clic_gauche_droite() ;
			if (dansDessin(P_p3) == 1)
				{
				if (P_p3.x < 0)
					{
					P_p3.x = -P_p3.x ;
					P_p3.y = -P_p3.y ;
					dessiner_ligne (P_p2, P_p1, C_couleurTrait) ;
					P_clicDroit = 1 ;
					}
				else
					dessiner_ligne (P_p2, P_p3, C_couleurTrait) ;
				
				actualiser () ;
					
				P_p2.x = P_p3.x ;
				P_p2.y = P_p3.y ;
				}
			}
		}
	i_outil = -1 ;
	}

void rectanglePlein(void)
	{
	Point P_p1 = attendre_clic() ;
	Point P_p2 = attendre_clic() ;
	int i_largeur = abs(P_p2.x - P_p1.x), i_hauteur = abs(P_p2.y - P_p1.y) ;
	Point P_coin ;

	if (dansDessin(P_p1) == 1 && dansDessin(P_p2) == 1)	
		{	
		if (P_p1.x < P_p2.x && P_p1.y < P_p2.y)		
			P_coin = P_p1 ;
		else if (P_p1.x < P_p2.x && P_p1.y > P_p2.y)
			{
			P_coin.x = P_p1.x ;
			P_coin.y = P_p2.y ;
			}
		else if (P_p1.x > P_p2.x && P_p1.y < P_p2.y)
			{
			P_coin.x = P_p2.x ;
			P_coin.y = P_p1.y ;
			}
		else 
			P_coin = P_p2 ;

		Point P_coinInt = {P_coin.x + 2, P_coin.y + 2} ;
		dessiner_rectangle (P_coin, i_largeur, i_hauteur, C_couleurTrait) ;
		dessiner_rectangle (P_coinInt, i_largeur - 4, i_hauteur - 4, C_couleurRemp) ;		
		}
	i_outil = -1 ;
	}

void cerclePlein(void)
	{
	Point P_p1 = attendre_clic() ;
	Point P_p2 = attendre_clic() ;

	int rayon = sqrt(pow((P_p2.x - P_p1.x),2) + pow((P_p2.y - P_p1.y),2)) ;
	
	Point P_limiteHaut = {P_p1.x, P_p1.y - rayon}, P_limiteBas = {P_p1.x, P_p1.y + rayon} ;
	Point P_limiteDroite = {P_p1.x + rayon, P_p1.y}, P_limiteGauche = {P_p1.x - rayon, P_p1.y} ;
	if (dansDessin(P_limiteHaut) == 1 && dansDessin(P_limiteBas) == 1 && dansDessin(P_limiteDroite) == 1 && dansDessin(P_limiteGauche) == 1)
		{	
		dessiner_disque (P_p1, rayon, C_couleurTrait) ;
		dessiner_disque (P_p1, rayon - 2, C_couleurRemp) ;
		}
	i_outil = -1 ;
	}

void rectangleRaye(void)
	{
	Point P_p1, P_p2, P_p3, P_p4, P_r1, P_r2 ;
	P_p1 = attendre_clic() ;
	P_p2 = attendre_clic() ;
	
	int i_longueur = abs(P_p2.x - P_p1.x) ;

	P_p3.x = P_p2.x ;
	P_p3.y = P_p1.y ;
	P_p4.x = P_p1.x ;
	P_p4.y = P_p2.y ;
	

	P_r1.y = P_p1.y ;
	P_r2.y = P_p2.y ;

	if (dansDessin(P_p1) == 1 && dansDessin(P_p2) == 1)
		{
		dessiner_ligne(P_p1, P_p3, C_couleurTrait) ;
		dessiner_ligne(P_p1, P_p4, C_couleurTrait) ;
		dessiner_ligne(P_p2, P_p4, C_couleurTrait) ;
		dessiner_ligne(P_p3, P_p2, C_couleurTrait) ;
		}

	for (int iX = P_p1.x; iX < i_longueur + P_p1.x; iX += 20)
		{
		P_r1.x = iX ;
		P_r2.x = iX ;
		
		dessiner_ligne (P_r1, P_r2, C_couleurRemp) ;
		}

	i_outil = -1 ;
	}

void sauvegarde (void)
	{
	char s_nomFichier [50] ;
	char s_chemainFichier [255] = "" ;
	
	printf ("Nom du fichier: ") ;
	scanf ("%s", s_nomFichier) ;
	sprintf(s_chemainFichier, "sauvegardes/%s.bmp", s_nomFichier) ;
	
	SDL_Surface* dessin = NULL ;
	SDL_Rect zoneDessin = {0, TAB_HAUT + 50, L_DESSIN, H_DESSIN} ;

	dessin = SDL_CreateRGBSurface (0, L_DESSIN, H_DESSIN, 32, 0, 0, 0, 0) ;
	SDL_BlitSurface (SDL_GetVideoSurface(), &zoneDessin, dessin, NULL) ;
	SDL_SaveBMP(dessin, s_chemainFichier) ;
	
	printf("Fichier enregistré avec succès !\n") ;
	i_outil = -1 ;
	}

void loadSauvegarde (void)
	{
	char s_nomFichier [50] ;
	char s_chemainFichier [255] = "" ;
	
	printf ("Nom du fichier: ") ;
	scanf ("%s", s_nomFichier) ;
	sprintf(s_chemainFichier, "sauvegardes/%s.bmp", s_nomFichier) ;
	
	SDL_Surface* dessin = NULL ;
	SDL_Rect zoneDessin = {0, TAB_HAUT + 50, L_DESSIN, H_DESSIN} ;

	dessin = SDL_LoadBMP(s_chemainFichier) ;

	SDL_BlitSurface (dessin, NULL, SDL_GetVideoSurface(), &zoneDessin) ;
	
	printf("Fichier chargé avec succès !\n") ;
	i_outil = -1 ;
	}

void texte(void)
	{
	Point P_locaTexte ;
	char s_texte [100] ;
	int i_tailleTexte ;

	P_locaTexte = attendre_clic() ; 	
	
	if (dansDessin(P_locaTexte) == 1)
		{
		printf ("Votre texte: ") ;
		scanf ("%s", s_texte) ;
		printf ("Taille: ") ;
		scanf ("%d", &i_tailleTexte) ;
		
		afficher_texte(s_texte, i_tailleTexte, P_locaTexte, C_couleurTrait) ;
		}
	i_outil = -1 ;
	}

void gomme(void)
	{
	Point P_point;
	
	P_point = attendre_clic () ;
	
	if (dansDessin(P_point) == 1)
		{
		int i_gommeActive = 1 ;
		while (i_gommeActive == 1)
			{
			dessiner_ligne(P_point, P_posSouris, blanc) ;
			P_point = P_posSouris ;
			actualiser() ;
			if (clic_a_eu_lieu().x != -1)
				i_gommeActive = 0 ;

			}
		}
	i_outil = -1 ;
	}
