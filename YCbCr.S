
	.equ y1, 77
	.equ y2, 150
	.equ y3, 29
	.equ cb1, -43
	.equ cb2, -85
	.equ cb3, 128
	.equ cr1, 128
	.equ cr2, -107
	.equ cr3, -21
	

@void RGB2YCbCr(unsigned char x[64], usigned char g[64],
@	unsigned char b[64], char y[64], char cb[64], char cr[64])
@r3 	y*
@sp		cb*
@sp+4	cr*
	.text
.global RGB2YCbCr
RGB2YCbCr:
			stmfd sp!, {r4,r5,r6,r7,r8,r9,r10,r11,lr}
			ldr r4,[sp,#36]
			ldr r5,[sp,#40]


			mov r6, #0
			sub sp, sp, #4
loop:
			cmp r6, #64
			beq exit
			str r6, [sp]

			ldrb r7,[r0],#1
			ldrb r8,[r1],#1
			ldrb r9,[r2],#1

	@y[i] = ((77*_r+150*_g+29*_b)>>8)-128;
			ldr r10, =y1
			mul r6, r10, r7
			mov r11, r6

			ldr r10, =y2
			mla r11, r10, r8, r6


			ldr r10, =y3
			mla r6, r10, r9, r11

			ldr r10, =-128
			add r6, r10, r6, asr #8
			strb r6,[r3]

	@cb[i] = ((-43*_r-85*_g+128*_b)>>8);
			ldr r10, =cb1
			mul r6, r10, r7


			ldr r10, =cb2
			mla r11, r10, r8, r6


			ldr r10, =cb3
			mla r6, r10, r9, r11

			mov r6, r6, asr #8
			strb r6, [r4]

	@cr[i] = ((128*_r-107*_g-21*_b)>>8);
			ldr r10, =cr1
			mul r6, r10, r7


			ldr r10, =cr2
			mla r11, r10, r8, r6


			ldr r10, =cr3
			mla r6, r10, r9, r11

			mov r6, r6, asr #8
			strb r6, [r5]


			ldr r6, [sp]
			add r6, r6, #1
			b loop

exit:
		add sp, sp, #4
		ldmfd sp!, {r4,r5,r6,r7,r8,r9,r10,r11,pc}

