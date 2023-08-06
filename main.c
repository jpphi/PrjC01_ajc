/* Ligne de commande:
 * pie -p n1,n2,n3,...,nx -l ch1, ch2,...,chx -t type - f fich.png -o h,l,r,c -c x
 *
 * Ligne de commande pour test:
 * ./pie -p 10,20,15,15,30 -l 'Label: 10%','Label: 20%','Label: 15%','Label: 15%','Label: 30%' -f CamPartiel.png -o 800,800,400,0x80A0B0C0
 *
 * Option c
 * ./pie -p 5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2, -l 'Label 1: 5 %','Label 1: 3 %','Label 1: 2 %','Label 2: 5 %','Label 2: 3 %','Label 2: 2 %','Label 3: 5 %','Label 3: 3 %','Label 3: 2 %','Label 4: 5 %','Label 4: 3 %','Label 4: 2 %','Label 5: 5 %','Label 5: 3 %','Label 5: 2 %','Label 6: 5 %','Label 6: 3 %','Label 6: 2 %','Label 7: 5 %','Label 7: 3 %','Label 7: 2 %','Label 8: 5 %','Label 8: 3 %','Label 8: 2 %','Label 9: 5 %','Label 9: 3 %','Label 9: 2 %','Label 10: 5 %','Label 10: 3 %','Label 10: 2 %' -f pbArrondi.png -o 800,800,400,0x80A0B0C0 -t c
 * Option C
 * ./pie -p 11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9 -l 'Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9' -f Cam36C.png -o 800,800,400,0x80A0B0C0 -t C
 *
 * Option B
 * ./pie -p 70,20,30,40,50,100,50,60 -l 'Label: 70','Label: 20','Label: 30','Label: 40','Label: 50','Label: 100','Label: 50','Label: 60' -f barChartB.png -o 800,800,400,0x80A0B0C0 -t B
 * Option b
 * ./pie -p 10,20,30,25,15 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 25%','Label: 15%' -f barChartb.png -o 800,800,400,0x80A0B0C0 -t b
 *
 * Divers
 * ./pie -p 10,20,30,40,50,100,50,60 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 40%','Label: 50%','Label: 100%','Label: 50%','Label: 60%' -f toto1.png -o 800,800,400,0x80A0B0C0
 *
 * ./pie -p 11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9 -l 'Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9' -f toto.png -o 800,800,400,0x80A0B0C0 -t C
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gd.h>
#include <gdfontl.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontg.h>
#include <math.h>

#define NBPOLICE 5

void afficheAide(void);

int main(int argc, char **argv)
{
    char *cP, *cL, *cF, *cO, *mot,  **tabArgL, *chW; //*cT,
    char typeGraphique= 'C'; // Type de graphique par défaut

    long unsigned int COULEURS[]= {0x000000FF, 0x000080FF, 0x0000FF00, 0x0080FF80, 0x00FF0000, 0x00FF8000 ,0x00FFFF00, 0x00FF00FF, 0x0000FFFF, 0x00808080, 0x00FF8080};
    long unsigned int COULEUR_FOND= 0x00FFFFFF;

    int longCouleur= sizeof(COULEURS)/sizeof(long unsigned int), nArgP= 1, nArgL= 1;
    int *pourcentage= NULL;
    int hauteur = 400, largeur, dimension_graph= 200, epaisseur;
    int opt, numPolice= 3, d3= 0;

    FILE *desc;

    gdImagePtr im;
    gdFontPtr polices[NBPOLICE]; // Plus facile si on souhaite passé le type de police= gdFontLarge;

    polices[0]= gdFontTiny;
    polices[1]= gdFontSmall;
    polices[2]= gdFontMediumBold;
    polices[3]= gdFontLarge;
    polices[4]= gdFontGiant;

    if(argc== 1)
    {
        afficheAide();
        return 1;
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //
    //                                          RECUPERATION DE LA LIGNE DE COMMANDE ET PRE TRAITEMENT
    //
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    while((opt = getopt(argc, argv, "ac:df:l:o:p:t:")) != -1) // pltf
    {
        switch(opt)
        {
        case 'a':
            longCouleur--;
        break;
        case 'c':
            //printf("option: %c\n", opt);
            //printf("param: %s\n", optarg);
            //printf("Longueur: %d\n", strlen(optarg));
            numPolice= (optarg[0]-48) % NBPOLICE;
        break;

        case 'd':
            d3= 1;
        break;

        case 'f':
            cF= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
            strcpy(cF, optarg);
        break;

        case 'l':
            cL= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
            strcpy(cL, optarg);
        break;


        case 'o':
            cO= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
            strcpy(cO, optarg);
            sscanf(cO,"%d,%d,%d,%lx", &hauteur, &largeur, &dimension_graph, &COULEUR_FOND);
            if(hauteur < 200)hauteur=200;
            if(largeur < 200)largeur=200;
        break;

        case 'p':
            cP= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
            strcpy(cP, optarg);
        break;

        case 't': // De la forme t x avec x= c pour un camembert, h pour un histo, b pour un bar chart
            typeGraphique= optarg[0];
        break;

        case ':':
           printf("Erreur: Option sans paramètre.\n");
           break;

        case '?':
           printf("\nOption: '%c' inconnue \n", optopt);
           afficheAide();
           return 1;
           break;
        }
    }

    //printf("\n%s\n%s\n%s\n%s\n", cP,cT,cF, cL);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //
    //                                          RECUPERATION ET MISE EN FORMES DES PARAMETRES
    //
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    //------------------- Paramètre -f

    if(cF== NULL)
    {
        printf("\n Erreur, la paramètre -f est obligatoire !\n");
        afficheAide();
        return 1;
    }

    desc=fopen(cF,"wb");

    //------------------- Paramètre -p

    if(cP== NULL)
    {
        printf("\n Erreur, la paramètre -p est obligatoire !\n");
        afficheAide();
        return 1;
    }

    // Décomposition de l'arguement -p (pourcentage)
    mot=  strtok(cP, ",");
    //printf("Début mot= %s\n", mot);
    while(mot!= NULL)
    {
        double pp100;
        //printf("mot= %s", mot);
        pourcentage= (int *)realloc(pourcentage, nArgP * sizeof(int));
        sscanf(mot, "%lf", &pp100);
        switch (typeGraphique)
        {
            case 'c':
                pourcentage[nArgP-1]= (int)(pp100*3.6);
            break;
            case 'C':
                pourcentage[nArgP-1]= (int)(pp100);
            break;

            case 'b':
            case 'h':
            case 'B':
            case 'H':
                pourcentage[nArgP-1]= (int)(pp100);
            break;
            default:
            break;
        }
        //printf("< nArgP= %d -- pourcentage[%d]= %d\n", nArgP, nArgP-1, pourcentage[nArgP-1]);
        mot= strtok(NULL,",");
        nArgP++;
    }
    nArgP--;

    //----------------------------------- Paramètre -l

    // On va calculer le nombre de mot contenu dans la chaine cL
    if(cL!= NULL)
    {

        chW= malloc( (strlen(cL)+1) * sizeof(char));
        strcpy(chW, cL); // Il est nécessaire de sauvegarder cL

        mot=  strtok(chW, ",");
        //printf("Début mot= %s\n", mot);
        while(mot!= NULL)
        {
            //printf("mot= %s - nArgL %d ", mot, nArgL);
            //pourcentage= (int *)realloc(pourcentage, nArgL * sizeof(int));
            //sscanf(mot, "%d", &pourcentage[nArgL-1]);
            //printf("< nArgL= %d\n", nArgL);
            mot= strtok(NULL,",");
            nArgL++;
        }
        nArgL--;
        tabArgL= (char **)malloc(nArgL * sizeof(char *));
        //printf("-> nArgL %d -> %p\n", nArgL, tabArgL);

        // Reservation de l'espace mémoire pour chacun des mots contenu dans cL
        strcpy(chW, cL); // Il est nécessaire de sauvegarder cL
        mot=  strtok(chW, ",");
        //printf("\nRedécomposition= %s\n", mot);
        for(int i= 0; mot!= NULL; i++)
        {
            int tmot= strlen(mot);
            //printf("\nmot= %s - tmot %d ", mot, tmot);
            tabArgL[i]= (char *)malloc( (tmot +1) * sizeof(char));
            strcpy(tabArgL[i], mot);
            //printf("< nArgL= %d - *tabArgL %s\n", nArgL, tabArgL[i]);
            mot= strtok(NULL,",");
        }
        //printf("-> nArgL %d TabArgL[0]= %s\n", nArgL, tabArgL[0]);

    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //
    //                                          TRACE DES DIFFERENTES FIGURES 2D
    //
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    //----------------------------------- Création de l'image de taille donée en paramètre

    im = gdImageCreateTrueColor(largeur, hauteur);
    gdImageFilledRectangle(im, 0, 0, largeur-1, hauteur-1, COULEUR_FOND);

    //----------------------------------- Tracer du pie

    if( ( (typeGraphique== 'c') || (typeGraphique== 'C') ) && !d3)
    {
        double si, co, angle;
        int x0, y0, x1, y1, ltrait= 10;
        int r= dimension_graph/2 + 10;

        for(int i=0, tmp= 0; i<nArgP; i++)
        {
            //----------------------------------- Tracer d'une portion de camembert

            gdImageFilledArc (im, largeur/2, hauteur/2, dimension_graph, dimension_graph, tmp, tmp+pourcentage[i], COULEURS[i%(longCouleur)], gdPie);
            //printf("\ntmp= %d - tmp + pourcentage[%d]= %lu - i%(longCouleur-1)= %d - i= %d- longCouleur= %d", tmp,i, tmp + pourcentage[i], i%(longCouleur), i, longCouleur);

            angle= (double)(tmp + (double)pourcentage[i]/2)*M_PI/180;
            si= sin(angle);
            co= cos(angle);

            // VARIABLES DE DEBUG
            //double angleDeg= (tmp + pourcentage[i]/2);


            //----------------------------------- Ecriture d'un label associé s'il existe

            //printf("\nangle %lf, sinus= %lf, cosinus= %lf, pourcentage= %d, tmp %d, angle cumulé %d M_PI= %lf posx= %d posy= %d\n", angle, si, co, pourcentage[i], tmp, tmp + pourcentage[i], M_PI, posx,posy);
            if( (cL!= NULL) && ( i < nArgL))
            {
                int posx, posy, offset, off_y, off_y_s=0, off_y_s2=0;

                //----------------------------------- Tracer des trait
                x0= (int)(largeur/2 + dimension_graph/2 * co );
                y0= (int)(hauteur/2 + dimension_graph/2 * si );
                x1= (int)(largeur/2 + (dimension_graph/2+ltrait) * co );
                y1= (int)(hauteur/2 + (dimension_graph/2+ltrait) * si );
                //printf("\n x0, y0 = %d, %d et x1, y1= %d, %d ltrait= %d -- posx= %d posy=  %d r= %d -- co=  %lf si= %lf \n",x0, y0, x1, y1, ltrait, posx, posy, r, co, si);
                //printf("VAR DEBUG: angle en degré = %lf\n", angleDeg);
                gdImageLine(im, x0, y0, x1, y1, 0x00000000);

                posx= (int)(largeur/2 + r * co );
                posy= (int)(hauteur/2 + r * si );

                // Attention, sens inverse du sens trigo! Entre 90 et 270, écriture avant le camembert
                if( (angle > M_PI/2) && (angle < 3*M_PI/2) )
                {
                    offset= -(polices[numPolice]->w) * strlen(tabArgL[i]) - polices[numPolice]->w;
                    off_y= (int)((polices[numPolice]->w) * 1.0 * co);
                    //off_y_s= (int)((polices[numPolice]->w) * si * 1.5);
                }
                else
                {
                    offset= (polices[numPolice]->w);
                    off_y= (int)(-(polices[numPolice]->w) * 1.0 * co);
                    //off_y_s= (int)((polices[numPolice]->w) * si * 1.5);
                }

                // Pour les angles prés de 90 et 270, on décale l'écriture
                if( (angle > M_PI/3) && (angle < 2*M_PI/3) || (angle > 4*M_PI/3) && (angle < 5*M_PI/3) )
                {
                    off_y_s= (int)((polices[numPolice]->w) * si * 1.5);
                    off_y+= off_y_s;
                }

                // Pour les angles trés prés de 90 et 270, on décale l'écriture d'un facteur supplémentaire
                if( (angle > 9*M_PI/20) && (angle < 11*M_PI/20) || (angle > 29*M_PI/20) && (angle < 31*M_PI/20) )
                {
                    off_y_s2= (int)((polices[numPolice]->w) * si * 1.5);
                    off_y+= off_y_s2;
                }

                // Ecriture
                gdImageString(im, polices[numPolice], posx + offset, posy + off_y,tabArgL[i], 0x00000000);
                //printf("\n Dans l affichage chaine: %s - offset= %d\n", tabArgL[i], offset);
            }

            tmp+= pourcentage[i];
        }
    }

    //----------------------------------- Tracer du bar chart

    if( ( (typeGraphique== 'b') || (typeGraphique== 'B') ) && !d3)
    {
        int delta= 4*polices[numPolice]->w, somme= 0;

        if(typeGraphique== 'b')
        {
            for(int j= 0; j < nArgP ;j++)
            {
                pourcentage[j]= (int)( (double)pourcentage[j]*(hauteur - 2*delta)/100);
                //printf("\nrecalcul du pourcentage= %d\n", pourcentage[j]);
            }
        }

        for(int i=0, tmp= hauteur - delta; i<nArgP; i++)
        {
            int base;

            base= tmp - pourcentage[i] ;

            // Tracer une part
            gdImageFilledRectangle(im, largeur/2 - dimension_graph/2, tmp ,largeur/2 + dimension_graph/2, base, COULEURS[i%(longCouleur)]);

            //----------------------------------- Ecriture d'un label associé s'il existe

            if( (cL!= NULL) && ( i < nArgL))
            {
                int posx, posy;

                posx= largeur/2 + dimension_graph/2 + polices[numPolice]->w;
                posy= base + pourcentage[i] / 2;

                gdImageString(im, polices[numPolice], posx, posy, tabArgL[i], 0x00000000);
            }

            tmp-= pourcentage[i];
        }

        // Dessiner une échelle
        for(int j= 0; j < nArgP; j++)somme+= pourcentage[j];
        for(int pas= hauteur - delta ; pas >= delta ; pas-= (hauteur- 2*delta)/10)
        {
            //printf("\nsomme= %d, pas= %d\n", somme, pas);
            gdImageLine(im, largeur/2 - dimension_graph/2 - 4*polices[numPolice]->w, pas, largeur/2 - dimension_graph/2 - polices[numPolice]->w, pas, 0x00000000);
        }

    }

    //----------------------------------- Tracer d'un histogramme

    if( ( (typeGraphique== 'h') || (typeGraphique== 'H') ) && !d3)
    {
        int x0, y0, x1, y1;
        int espace= polices[numPolice]->w;
        int larg_h= largeur/nArgP - nArgP * espace - 2 * polices[numPolice]->w, marge= 30 * polices[numPolice]->w;

        x0= polices[numPolice]->w;
        x1= x0 + larg_h;
        y0= hauteur - marge;

        if(typeGraphique== 'h')
        {
            for(int j= 0; j < nArgP ;j++)
            {
                pourcentage[j]= (int)( (double)pourcentage[j]*(hauteur - marge - 5 * polices[numPolice]->h)/100);
                //printf("\nrecalcul du pourcentage= %d marge %d 5*police %d hauteur %d large_h %d\n", pourcentage[j], marge, 5*polices[numPolice]->w, hauteur, larg_h);
            }
        }

        for(int i=0; i<nArgP; i++)
        {
            //----------------------------------- Tracer une bare

            gdImageFilledRectangle(im, x0, y0, x1, y0 - pourcentage[i], COULEURS[i]);

            //printf("\nx0, y0= %d, %d - x1, y1 %d,%d - pourcentage[%d]= %d larg_h= %d\n", x0,y0,x1,y1,i, pourcentage[i], larg_h);

            x0= x0 + larg_h + espace;
            x1= x1 + larg_h + espace;
        }
    }


    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //
    //                                          TRACE DES DIFFERENTES FIGURES 3D
    //
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------


    if( ( (typeGraphique== 'c') || (typeGraphique== 'C') ) && d3)
    {
        int epaisseur= hauteur/12;
        unsigned int couleur;

        //----------------------------------- Tracer les contours extérieur des camemberts qui sont entre 0  et 180°
        for(int i=0, tmp= 0; i<nArgP && tmp < 180; i++)
        {
            couleur= COULEURS[i%(longCouleur)];
            int tmp2;

            tmp2=(tmp+pourcentage[i]>180)?180:tmp+pourcentage[i];
            //tmp2= tmp+pourcentage[i];
            for(int i= 1; i< epaisseur; i++)
            {
                gdImageArc (im, largeur/2, hauteur/2 + i, dimension_graph, dimension_graph/2, tmp, tmp2, couleur);
            }
            tmp+= pourcentage[i];
        }

        //----------------------------------- Tracer les camemberts
        for(int i=0, tmp= 0; i<nArgP; i++)
        {
            gdImageFilledArc (im, largeur/2, hauteur/2, dimension_graph, dimension_graph/2, tmp, tmp+pourcentage[i], COULEURS[i%(longCouleur)], gdEdged | gdArc);

            tmp+= pourcentage[i];

        }

        // Traçage des bords
        gdImageArc(im, largeur/2, hauteur/2, dimension_graph, dimension_graph/2, 0, 360, 0);
        gdImageArc(im, largeur/2, hauteur/2 + epaisseur, dimension_graph, dimension_graph/2, 0, 180, 0);
        gdImageLine(im, largeur/2 - dimension_graph/2, hauteur/2, largeur/2 - dimension_graph/2, hauteur/2 + epaisseur, 0x00000000);
        gdImageLine(im, largeur/2 + dimension_graph/2, hauteur/2, largeur/2 + dimension_graph/2, hauteur/2 + epaisseur, 0x00000000);
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //
    //                                          SAUVEGARDE DU GRAPHIQUE
    //
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------


    if (!desc)
    {
        fprintf(stderr, "Erreur de création du fichier.\n");
        gdImageDestroy(im);
        return 1;
    }

    // Sauvegarde du fichier
    gdImagePng(im, desc);
    fclose(desc);

    gdImageDestroy(im);
    return 0;
}

void afficheAide(void)
{
    printf("Utilisation:\npie -p n1,n2,n3,...,nx -l ch1, ch2,...,chx -t type -f fich.png -o h,l,r,cx -c x\n"
           "-p indique les pourcentages\n-l labels\n-t type de graphique type= c ou C pour un camembert, h ou H pour un histo, b ou B pour un bar chart."
           " En minuscule les valeurs seront interprétées comme des %, en majuscule les valeurs sont des valeurs absoles.\n-f Non_du_fichier\n"
           "-o paramètre d'affichage h hauteur, l largeur, r dimension (rayon pour un pie chart) cx couleur de fond en hexadécimal avec opacité 0x000000FF (pour bleu).\n"
           "-c paramètre définissant la taille de la police du texte affiché. Valeur possible: 0 (tiny), 1 (small), 2 (medium bold), 3 (large) et 4 (Giant).\n");
}
