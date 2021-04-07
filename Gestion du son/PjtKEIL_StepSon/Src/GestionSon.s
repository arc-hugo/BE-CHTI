	PRESERVE8
	THUMB   
	
	export CallbackSon
	export SortieSon
	import Son
	import LongueurSon

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
;void CallbackSon ()(
;	SortieSon = Son[Index];
;	Index++;
;	SortieSon += 32768;
;	
;}

CallbackSon proc
	push{r4, r5, r6}
	ldr r0, =Index
	ldr r1, =SortieSon
	ldr r2, =Son
	ldr r3, =LongueurSon
	ldr r4, [r0]
	ldr r3, [r3]
	mov r5, #2
	mul r3, r5
	subs r3, r4
	beq FinSi
Si
	ldrsh r6, [r2, r4]
	mov r5, #719
	add r6, #32768
	mul r6, r5
	lsr r6, #16
	strh r6, [r1]
	add r4, #2
	str r4, [r0]
FinSi
	pop{r4, r5, r6}
	bx lr
	endp
	END	