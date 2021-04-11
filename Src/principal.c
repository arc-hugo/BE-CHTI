#include "DriverJeuLaser.h"

// Variables bruitverre.asm
extern int PeriodeSonMicroSec;
extern short SortieSon;

// Fonction GestionSon.s
extern void CallbackSon(void);

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

// Configuration du Timer 4 en fonction de la période en micro seconde
// récupérée dans bruitverre.asm
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
// PWM de fréquence 100kHz
PWM_Init_ff(TIM3, 3, 720);
	
// On ajoute la débordement (priorité 2) sur la fonction CallbackSon de GestionSon.s
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	
// Liaison du canal 3 à la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

//============================================================================	
	
	
while	(1)	PWM_Set_Value_TIM3_Ch3(SortieSon);
}

