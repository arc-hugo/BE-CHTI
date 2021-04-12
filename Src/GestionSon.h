#ifndef GESTIONSON_H__
#define GESTIONSON_H__

// Fonction StartSon.
// Réinitialise l'index du tableau de valeur de son afin de pouvoir le rejouer.
void StartSon(void);

// Fonction CallbackSon.
// Handler d'interruption horloge permettant de mettre à jour la valeur du son à jouer.
void CallbackSon(void);

#endif
