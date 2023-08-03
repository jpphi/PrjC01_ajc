/* Ligne de commande:
 * pie -p n1,n2,n3,...,nx -l ch1, ch2,...,chx -t type - f fich.png -o h,l,r,c
 *
 * Ligne de commande pour test:
 * ./pie -p 10,20,15,15,30 -l 'Label: 10%','Label: 20%','Label: 15%','Label: 15%','Label: 30%' -f CamPartiel.png -o 800,800,400,0x80A0B0C0
 * ./pie -p 5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2, -l 'Label 1: 5 %','Label 1: 3 %','Label 1: 2 %','Label 2: 5 %','Label 2: 3 %','Label 2: 2 %','Label 3: 5 %','Label 3: 3 %','Label 3: 2 %','Label 4: 5 %','Label 4: 3 %','Label 4: 2 %','Label 5: 5 %','Label 5: 3 %','Label 5: 2 %','Label 6: 5 %','Label 6: 3 %','Label 6: 2 %','Label 7: 5 %','Label 7: 3 %','Label 7: 2 %','Label 8: 5 %','Label 8: 3 %','Label 8: 2 %','Label 9: 5 %','Label 9: 3 %','Label 9: 2 %','Label 10: 5 %','Label 10: 3 %','Label 10: 2 %' -f pbArrondi.png -o 800,800,400,0x80A0B0C0 -t c
 *
 * ./pie -p 5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2,5,3,2, -l 'Label 1: 5 %','Label 1: 3 %','Label 1: 2 %','Label 2: 5 %','Label 2: 3 %','Label 2: 2 %','Label 3: 5 %','Label 3: 3 %','Label 3: 2 %','Label 4: 5 %','Label 4: 3 %','Label 4: 2 %','Label 5: 5 %','Label 5: 3 %','Label 5: 2 %','Label 6: 5 %','Label 6: 3 %','Label 6: 2 %','Label 7: 5 %','Label 7: 3 %','Label 7: 2 %','Label 8: 5 %','Label 8: 3 %','Label 8: 2 %','Label 9: 5 %','Label 9: 3 %','Label 9: 2 %','Label 10: 5 %','Label 10: 3 %','Label 10: 2 %' -f pbArrondi.png -o 800,800,400,0x80A0B0C0 -t C
 *
 * ./pie -p 10,20,30,40,50,100,50,60 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 40%','Label: 50%','Label: 100%','Label: 50%','Label: 60%' -f toto1.png -o 800,800,400,0x80A0B0C0
 * ./pie -p 11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9,11,9 -l 'Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9','Label: 11','Label: 9' -f toto.png -o 800,800,400,0x80A0B0C0 -t C
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gd.h>
#include <gdfontl.h>
#include <math.h>

//#define DEBUG 0

int HAUTEUR = 400;
int LARGEUR = 400;
int DIMENSION= 200;
long unsigned int COULEUR_FOND= 0x00FFFFFF;

int taille_police= 10;

long unsigned int COULEURS[]= {0x000000FF, 0x0000FF00, 0x00FF0000, 0x00FFFF00, 0x00FF00FF, 0x0000FFFF, 0x00808080, 0x00AABBCC};

void afficheAide(void);

int main(int argc, char **argv)
{
    char *cP, *cL, *cF, *cO, *mot,  **tabArgL, *chW; //*cT,
    char typeGraphique= 'c'; // Type de grapphiqque par défaut
    int opt;
    int longCouleur= sizeof(COULEURS)/sizeof(long unsigned int), nArgP= 1, nArgL= 1, tailleArgL= 1;
    int *pourcentage= NULL;
    gdImagePtr im;
    FILE *desc;

    if(argc== 1)
    {
        afficheAide();
        return 1;
    }

    while((opt = getopt(argc, argv, "p:t:l:f:o:")) != -1) // pltf
    {
       switch(opt)
       {
        case 'p':
           //printf("option: %c\n", opt);
           //printf("param: %s\n", optarg);
           //printf("Longueur: %d\n", strlen(optarg));
           cP= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
           strcpy(cP, optarg);
        break;

        case 't': // De la forme t x avec x= c pour un camembert, h pour un histo, b pour un bar chart
           printf("option: %c\n", opt);
           printf("param: %s\n", optarg);
           printf("Longueur: %d\n", strlen(optarg));
           //cT= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
           //strcpy(cT, optarg);
           typeGraphique= optarg[0];
        break;

        case 'l':
           cL= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
           strcpy(cL, optarg);
        break;

       case 'f':
           cF= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
           strcpy(cF, optarg);
       break;

       case 'o':
           cO= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
           strcpy(cO, optarg);
           //printf("option: %c\n", opt);
           //printf("param: %s\n", optarg);
           //printf("Longueur: %d\n", strlen(optarg));
           sscanf(cO,"%d,%d,%d,%lx", &HAUTEUR, &LARGEUR, &DIMENSION, &COULEUR_FOND);
           if(HAUTEUR < 200)HAUTEUR=200;
           if(LARGEUR < 200)LARGEUR=200;
           if(DIMENSION < 200)DIMENSION=100;
           //printf("\nH %d L %d R %d C %lx\n", HAUTEUR, LARGEUR, DIMENSION, COULEUR_FOND);
           //if(COULEUR_FOND < 200)HAUTEUR=200;

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
            case 'B':
                break;
            case 'h':
            case 'H':
                break;
            default:
                break;
        }
        //sscanf(mot, "%lf", );
        printf("< nArgP= %d -- pourcentage[%d]= %d\n", nArgP, nArgP-1, pourcentage[nArgP-1]);
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

    //----------------------------------- Tracer du pie
    im = gdImageCreateTrueColor(LARGEUR, HAUTEUR);
    gdImageFilledRectangle(im, 0, 0, LARGEUR-1, HAUTEUR-1, COULEUR_FOND);

    for(int i=0, tmp= 0; i<nArgP; i++)
    {
        double si, co, angle;
        int posx, posy, offset, off_y, off_x, off;
        int x0, y0, x1, y1, ltrait= 10;
        int r= DIMENSION/2 + 10;

        gdImageFilledArc (im, LARGEUR/2, HAUTEUR/2, DIMENSION, DIMENSION, tmp, tmp+pourcentage[i], COULEURS[i%(longCouleur)], gdPie);
        //printf("\ntmp= %d - tmp + pourcentage[%d]= %lu - i%(longCouleur-1)= %d - i= %d- longCouleur= %d", tmp,i, tmp + pourcentage[i], i%(longCouleur), i, longCouleur);

        angle= (double)(tmp + pourcentage[i]/2)*M_PI/180;

        // VARIABLES DE DEBUG
        //double angleDeg= (tmp + pourcentage[i]/2);

        si= sin(angle);
        co= cos(angle);
        posx= (int)(LARGEUR/2 + r * co );
        posy= (int)(HAUTEUR/2 + r * si );

        x0= (int)(LARGEUR/2 + DIMENSION/2 * co );
        y0= (int)(HAUTEUR/2 + DIMENSION/2 * si );
        x1= (int)(LARGEUR/2 + (DIMENSION/2+ltrait) * co );
        y1= (int)(HAUTEUR/2 + (DIMENSION/2+ltrait) * si );
        //printf("\n x0, y0 = %d, %d et x1, y1= %d, %d ltrait= %d -- posx= %d posy=  %d r= %d -- co=  %lf si= %lf \n",x0, y0, x1, y1, ltrait, posx, posy, r, co, si);
        //printf("VAR DEBUG: angle en degré = %lf\n", angleDeg);
        gdImageLine(im, x0, y0, x1, y1, 0x00000000);

        //printf("\nangle %lf, sinus= %lf, cosinus= %lf, pourcentage= %d, tmp %d, angle cumulé %d M_PI= %lf posx= %d posy= %d\n", angle, si, co, pourcentage[i], tmp, tmp + pourcentage[i], M_PI, posx,posy);
        if( (cL!= NULL) && ( i < nArgL))
        {
            if( (angle > M_PI/2) && (angle < 3*M_PI/2) )
                offset= -taille_police * strlen(tabArgL[i]);
            else
                offset= 0;

            if( (angle > M_PI/3) && (angle < 4*M_PI/3) )
                off= (int)(taille_police*si);
            else if( (angle > 4*M_PI/3) && (angle < 5*M_PI/3) )
                off= (int)(taille_police * si);
            else
                off= 0;
            off_y= (int)(taille_police * 1.5 * si);
            off_x= (int)(taille_police * 1.5 * co);
            //gdImageString(im, gdFontLarge, posx, posy, tabArgL[i], 0x00000000);
            gdImageString(im, gdFontLarge, posx + offset + off_x , posy + off_y + off,tabArgL[i], 0x00000000);
            //printf("\n Dans l affichage chaine: %s - offset= %d\n", tabArgL[i], offset);
        }

        tmp+= pourcentage[i];

    }


    if (!desc) {
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
    printf("Utilisation:\npie -p n1,n2,n3,...,nx -l ch1, ch2,...,chx -t type -f fich.png -o h,l,r,cx\n"
           "-p indique les pourcentages\n-l labels\n-t type de graphique type= c pour un camembert, h pour un histo, b pour un bar chart\n-f Non_du_fichier\n"
           "-o paramètre d'affichage h hauteur, l largeur, r dimension (rayon pour un pie chart) cx couleur de fond en hexadécimal avec opacité 0x000000FF (pour bleu).\n");

}
