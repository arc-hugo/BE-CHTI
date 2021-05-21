#include "DriverJeuLaser.h"
#include "Affichage_Valise.h"

extern int DFT_ModuleAuCarre(short int *, char);

// Tableau de 64 entiers courts (16 bits)
short int Buffer[64];

// Tableau de résultat de la DFT
int DFT[64];


// Fonction callback de SysTick
// Enregistre les valeurs de la DMA et appel la DFT dessus
void callbackSystick() {
	// Démarragede la DMA
	Start_DMA1(64);
	// Attente
	Wait_On_End_Of_DMA1();
	// Arrêt
	Stop_DMA1;
	
	for(char i = 0; i < 64; i++)
		DFT[i] = DFT_ModuleAuCarre(Buffer, i);
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

/*	PARTIE SON	*/
	
	
/*	PARTIE DFT/DMA 	*/
// Réglage de la périodicit du timer SysTick à 5ms
Systick_Period_ff(360000);
// Configuration de l'interruption du timer SysTick (callbackSystick en priorité 1)
Systick_Prio_IT(1, callbackSystick);
// Lancement de Systick et validation des interruptions
SysTick_On;
SysTick_Enable_IT;

// Réglage de la durée de capture du signal (une microseconde)
Init_TimingADC_ActiveADC_ff(ADC1, 72);
// Choix de la pin dù entrée (PA2)
Single_Channel_ADC(ADC1, 2);
// Configuration de TIM2 pour le déclanchemment de l'ADC
Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);

// Définition du buffer à remplir par la DMA
Init_ADC1_DMA1(0, Buffer);

/*	AFFICHAGE VALISE	*/

//============================================================================	

while	(1)
	{

	}
}

