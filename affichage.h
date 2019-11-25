#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

/** Fonction principale : permet de creer puis d'afficher le tableau dans le
*         terminal a l'aide d'une serie de concatenantions
*
* @param  classement un pointeur vers un tableau de voiture triees
* @param  manche     un numero indiquant la partie de la serie de course dans laquelle
*                    on est
*/
void afficherTableauScore(voiture *classement[], int manche);

/**
*@param tuple *classement[] un pointeur vers un tableau de voiture triees en memoire partagee et locale
*@param int manche          un numero indiquant la partie de la serie de course dans laquelle
*                           on est
* fait afficher dans la console le classement et des voitures et leur temps
* N.B: tuple utilise pour gestion des pointeurs entre les pointeurs de la memoire locale et partagee
*/
void afficherTableauScoreQualif(tuple *classement[], int manche);

/** Permet de generer et de remplir un case pour le tableau.
*  ATTENTION : necessite de faire un free apres utilisation car on utilise un malloc
*
* @param  tailleCellule  la taille de la cellule qu'on desire creer
* @param  input          nombre que l'on desire introduire dans la cellule
*                        si le nombre == 0, on le remplacera par le string NA
* @param  sizeInput      le nombre de chiffres constituant le parametre input
* @return                renvoie un poiteur vers la zone memoire contenant notre cellule
*/
char* creationCelluleNombre(int tailleCellule, int input, int sizeInput);

/** Permet de choisir entre les differents etats possibles pour la voiture a savoir
*  OUT, P ou GO
*
* @param  status  le status de la voiture sous format numerique
* @return         retourne une chaine de caracteres de bonne taille pour la cellule
*/
char* decodageStatus(int status);

/** Permet de creer le titre du tableau.  Selectionne le titre correcte pour la
*  course en cours
*
* @param  manche  un nombre permettant de determiner la course dans laquelle on est.
*                 Doit etre compris entre 1 et 7 inclus
* @return         renvoie un poiteur vers la zone memoire contenant notre ligne
*/
char* creationManche(int manche);

#endif // AFFICHAGE_H_INCLUDED
