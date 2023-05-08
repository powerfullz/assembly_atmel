; Basic sum up
ldi r19,19	; r16 = 19
ldi r20,95	; r17 = 95
ldi r21,5	; r21 = 5
; r19 + r20 + r21
add r19,r20
add r19,r21

; Basic substract
sub r19, r25	; r19 - r25

; Some instructions
inc r19		; r19 + 1
dec r19		; r19 - 1

; SRAM Addressing
lds r22, 0x80	;r22 = [0x80]
sts 0x81, r22	; [0x81] = r22 = [0x80]
;Store 55 into [0x80]
ldi r23, 0x55
sts 0x80, r23

; Dataspace Addressing
in r1,0x3f	; r1 = SREG
in r2,0x3e	; r2 = SPH