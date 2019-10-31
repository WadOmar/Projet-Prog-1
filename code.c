#include "lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

void dessiner_segment (Point p1, Point p2);
void dessiner_triangle (Point p1, Point p2, Point p3);
void dessiner_rect (Point p1, Point p2, Point p3, Point p4);
/*void dessiner_rectp(Point p1, int largeur, int hauteur, Couleur );
void dessiner_disque(Point p1, int rayon, Couleur );*/

int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(1400,900);

	int largeur, hauteur;	
	Point p1, p2, p3, p4;
	dessiner_segment(p1,p2);
	/*dessiner_triangle(p1,p2,p3);*/
	/*dessiner_rect(p1,p2,p3,p4);*/
    
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }


void dessiner_segment(Point p1, Point p2)
	{
		p1 = attendre_clic();
		p2 = attendre_clic();			
		dessiner_ligne(p1,p2, vert);
		actualiser();	
	}

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


