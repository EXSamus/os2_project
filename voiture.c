#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
//#include <windows.h>
#include "circuit.h"
#include "secteurs.h"
#include "voiture.h"
#include "constantes.h"

/*
*
* Ce fichier .c est compile puis lance lorsqu'un processus fils est cree
* il fait appel a des headers pour utiliser les fonctions de voitures, du circuits, ...
* il simule une course selon les parametres entree avec une voiture
*
*/

/******************  definition des variables globales  ***********************/
int nombreFiliale;

/****************  definition des methodes du processus  **********************/
void initVoiture(int stat, int read, int id, voiture *shm);
void attenteQuali(voiture *shm, int id);


/** Methode principale : simule le fonctionnement d'une voiture de course
*   divisee en 3 parties distinctes :
*
*     - les periodes d'essais
*         lance la periode d'essais choisie grace au nombre passer en parametre
*         au lancement du processus : 1 pour la periode 1, 2 pour la periode 2,
*         3 pour la periode 3
*     - les periodes de qualifications
*         chiffre en parametre 4 : enchaine 3 sessions de qualifacation a la suite.
*         la methode attenteQuali permet de synchroniser les processus pour
*         les relancer a peu pres en meme temps
*     - la course principle
*         chiffre en parametre 7 : lance simplement la methode Course()
*
*/
int main(int argc, char* argv[]){
  srand(time(NULL) ^ (getpid()<<16));

  sem_t *sem;
  voiture *shm;
  //initialisation des differentes variables
  nombreFiliale = atoi(argv[2]);
  int id = atoi(argv[4]);

  shm = (voiture*) shmat(atoi(argv[1]), NULL, 0);
  initVoiture(2, 0, id, shm);

/********************  Les periodes d'essais ********************************/

  if (strcmp(argv[3], "P1") == 0) {
    essaiLibreQuali(P1, &shm[nombreFiliale]);
  }
  else if (strcmp(argv[3], "P2") == 0) {
    essaiLibreQuali(P2, &shm[nombreFiliale]);
  }
  else if (strcmp(argv[3], "P3") == 0) {
    essaiLibreQuali(P3, &shm[nombreFiliale]);
  }

/********************** Les periodes de qualification ***********************/

  else if (strcmp(argv[3], "Q") == 0) {
    essaiLibreQuali(Q1, &shm[nombreFiliale]);
    attenteQuali(shm, id);

    essaiLibreQuali(Q2, &shm[nombreFiliale]);
    attenteQuali(shm, id);

    essaiLibreQuali(Q3, &shm[nombreFiliale]);
  }

/************************** La course principale ****************************/

  else{
    Course(TOURS_COURSE, &shm[nombreFiliale]);
  }

  /*************************** Fin du programme *******************************/

  shm[nombreFiliale].status = -1;

  shmdt(shm);
  exit(EXIT_SUCCESS);
}

/** initialisation d'une voiture avec toutes ses variables
*
* @param int stat     initialise la variable status de la voiture
                      valeur autorisee {-1,0,1,2}
* @param int read     initialise la variable ready de la voiture
                      valeur autorisee {-1,0,1,2}
* @param int id       initialise la variable id de la voiture
* @param voiture* shm pointeur vers l'emplacement en memoire partagee de la voiture
*
* N.B. pour plus d'infos sur les differents parametre aller voir le fichier voiture.h
*/
void initVoiture(int stat, int read, int id, voiture *shm){

  shm[nombreFiliale].id = id;
  shm[nombreFiliale].tempSecteur1 = 0;
  shm[nombreFiliale].tempSecteur2 = 0;
  shm[nombreFiliale].tempSecteur3 = 0;
  shm[nombreFiliale].meilleurTemps = 0;
  shm[nombreFiliale].tempsTotal = 0;
  shm[nombreFiliale].tours = 1;
  shm[nombreFiliale].status = stat;
  shm[nombreFiliale].ready = read;
  shm[nombreFiliale].changeOrdre = FALSE;
}

/**permet a la voiture d'attendre que le processus pere finisse de synchroniser les
*  voitures avant de lancer une nouvelle periode de qualification
*
* @param voiture* shm pointeur vers l'emplacement en memoire partagee de la voiture
* @param int id       numero de la voiture
*
*/
void attenteQuali(voiture *shm, int id){
  while (shm[nombreFiliale].ready == -1) { //mise en attente de de la voirure en attendant les autres
    sleep(TEMPS_ATTENTE);
  }
  if (shm[nombreFiliale].status == -1) {//fin du processus
    initVoiture(-1, -1, id, shm);
    shmdt(shm);
    printf("%s\n", "fin des qualif");
    exit(EXIT_SUCCESS);
  }
  else{	//mettre voiture dans l'etat course
    initVoiture(2, 0, id, shm);
    printf("%s\n", "gogogo");
  }
  return;
}
