#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"

extern int DFT_ModuleAuCarre(short int *, char);

// Tableau des indices des 6 joueurs
char k[6]= {17, 18, 19, 20, 23, 24};
// Tableau de score des 6 joureurs
char Scores[6] = {0,0,0,0,0,0};
// Tableau de compte des occurances des signaux sur une période de 100ms
char Comptes[6] = {0,0,0,0,0,0};
// Tableau de 64 entiers courts (16 bits)
short int Buffer[64];
// Tableau de résultat de la DFT
int DFT[6];

// Fonction callback de SysTick
// Comptabilise les points des signaux corrspondant aux différents joueurs
void callbackSystick() {
	// Démarragede la DMA
	Start_DMA1(64);
	// Attente
	Wait_On_End_Of_DMA1();
	// Arrêt
	Stop_DMA1;
	
	for (int i = 0; i < 6; i++) {
		// Lancement de la DFT sur les résultats de la DMA pour les 6 signaux seulement
		DFT[i] = DFT_ModuleAuCarre(Buffer, k[i]);
		
		// Si l'un de nos signaux est reçu, on incrémente le tableau de compte à l'emplacement correspondant
		if ((DFT[i] >> 22) >= 60) {
			Comptes[i]++;
		}
		// Sinon on le remet à zéro
		else {
			Comptes[i] = 0;
		}
		// Le tableau doit rester entre 0 et 20 (période 0 à 100ms)
		Comptes[i] %= 21;
		
		// Si le signal a été reçu plus de la moitié du temps (>= 50ms), on incrémente le score du joueurs
		// Et on joue le son
		if (Comptes[i] == 12) {
			Scores[i]++;
			StartSon();
		}
		// Le score doit rester entre 0 et 99
		Scores[i] %= 100;
		
		// Mise à jour du score de l'afficheur correspondant
		if (i < 4) {
				Prepare_Afficheur(i+1,Scores[i]);
		}
	}
	Mise_A_Jour_Afficheurs_LED();
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

/*	PARTIE SON	*/
//	TIMER 4		//
// Timer 4 en fonction de la période en microsecondes
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
// On ajoute le débordement (priorité 2) sur la fonction CallbackSon de GestionSon.s
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);

//	TIMER 3		//
// PWM de fréquence 100kHz
PWM_Init_ff(TIM3, 3, 720);
// Liaison du canal 3 à la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

/*	PARTIE DFT/DMA 	*/
// Réglage de la périodicit du timer SysTick à 5ms
Systick_Period_ff(360000);
// Configuration de l'interruption du timer SysTick (callbackSystick en priorité 1)
Systick_Prio_IT(1, callbackSystick);
// Lancement de Systick et validation des interruptions
SysTick_On;
SysTick_Enable_IT;

//	TIMER 2		//
// Réglage de la durée de capture du signal (une microseconde)
Init_TimingADC_ActiveADC_ff(ADC1, 72);
// Choix de la pin dù entrée (PA2)
Single_Channel_ADC(ADC1, 2);
// Configuration de TIM2 pour le déclanchemment de l'ADC
Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);

// Définition du buffer à remplir par la DMA
Init_ADC1_DMA1(0, Buffer);

/*	PARTIE AFFICHAGE	*/
// Initialisation des périphériques d'affichage et de choix des capteurs
Init_Affichage();
// Mise à zéro de tous les afficheurs
for (int i = 1; i < 5; i++)
	Prepare_Afficheur(i,0);
// Choix du capteur cible
Choix_Capteur(1);
// Allumage de la LED indiquant la cible
Prepare_Set_LED(LED_Cible_1);
// Mise à jour des afficheurs (envoie de trame)
Mise_A_Jour_Afficheurs_LED();

//============================================================================	

while	(1)
	{
		
	}
}

