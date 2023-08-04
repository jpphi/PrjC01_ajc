# PrjC01_ajc
Projet AJC - Utilisation de gdlib  
  
## Fonctionnement du programme  
Ce programme permet de dessiner des camemberts proportionnels aux pourcentages passé en paramètre.  
- Sans arguement, le programme affiche l'aide.  
- -p ce paramètre obligatoire permet de définir les pourcentages passés.  
- -l ce paramètre optionel permet de passer les étiquettes associées aux pourcentages.  
- -f ce paramètre obligatoire indique le nom du fichier png dans lequel l'image sera sauvegardée.  
- -t ce paramètre optionel permet de définir le type de graphique (-t type de graphique type= c/C pour un camembert, h/H pour un histogramme, b/B pour un bar chart). Si le paramètre est en minuscule, les données sont considérées comme un pourcentage, sinon les données sont des données absolues. **b et h sont en cours d'intégration**.  
- -o ce paramètre optionel permet de définir la hauteur et la largeur de l'image ainsi que le rayon du cercle et la couleur de fond.  
  
La valeur par défaut du paramètre -t est 'C'.  
Les valeurs par défauts du paramètre -o sont 400, 400, 200, 0x00FFFFFF (Couleur blanche).  
  
## Remarques  
Les paramètres doivent être cohérents.  
Les différentes valeurs doivent être séparées par des virgules et sans espace.  
L'utilisation du paramètre 'o' suppose de fournir tout les paramètres (hauteur, largeur, rayon et couleur de fond).  
S'il y a trop de paramètres labels par rapport au nombre de pourcentage passé, ces paramètres en trop seront ignoré.  

## Exemple  
Pour illustréer le problème d'arrondi:  
**./pie -p 5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2, -l 'Label 1: 5 %','Label 1: 3 %','Label 1: 2 %','Label 2: 5 %','Label 2: 3 %','Label 2: 2 %','Label 3: 5 %','Label 3: 3 %','Label 3: 2 %','Label 4: 5 %','Label 4: 3 %','Label 4: 2 %','Label 5: 5 %','Label 5: 3 %','Label 5: 2 %','Label 6: 5 %','Label 6: 3 %','Label 6: 2 %','Label 7: 5 %','Label 7: 3 %','Label 7: 2 %','Label 8: 5 %','Label 8: 3 %','Label 8: 2 %','Label 9: 5 %','Label 9: 3 %','Label 9: 2 %','Label 10: 5 %','Label 10: 3 %','Label 10: 2 %' -f pbArrondi.png -o 800,800,400,0x80A0B0C0 -t c**   
Utilisation en valeur absolue:  
**./pie -p 11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9 -l 'Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9' -f toto.png -o 800,800,400,0x80A0B0C0 -t C**  
  
Crée un fichier toto.png contenant une image d'un graphique de type camenmbert. les pourcentages et les labels sont indiqués dans les paramètres p et l.  
Cette image fera 800 pixels de haut et de large. Le camembert aura un diamètre de 400. La couleur de fond est défnie par 0x80A0B0C0.  
  
## Problèmes et améliorations  
- La ligne de commande n'est pas vérifiée ni filtrée. Attention de ne pas entrer n'importe quoi ! :)  
- Une version incluant les histogrammes est prévue.  
- Une version permettant de faire des graphiques 3D.  
- Des erreurs d'arrondies peuvent dégradées l'image d'un camembert (voir le png pbArrondi).  
  
## Valeur retournée  
1 en cas d'erreur, 0 si succès.  
  
## Ligne de commande pour test  
Paramètre nul dans une liste: Pas de plantage et l'ordre des valeurs passées est conforme à ce qui est attendu (la double virgule est filtrée).  
./pie -f toto.png -p 10,,30,50 -l lab1,,lab3,lab4  
A noter que le ',,' à un comportement différent du '0' qui créera une portion de camembert d'une taille de 0.  
./pie -f toto.png -p 10,,30,50 -l lab1,lab2,,lab4 -t c  


