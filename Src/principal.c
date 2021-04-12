#include "DriverJeuLaser.h"
#include "GestionSon.h"

// Variables bruitverre.asm
extern int PeriodeSonMicroSec;

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

// Configuration du Timer 4 en fonction de la p�riode en micro seconde
// r�cup�r�e dans bruitverre.asm
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
Timer_1234_Init_ff(TIM2, 10000*72*PeriodeSonMicroSec);
// PWM de fr�quence 100kHz
PWM_Init_ff(TIM3, 3, 720);
	
// On ajoute la d�bordement (priorit� 2) sur la fonction CallbackSon de GestionSon.s
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
Active_IT_Debordement_Timer(TIM2, 1, StartSon);
	
// Liaison du canal 3 � la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

//============================================================================	
	
	
while	(1) {}
}

