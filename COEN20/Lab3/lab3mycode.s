//Stephen Tambussi
	.syntax	unified
	.cpu	cortex-m4
	.text
	
	.global	UseLDRB
	.thumb_func
UseLDRB:
	.REPT 512//Copying one byte at a time
	LDRB R2, [R1], 1
	STRB R2, [R0], 1
	.ENDR
	BX LR
	
	.global UseLDRH
	.thumb_func
UseLDRH:
	.REPT 256//Copying two bytes at a time
	LDRH R2, [R1], 2
	STRH R2, [R0], 2
	.ENDR
	BX LR
	
	.global UseLDR
	.thumb_func
UseLDR:
	.REPT 128//four bytes at a time
	LDR R2, [R1], 4
	STR R2, [R0], 4
	.ENDR
	BX LR
	
	.global	UseLDRD
	.thumb_func
UseLDRD:
	.REPT 64//eight bytes at a time
	LDRD R3,R2, [R1], 8
	STRD R3,R2, [R0], 8
	.ENDR
	BX LR
	
	.global	UseLDM
	.thumb_func
UseLDM:
	PUSH {R4-R9}
	.REPT 16
	LDMIA R1!,{R2-R9}//Loads, then increments
	STMIA R0!,{R2-R9}//Stores, then increments
	.ENDR
	POP {R4-R9}
	BX LR
	
	.end