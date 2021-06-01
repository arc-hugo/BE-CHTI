#ifndef GESTIONSON_H__
#define GESTIONSON_H__

// Variables bruitverre.asm
// P�riode d'�chantillonnage du son
extern int PeriodeSonMicroSec;

// Fonction StartSon.
// R�initialise l'index du tableau de valeur de son afin de pouvoir le rejouer.
void StartSon(void);

// Fonction InitSon
// Initialise l'index hors du tableau pour ne pas jouer le son au d�but
void InitSon(void);

// Fonction CallbackSon.
// Handler d'interruption horloge permettant de mettre � jour la valeur du son � jouer.
void CallbackSon(void);

#endif
