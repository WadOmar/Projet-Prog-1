	    cPaint
Ouadrhiri Omar et Spinu Daniel

Fonctionalitées:
	- Fausse barre de chargement au démarrage (avec une phrase aléatoire différente à chaque lancement)
	- Boutons :
		* segment
		* rectangle vide
		* rectangle plein
		* cercle vide
		* cercle plein
		* polygone vide
		* rectangle rayé
		* dessin à main levé : Un clic pour commencer, le deuxième pour arrêter
		* remplissage : Appuyer n'importe où sur la zone de dessin, pour propager une couleur (eviter tout l'ecran)
		* clear : Remet à zero l'interface
		* sauvegarde : enregistre en .bmp votre fichier (voir console)
		* chargement sauvegarde : recupere une ancienne sauvegarde
	- Barre d'aide (il suffit d'appuyer sur un bouton pour savoir comment il fonctionne)
	- Palettes de couleur

Problèmes connus / Bugs:
	- Remplissage sur tout l'écran = erreur ;
	- Il faut parfois appuyer plusieurs fois sur un bouton pour qu'il marche

Problèmes surmontés:
	- Afficher_texte qui ne marchait pas a cause de l'erreur de chargement de la police
	- On a eu du mal avec le remplissage également étant donné notre manque de connaissance (Avant le cours sur la récursivité)

Idées non réalisées (Manque de temps :c):
	- aérosol : Generer un certain nombre de points au hasard sur l'écran, et n'afficher que ceux qui se situent sur un certain rayon du clic.
	- undo : Utiliser un tableau à 2 dimansions correspondant à la zone de dessin, et l'actualiser à chaque changement.
	- formes en 3 dimensions  
  
