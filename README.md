# PrjC01_ajc
Projet AJC - Utilisation de gdlib (https://libgd.github.io/)  
  
## Fonctionnement du programme  
Ce programme permet de dessiner des camemberts proportionnels aux pourcentages passé en paramètre ou considère les valeurs passées comme étant des valeurs absolues.  
- Sans arguement, le programme affiche l'aide.  
- -p ce **paramètre obligatoire** permet de définir les pourcentages passés.  
- -l ce paramètre optionel permet de passer les étiquettes associées aux pourcentages.  
- -f ce **paramètre obligatoire** indique le nom du fichier png dans lequel l'image sera sauvegardée.  
- -t ce paramètre optionel permet de définir le type de graphique (-t type de graphique type= c/C pour un camembert, h/H pour un histogramme, b/B pour un bar chart). Si le paramètre est en minuscule, les données sont considérées comme un pourcentage, sinon les données sont des données absolues. **h est en cours d'intégration**.  
- -o ce paramètre optionel permet de définir la hauteur et la largeur de l'image ainsi que le rayon du cercle et la couleur de fond.  
- -c ce paramètre optionel permetde définir la taille de la police. Valeur possible 0, 1, 2, 3 et 4.  
- -d ce paramètre optionel permet de tracer les graphique en 3d. Il ne prend pas de paramètre. **Seul les camemberts 3d sont gérés**  
- -a ce paramètre optionel permet d'éviter que 2 camemberts soit de même couleur. Voir les png exemple cidentique.png et cidentiqueres.png  
  
La valeur par défaut du paramètre -t est 'C'.  
La valeur par défaut du paramètre -c est 3.  
Les valeurs par défauts du paramètre -o sont 400, 400, 200, 0x00FFFFFF (Couleur blanche).  
  
## Remarques  
Les paramètres doivent être cohérents.  
Les différentes valeurs doivent être séparées par des virgules et sans espace.  
L'utilisation du paramètre 'o' suppose de fournir tout les paramètres (hauteur, largeur, rayon et couleur de fond).  
S'il y a trop de paramètres labels par rapport au nombre de pourcentage passé, ces paramètres en trop seront ignoré.  

## Exemple et ligne de commande pour test  
Pour illustrer le problème d'arrondi:  
./pie -p 5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2, -l 'Label 1: 5 %','Label 1: 3 %','Label 1: 2 %','Label 2: 5 %','Label 2: 3 %','Label 2: 2 %','Label 3: 5 %','Label 3: 3 %','Label 3: 2 %','Label 4: 5 %','Label 4: 3 %','Label 4: 2 %','Label 5: 5 %','Label 5: 3 %','Label 5: 2 %','Label 6: 5 %','Label 6: 3 %','Label 6: 2 %','Label 7: 5 %','Label 7: 3 %','Label 7: 2 %','Label 8: 5 %','Label 8: 3 %','Label 8: 2 %','Label 9: 5 %','Label 9: 3 %','Label 9: 2 %','Label 10: 5 %','Label 10: 3 %','Label 10: 2 %' -f pbArrondi.png -o 800,800,400,0x80A0B0C0 -t c   
  
Utilisation en valeur absolue:  
./pie -p 11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9 -l 'Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9' -f Cam36-tC.png -o 800,800,400,0x80A0B0C0 -t C  
  
Crée un fichier toto.png contenant une image d'un graphique de type camenmbert. les pourcentages et les labels sont indiqués dans les paramètres p et l.  
Cette image fera 800 pixels de haut et de large. Le camembert aura un diamètre de 400. La couleur de fond est défnie par 0x80A0B0C0.  
  
Bar chart relatif et absolue;  
./pie -p 70,20,30,40,50,100,50,60 -l 'Label: 70','Label: 20','Label: 30','Label: 40','Label: 50','Label: 100','Label: 50','Label: 60' -f barChartB.png -o 800,800,400,0x80A0B0C0 -t B  
./pie -p 10,20,30,25,15 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 25%','Label: 15%' -f barChartb.png -o 800,800,400,0x80A0B0C0 -t b  
  
Camembert 3d:  
./pie -p 10,20,30,25,15,150,30,20,60 -f essai3dC.png -o 800,800,400,0x80A0B0C0 -t C -d  
  
Utilisation de l'option a:  
./pie -p 10,20,30,25,15,100,50,40,10,20,20,20 -f cidentiqueres.png -o 800,800,400,0x00DDEEFF -t C -a  
./pie -p 10,20,30,25,15,100,50,40,10,20,20,20 -f cidentique.png -o 800,800,400,0x00DDEEFF -t C  
  
Bar chart 2D:  
./pie -p 10,20,30,25,15 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 25%','Label: 15%' -f barChartb.png -o 800,800,400,0x80A0B0C0 -t b  
./pie -p 70,20,30,40,50,100,50,60 -l 'Label: 70','Label: 20','Label: 30','Label: 40','Label: 50','Label: 100','Label: 50','Label: 60' -f barChartB.png -o 800,800,400,0x80A0B0C0 -t B  
  
Histogramme 2D (**en cours de dév**)  
./pie -p 70,20,30,40,50,100,50,60 -l 'Label: 70','Label: 20','Label: 30','Label: 40','Label: 50','Label: 100','Label: 50','Label: 60' -f histoB.png -o 800,800,400,0x80A0B0C0 -t H  
./pie -p 10,20,30,25,15 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 25%','Label: 15%' -f histob.png -o 800,800,400,0x80A0B0C0 -t h  
  
## Problèmes et améliorations  
- La ligne de commande n'est pas vérifiée ni filtrée. Attention de ne pas entrer n'importe quoi ! :)  
- La version incluant les histogrammes ne gère pas les label. **Encore en phase de test**.  
- Une version permettant de faire des graphiques 3D sur tout type de graphique.  
- Les labels ne sont pas géré en 3D.  
- Des erreurs d'arrondies peuvent dégradées l'image d'un camembert (voir le png pbArrondi).  
- Si le nombre de camembert à afficher correspond aux nombre de couleurs disponible + 1, le dernier camembert aura la même couleur que le 1er. **Pour solutionner le problème utiliser le paramètre -a**.  
  
## Valeur retournée  
1 en cas d'erreur, 0 si succès.  
  
## Ligne de commande pour test  
Paramètre nul dans une liste: Pas de plantage et l'ordre des valeurs passées est conforme à ce qui est attendu (la double virgule est filtrée).  
./pie -f toto.png -p 10,,30,50 -l lab1,,lab3,lab4  
A noter que le ',,' à un comportement différent du '0' qui créera une portion de camembert d'une taille de 0.  
./pie -f toto.png -p 10,,30,50 -l lab1,lab2,,lab4 -t c  


