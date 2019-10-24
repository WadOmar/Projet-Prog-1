#include "../lib/libgraphique.h"
#include<stdio.h>

#define L_FENETRE 1400
#define H_FENETRE 900

int main(void)
    {
    ouvrir_fenetre(L_FENETRE, H_FENETRE);
	
    
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }



