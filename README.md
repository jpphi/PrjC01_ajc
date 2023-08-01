# PrjC01_ajc
Projet AJC - Utilisation de gdlib  
  
## Fonctionnement du programme  
Ce programme permet de dessiner des camemberts proportionnel au pourcentage passé.  
-p ce paramètre obligatoire permet de définir les pourcentages passés en paramètres.
-l ce paramètre optionel permet de passer les étiquettes associées au pourcentage.
-f ce paramètre obligatoire indique le nom du fichier png dans lequel l'image sera sauvegardée.
-t ce paramètre optionel permet de définir les caractéristique de l'image. Non gérer actuelement.
-o ce paramètre optionel permet de définir la hauteur et la largeur de l'image ainsi que le rayon du cercle et la couleur de fond.  
  
## Exemple  
./pie -p 10,20,30,40,50,100,50,60 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 40%','Label: 50%','Label: 100%','Label: 50%','Label: 60%' -f toto.png -o 800,800,400,0x80A0B0C0  
Crée un fichier toto.png contenant une image d'un graphique de type camenmbert. les pourcentages et les labels sont indiqués dans les paramètres p et l.  
Cette image fera 800 pixels de haut et de large. Le camenmbert aura un diamètre de 400. La couleur de fond est défnie par 0x80A0B0C0.
