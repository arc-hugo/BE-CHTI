#ifndef GESTIONSON_H__
#define GESTIONSON_H__

// Fonction StartSon.
// R�initialise l'index du tableau de valeur de son afin de pouvoir le rejouer.
void StartSon(void);

// Fonction CallbackSon.
// Handler d'interruption horloge permettant de mettre � jour la valeur du son � jouer.
void CallbackSon(void);

#endif
