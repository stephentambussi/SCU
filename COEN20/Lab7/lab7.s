//Stephen Tambussi
	.syntax	unified
	.cpu	cortex-m4
	.text
	
	.global Bills
	.thumb_func
Bills: //twenties
	LDR R3,=214748365 //R3=2^32/20
	SMMUL R2,R0,R3
	STR	R2,[R1] //paper.twenties=quotient
	LSL	R3,R2,4 //R3=16*cnt
	ADD R3,R3,R2,LSL 2 //R3=20*cnt
	SUB	R0,R0,R3 //R0=remainder
	B	GeneralDivide
	
	.global GeneralDivide
	.thumb_func
GeneralDivide:
	//tens&dimes
	LDR R3,=429496730 //R3=2^32/10
	SMMUL R2,R0,R3
	STR R2,[R1,4] //struct.tens=quotient
	LSL R3,R2,3 //R3=8*cnt
	ADD R3,R3,R2,LSL 1 //R3=10*cnt
	SUB R0,R0,R3 //R0=remainder
	
	//fives&nickels
	LDR R3,=858993459 //R3=2^32/5
	SMMUL R2,R0,R3
	STR R2,[R1,8] //struct.fives=quotient
	LSL R3,R2,2 //R3=4*cnt
	ADD R3,R3,R2,LSL 0 //R3=5*cnt
	SUB R0,R0,R3 //R0=remainder
	
	//ones&pennies
	STR R0,[R1,12] //struct.ones=remainder
	BX	LR
	
	.global Coins
	.thumb_func
Coins: //quarters
	LDR R3,=171798692 //R3=2^32/25
	SMMUL R2,R0,R3
	STR	R2,[R1] //coins.quarters=quotient
	LSL	R3,R2,4 //R3=16*cnt
	ADD R3,R3,R2,LSL 3 //R3=24*cnt
	ADD R3,R3,R2,LSL 0 //R3=25*cnt
	SUB	R0,R0,R3 //R0=remainder
	B	GeneralDivide
	
	.end

