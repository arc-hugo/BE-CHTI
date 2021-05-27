	PRESERVE8
	THUMB   
	
	export CallbackSon
	export StartSon
	import Son
	import LongueurSon
	include Driver/DriverJeuLaser.inc

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly

;Section RAM (read write):
	area    maram,data,readwrite

SortieSon dcw 0
Index dcd 0
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


;Algo C
;void StartSon ()(
;	Index = 0;
;}
StartSon proc
	ldr r0, =Index
	mov r1, #0
	str r1, [r0]
	bx lr
	endp

;Algo C
;void CallbackSon ()(
;	if (Index < LongueurSon) {
;		SortieSon = Son[Index];
;		SortieSon = ((SortieSon + 32768)*718) >> 16;
;		PWM_Set_Value_TIM3_Ch3(SortieSon)
;		Index++;
;	}
;}
CallbackSon proc
	; Récupération des adresse et des données
	push{r4, r5, r6}
	ldr r0, =Index
	ldr r1, =SortieSon
	ldr r2, =Son
	ldr r3, =LongueurSon
	ldr r4, [r0]
	ldr r3, [r3]
	; Si l'index n'a pas atteint la fin du tableau, on entre dans Si
	subs r3, r4
	beq FinSi
Si
	; On charge la valeur de son suivante
	ldrsh r6, [r2, r4, lsl #1]
	; Calcul de mise à l'echelle de la valeur du son
	mov r5, #719
	add r6, #32768
	mul r6, r5
	lsr r6, #16
	; Stockage de la valeur du son dans SortieSon
	strh r6, [r1]
	; Appel de la fonction PWM_Set_Value_TIM3_Ch3
	push {r0, r1, r2, r3, lr}
	mov r0, r6
	bl PWM_Set_Value_TIM3_Ch3
	pop {r0, r1, r2, r3, lr}
	; Incrémentation de l'index pour le prochain appel
	add r4, #1
	str r4, [r0]
FinSi
	; Sortie de fonction
	; Remise à zéro si nécessaire
	
	pop{r4, r5, r6}
	bx lr
	endp
	END	