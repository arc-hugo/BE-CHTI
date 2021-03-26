	PRESERVE8
	THUMB   
	
	export CallbackSon
	export SortieSon

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite

SortieSon dcw 0
IndexTableSon dcd 0
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		



CallbackSon proc

	
	bx lr
	endp
	END	