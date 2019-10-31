#include "lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

/*void dessiner_segment (Point p1, Point p2);
void dessiner_triangle (Point p1, Point p2, Point p3);
void dessiner_rect (Point p1, Point p2, Point p3, Point p4);
void dessiner_disquer(Point p1, int rayon, Couleur couleur);*/
void dessiner_rectangler(Point p1, int largeur, int hauteur, Couleur couleur) ;

int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(1400,900);

	int largeur, hauteur, rayon;	
	Point p1, p2, p3, p4;
	/*dessiner_segment(p1,p2);*/
	/*dessiner_triangle(p1,p2,p3);*/
	/*dessiner_rect(p1,p2,p3,p4);*/
	/*dessiner_disquer(p1,rayon,rouge);*/
	dessiner_rectangler(p1, largeur, hauteur, vert);    

    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }


/*void dessiner_segment(Point p1, Point p2)
	{
		p1 = attendre_clic();
		p2 = attendre_clic();			
		dessiner_ligne(p1,p2, vert);
		actualiser();	
	}*/

/*void dessiner_triangle(Point p1, Point p2, Point p3)
	{
		p1 = attendre_clic();
		p2 = attendre_clic();
		p3 = attendre_clic();
		dessiner_ligne(p1, p2, rouge);
		dessiner_ligne(p2, p3, rouge);
		dessiner_ligne(p1, p3, rouge);
		actualiser();
	}*/

/*void dessiner_rect(Point p1, Point p2, Point p3, Point p4)
	{
		p1 = attendre_clic();
		p2 = attendre_clic();
		p3.x = p2.x;
		p3.y = p1.y;
		p4.x = p1.x;
		p4.y = p2.y;
		dessiner_ligne(p1, p3, bleu);
		dessiner_ligne(p1, p4, bleu);
		dessiner_ligne(p2, p4, bleu);
		dessiner_ligne(p3, p2, bleu);
		actualiser();
		
	}*/

/*void dessiner_disquer (Point p1, int rayon, Couleur couleur)
	{
	p1 = attendre_clic();
	Point p2 = attendre_clic();
	rayon = sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
	dessiner_disque (p1, rayon, couleur);
	actualiser();
	}*/	

void dessiner_rectangler (Point p1, int largeur, int hauteur, Couleur couleur)
	{
	p1 = attendre_clic();
	Point p2 = attendre_clic();
	Point coin;
	if (p1.x < p2.x && p1.y < p2.y)	
		{		
		largeur = p2.x - p1.x;
		hauteur = p2.y - p1.y;
		dessiner_rectangle (p1, largeur, hauteur, vert);
		}
	else if (p1.x < p2.x && p1.y > p2.y)
		{
		largeur = p2.x - p1.x;
		hauteur = p1.y - p2.y;
		coin.x = p1.x; 
		coin.y = p2.y;
		dessiner_rectangle (coin, largeur, hauteur, vert);
		}
	else if (p1.x > p2.x && p1.y < p2.y)
		{
		largeur = p1.x - p2.x;
		hauteur = p2.y - p1.y;
		coin.x = p2.x; 
		coin.y = p1.y;
		dessiner_rectangle (coin, largeur, hauteur, vert);
		}
	else 
		{
		largeur = p1.x - p2.x;
		hauteur = p1.y - p2.y;
		dessiner_rectangle (p2, largeur, hauteur, vert);
		}
	actualiser();
	}
