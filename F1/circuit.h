#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED
#include "secteurs.h"
#include <windows.h>
#include <time.h>
#define true 1
#define false 0



#endif // CIRCUIT_H_INCLUDED
/**
*
*simule un tour dans un circuit
*
*
*/
int tour(){

    int total=0;//temps total
    int crash = false;//boolean pour le crash de la voiture
    int s = 0;//temps pour un secteur
    int i=0;//compteur boucle

    while (i<9 && crash != true){

        s = secteur(300,500);
        Sleep(s*10);// endormir le processus pendant s*10 milliseconde
        if(s == 0){//test si il y a un crash
            crash = true;
            printf("crash sur le secteur %d\n",i);
        }


        total += s;//ajout au temps total de la voiture dans le circuit
        i++;
        printf("temps du secteur %d: %d seconde\n",i, s);
    }

    int min = total%3600/60;//minutes
    int sec = total%60;//secondes
    printf("temps total est de %dmin %ds\n",min, sec);
    return 0;
}
int essaiLibre(int chrono){
    int total=0;//temps total
    int crash = false;//boolean pour le crash de la voiture
    int s = 0;//temps pour un secteur
    int i = 1;
    while (total<=chrono && crash != true){

        s = secteur(90,250);
        Sleep(s*10);// endormir le processus pendant s*10 milliseconde
        if(s == 0){//test si il y a un crash
            crash = true;
            printf("crash sur le secteur %d\n",i);
        }
        if((i%2)==0){//si il passe dans le secteur 2
           // k.tempSecteur2=s;
           printf("temps du secteur %d: %d seconde\n",i, s);
        }
        else if((i%3)==0){//si il passe dans le secteur 3
           // k.tempSecteur3=s;
           printf("temps du secteur %d: %d seconde\n",i, s);
        }
        else{//si il passe dans le secteur 1
           // k.tempSecteur1=s;
           printf("temps du secteur %d: %d seconde\n",i, s);
        }


        total += s;//ajout au temps total de la voiture dans le circuit
        // printf("temps du secteur %d: %d seconde\n",i, s);
        i++;
    }
    return total;
}
