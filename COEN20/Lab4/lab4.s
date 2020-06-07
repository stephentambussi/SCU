//Stephen Tambussi
	.syntax	unified
	.cpu	cortex-m4
	.text
//Discriminant
	.global	Discriminant
	.thumb_func
Discriminant:
	MUL R1,R1,R1 //b*b
	LSL R0,R0,2	//R0=4a
	MLS R0,R0,R2,R1	//R0=b^2 - 4ac
	BX	LR

//Root1
	.global	Root1
	.thumb_func
Root1:
	PUSH {R4,R5,LR}
	MOV	R4,R0 //R0=a -->R4
	MOV R5,R1 //R1=b -->R5
	BL Discriminant//Calls functions
	BL SquareRoot
	SUB R0,R0,R5 //SquareRoot(Discriminant(..)) - b
	LSL R4,1	//2*a
	SDIV R0,R0,R4 //everything/2a
	POP {R4,R5,PC}
	
//Root2
	.global Root2
	.thumb_func
Root2:
	PUSH {R4,R5,LR}
	MOV	R4,R0 //R0=a -->R4
	MOV R5,R1 //R1=b -->R5
	BL Discriminant
	BL SquareRoot
	NEG	R0,R0 //negate SquareRoot(Discriminant(..))
	SUB R0,R0,R5 //SquareRoot(Discriminant(..)) - b
	LSL R4,1	//2*a
	SDIV R0,R0,R4 //everything/2a
	POP {R4,R5,PC}
	
//Quadratic
	.global	Quadratic
	.thumb_func
Quadratic:
	//R0=x,R1=a,R2=b,R3=c
	MLA	R1,R0,R1,R2 //ax+b --> R1 //perserves x
	MLA R0,R0,R1,R3 //x(ax+b)+c
	BX	LR
	
	.end
	

	