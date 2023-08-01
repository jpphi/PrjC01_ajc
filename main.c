/* Ligne de commande:
 * pie -p n1,n2,n3,...,nx -l ch1, ch2,...,chx -t type - f fich.png -o h,l,r,c
 *
 * Ligne de commande pour test:
 * ./pie -p 10,20,30,40,50,100 -l 'cou avec espace',azerty,gsdhlkj,encore,etencore,enfin -f toto.png -o 800,800,400,0x80A0B0C0
 * ./pie -p 10,20,30,40,50,100,50,60 -l 'Label: 10%','Label: 20%','Label: 30%','Label: 40%','Label: 50%','Label: 100%','Label: 50%','Label: 60%' -f toto.png -o 800,800,400,0x80A0B0C0
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
int RAYON= 200;
long unsigned int COULEUR_FOND= 0x00FFFFFF;

int taille_police= 10;

long unsigned int COULEURS[]= {0x000000FF, 0x0000FF00, 0x00FF0000, 0x00FFFF00, 0x00FF00FF, 0x0000FFFF, 0x00808080, 0x00AABBCC};

void afficheAide(void);

int main(int argc, char **argv)
{
    char *cP, *cT, *cL, *cF, *cO, *mot,  **tabArgL, *chW;
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

        case 't':
            cT= (char *)malloc( (strlen(optarg) * sizeof(char)) + sizeof(char));
            strcpy(cT, optarg);
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
           sscanf(cO,"%d,%d,%d,%lx", &HAUTEUR, &LARGEUR, &RAYON, &COULEUR_FOND);
           if(HAUTEUR < 200)HAUTEUR=200;
           if(LARGEUR < 200)LARGEUR=200;
           if(RAYON < 200)RAYON=100;
           //printf("\nH %d L %d R %d C %lx\n", HAUTEUR, LARGEUR, RAYON, COULEUR_FOND);
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
        //printf("mot= %s", mot);
        pourcentage= (int *)realloc(pourcentage, nArgP * sizeof(int));
        sscanf(mot, "%d", &pourcentage[nArgP-1]);
        //printf("< nArgP= %d\n", nArgP);
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

    //int pourcentage[]= {10,50,40,25,45};

    for(int i=0, tmp= 0; i<nArgP; i++)
    {
        double si, co;
        double angle;
        int posx, posy, offset;

        gdImageFilledArc (im, LARGEUR/2, HAUTEUR/2, RAYON, RAYON, tmp, tmp+pourcentage[i], COULEURS[i%(longCouleur)], gdPie);
        //printf("\ntmp= %d - tmp + pourcentage[%d]= %lu - i%(longCouleur-1)= %d - i= %d- longCouleur= %d", tmp,i, tmp + pourcentage[i], i%(longCouleur), i, longCouleur);

        angle= (double)(tmp + pourcentage[i]/2)*M_PI/180;
        si= sin(angle); // ((float)tmp);
        co= cos(angle); // ((float)tmp);
        posx= (int)(LARGEUR/2 + RAYON/2 * co);
        posy= (int)(HAUTEUR/2 + RAYON/2 * si);


        //printf("\nangle %lf, sinus= %lf, cosinus= %lf, pourcentage= %d, tmp %d, angle cumulé %d M_PI= %lf posx= %d posy= %d\n", angle, si, co, pourcentage[i], tmp, tmp + pourcentage[i], M_PI, posx,posy);
        if( (cL!= NULL) && ( i < nArgL))
        {
            if( (angle > M_PI/2) && (angle < 3*M_PI/2) )offset= -taille_police * strlen(tabArgL[i]);
            else offset= 0;
            gdImageString(im, gdFontLarge, posx + offset , posy,tabArgL[i], 0x00000000);
            //printf("\n Dans l affichage chaine: %s - offset= %d\n", tabArgL[i], offset);
            //gdImageString(im, gdFontLarge, posx , posy,"tutu", 0x00000000);
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
           "-p indique les pourcentages\n-l labels\n-t type de graphique\n-f Non_du_fichier\n"
           "-o paramètre d'affichage h hhauteur, l largeur, r rayon c couleur de fond en hexadécimal avec opacité 0x000000FF (pour bleu)");

}
