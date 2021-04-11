	PRESERVE8
	THUMB   
		

; ====================== zone de r�servation de donn�es,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
VarTime	dcd 0
	
	export VarTime

	
; ===============================================================================================
	
;constantes (�quivalent du #define en C)
TimeValue	equ 900000


	EXPORT Delay_100ms ; la fonction Delay_100ms est rendue publique donc utilisable par d'autres modules.

		
;Section ROM code (read only) :		
	area    moncode,code,readonly
		


; REMARQUE IMPORTANTE 
; Cette mani�re de cr�er une temporisation n'est clairement pas la bonne mani�re de proc�der :
; - elle est peu pr�cise
; - la fonction prend tout le temps CPU pour... ne rien faire...
;
; Pour autant, la fonction montre :
; - les boucles en ASM
; - l'acc�s �cr/lec de variable en RAM
; - le m�canisme d'appel / retour sous programme
;
; et donc poss�de un int�r�t pour d�buter en ASM pur

Delay_100ms proc
	
	    ldr r0,=VarTime; r0 = adresse de VarTime
						  
		ldr r1,=TimeValue; r1 = TimeValue
		str r1,[r0]; m�moire point�e par r0 = r1 (valeur de VarTime = TimeValue)
		
BoucleTempo	; Entr�e de boucle
		ldr r1,[r0]; r1 = m�moire point�e par r0 (r1 = TimeValue)		
						
		subs r1,#1; r1-- (TimeValue--)
		str  r1,[r0]; m�moire point�e par r0 = r1 (valeur de VarTime = TimeValue)
		bne	 BoucleTempo; si la valeur stock�e est diff�rente de 0, on reboucle
			
		bx lr; saut indirect vers lr (adresse de retour), permet de sortir de la fonction
		endp
		
		
	END	