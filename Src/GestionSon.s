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
;void CallbackSon ()(
;	SortieSon = Son[Index];
;	Index++;
;	SortieSon += 32768;
;	SortieSon = SortieSon >> 16;
;}

StartSon proc
	ldr r0, =Index
	mov r1, #0
	str r1, [r0]
	bx lr
	endp

CallbackSon proc
	push{r4, r5, r6}
	ldr r0, =Index
	ldr r1, =SortieSon
	ldr r2, =Son
	ldr r3, =LongueurSon
	ldr r4, [r0]
	ldr r3, [r3]
	subs r3, r4
	beq FinSi
Si
	ldrsh r6, [r2, r4, lsl #1]
	mov r5, #719
	add r6, #32768
	mul r6, r5
	lsr r6, #16
	strh r6, [r1]
	push {r0, r1, r2, r3, lr}
	mov r0, r6
	bl PWM_Set_Value_TIM3_Ch3
	pop {r0, r1, r2, r3, lr}
	add r4, #1
	str r4, [r0]
FinSi
	pop{r4, r5, r6}
	bx lr
	endp
	END	