//Stephen Tambussi

	.syntax unified
	.cpu cortex-m4
	.text

//CopyCell	
	.global CopyCell
	.thumb_func
CopyCell: //R0=dst, R1=src
	//R2=row,R3=col
	LDR R2,=0
outerloop1:
	LDR R3,=0//resets col for innerloop
	CMP R2,60 //row<60?
	BHS Finish1
innerloop1:
	CMP R3,60 //col<60?
	BHS innerEnd1
	LDR R12,[R1,R3,LSL 2]//R12=src[col]
	STR R12,[R0,R3,LSL 2]//R12-->dst[col]
	ADD R3,R3,1 //col++
	B innerloop1
innerEnd1:
	ADD R2,R2,1 //row++
	ADD R0,R0,960
	ADD R1,R1,960
	B outerloop1
Finish1:
	BX LR

//FillCell	
	.global FillCell
	.thumb_func
FillCell: //R0=dst, R1=pixel
	LDR R2,=0//row
outerloop2:
	LDR R3,=0//resets col for innerloop
	CMP R2,60 //row<60?
	BHS Finish2
innerloop2:
	CMP R3,60 //col<60?
	BHS innerEnd2
	STR R1,[R0,R3,LSL 2]//dst[col]=pixel
	ADD R3,R3,1 //col++
	B innerloop2
innerEnd2:
	ADD R2,R2,1 //row++
	ADD R0,R0,960
	B outerloop2
Finish2:
	BX LR
	
	.end
	