#include "DriverJeuLaser.h"
#include "GestionSon.h"

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

/*
 *	Configuration de l'interruption de mise à jour la lecture des échantillons du son
 */
// Timer 4 en fonction de la période en microsecondes
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
// On ajoute le débordement (priorité 2) sur la fonction CallbackSon de GestionSon.s
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	
	
/*
 *	Configuration de la PWM afin de lire le son
 */
// PWM de fréquence 100kHz
PWM_Init_ff(TIM3, 3, 720);
// Liaison du canal 3 à la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

/*
 *	Configuration de l'interruption de remise à zéro de la lecture des échantillons
 */
// Timer 2 en fonction de la période en dizaine de millisecondes
Timer_1234_Init_ff(TIM2, 10000*72*PeriodeSonMicroSec);
// Débordement sur la fonction StarSon avec une plus grande priorité que Timer 4
Active_IT_Debordement_Timer(TIM2, 1, StartSon);

//============================================================================	
	
	
while	(1) {}
}

