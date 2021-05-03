

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre(short int *, char);
extern short int  LeSignal[];

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

// Valeur de k pour les 6 signaux
char k[] = {17, 18, 19, 20, 23, 24};
int DFT[64];

for (int i = 0; i < 64; i++)
	DFT[i] = DFT_ModuleAuCarre(LeSignal, i);

//============================================================================	
	
	
while	(1)
	{
		
	}
}

