//Stephen Tambussi

	.syntax	unified
	.cpu	cortex-m4
	.text
	
	.global	Add
	.thumb_func
Add:
	ADD R0,R0,R1 //Adds value in R0 and R1 and stores it in R0
	BX LR
	
	.global	Less1
	.thumb_func
Less1:
	SUB R0,1 //Subtracts value in R0 by 1 and stores it in R0
	BX LR
	
	.global	Square2x
	.thumb_func
Square2x:
	PUSH {LR} //Needed bc this instruction calls another function
	ADD R0,R0,R0 //Adds value in R0 with itself and stores result in R0
	BL Square 
	POP {PC} //Releases from the stack
	
	.global Last
	.thumb_func
Last:
	PUSH {R4,LR} //Temp register needed to be used
	MOV R4,R0 
	BL SquareRoot
	ADD R0,R0,R4 
	POP {R4,PC} //Releases temp register
	.end
	
	
