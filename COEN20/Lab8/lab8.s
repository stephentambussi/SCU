//Stephen Tambussi
	.syntax	unified
	.cpu	cortex-m4
	.text
	
	.global Discriminant
	.thumb_func
Discriminant:
	VMUL.F32	S2,S0,S2 //S2=a*c
	VMUL.F32	S0,S1,S1 //S0=b*b
	VMOV	S1,4.0
	VMLS.F32	S0,S1,S2 //S0=b^2 -4ac
	BX	LR
	
	.global Quadratic
	.thumb_func
Quadratic:
	VMLA.F32 S2,S0,S1 //ax+b = S2
	VMLA.F32 S3,S2,S0 //x(ax+b)+c
	VMOV S0,S3
	BX LR
	
	.global Root1
	.thumb_func
Root1:
	PUSH {R4,R5,LR}
	VMOV R4,S0 //S0=a --> R4
	VMOV R5,S1 //S1=b --> R5
	BL Discriminant
	VMOV S1,R5
	VSQRT.F32 S0,S0 //sqrt(discriminant)
	VSUB.F32 S0,S0,S1 //sqrt(discriminant)-b
	VMOV S1,R4
	VMOV S3,2.0
	VMUL.F32 S1,S3,S1 //2*a
	VDIV.F32 S0,S0,S1 //everything/2a
	POP {R4,R5,PC}
	
	.global Root2
	.thumb_func
Root2:
	PUSH {R4,R5,LR}
	VMOV R4,S0 //S0=a --> R4
	VMOV R5,S1 //S1=b --> R5
	BL Discriminant
	VMOV S1,R5
	VSQRT.F32 S0,S0 //sqrt(discriminant)
	VNEG.F32 S0,S0 //neg(sqrt(discriminant))
	VSUB.F32 S0,S0,S1 //-sqrt(discriminant)-b
	VMOV S1,R4
	VMOV S3,2.0
	VMUL.F32 S1,S3,S1 //2*a
	VDIV.F32 S0,S0,S1 //everything/2a
	POP {R4,R5,PC}
	
	.end