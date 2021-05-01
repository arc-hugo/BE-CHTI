#include "DriverJeuLaser.h"
#include "GestionSon.h"

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

/*
 *	Configuration de l'interruption de mise � jour la lecture des �chantillons du son
 */
// Timer 4 en fonction de la p�riode en microsecondes
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
// On ajoute le d�bordement (priorit� 2) sur la fonction CallbackSon de GestionSon.s
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	
	
/*
 *	Configuration de la PWM afin de lire le son
 */
// PWM de fr�quence 100kHz
PWM_Init_ff(TIM3, 3, 720);
// Liaison du canal 3 � la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

/*
 *	Configuration de l'interruption de remise � z�ro de la lecture des �chantillons
 */
// Timer 2 en fonction de la p�riode en dizaine de millisecondes
Timer_1234_Init_ff(TIM2, 10000*72*PeriodeSonMicroSec);
// D�bordement sur la fonction StarSon avec une plus grande priorit� que Timer 4
Active_IT_Debordement_Timer(TIM2, 1, StartSon);

//============================================================================	
	
	
while	(1) {}
}

