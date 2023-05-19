.include <m328pdef.inc>
; Store a 16-bit number 0x1234 at SRAM location 0x402
ldi r16, 0x12		; Store the high byte at r16
ldi r17, 0x34		; store the low byte at r17
sts 0x402, r16		; store high byte into 0x402
sts 0x403, r17		; store low byte into 0x403

; Store a 16-bit number 0x5678 at SRAM location 0x408
ldi r18, 0x56		; r18 = 0x56
ldi r19, 0x78		; r19 = 0x78
sts 0x408, r18		; store high byte into 0x408
sts 0x409, r19		; store low byte into 0x409

; Sum the above two numbers and store the result in EEPROM starting location.
add r16, r18	; Add high byte
adc r17, r19	; Add low byte with carry

storeHigh:
	sbic EECR, EEPE			; checks if EEPE is 0
	rjmp storeHigh			; if not, repeat check
	ldi r26, LOW(0x0000)	; X = 0x00
	ldi r27, HIGH(0x0000)	; X = 0x00
	out EEARH, XH			; EEAR high = 0x00
	out EEARL, XL			; set EEAR low = 0x00
	out EEDR, r16			; EEDR = 0x68
	sbi EECR, EEMPE; set EEMPE to 1
	sbi EECR, EEPE; set EEPE to 1

store_eeprom_low:
	sbic EECR, EEPE; checks if EEPE is 0
	rjmp store_eeprom_low; if not, repeat check
	ldi r26, LOW(0x0001); X low is 0x01
	ldi r27, HIGH(0x0001); X high is 0x00
	out EEARH, XH; set EEAR high to 0x00
	out EEARL, XL; set EEAR low to 0x01
	out EEDR, r17; set EEDR to 0xAC
	sbi EECR, EEMPE; set EEMPE to 1
	sbi EECR, EEPE; set EEPE to 1


; Store 10 16-bit numbers starting from 0x0910 at Program Memory location using the ASM code and store the sum of 10 numbers in 0x0200 SRAM location. Use X pointer to transverse the 10 numbers stored.

ldi r26, LOW(0x0500); set X low to 0x00
	ldi r27, HIGH(0x0500); set X high to 0x05
	ldi r30, LOW(0x0910); set Z low to 0x10
	ldi r31, HIGH(0x0910); set Z high to 0x09

;This loop moves numbers from the flash memory to the SRAM
	ldi r20, 10; loads 10 into r20
move_to_SRAM:
	lpm r17, Z+; loads the value at Z into num1 low and increments Z
	lpm r16, Z+; loads the value at Z into num1 high and increments Z
	st X+, r17; stores the value in num1 low at X and increments X
	st X+, r16; stores the value in num1 high at X and increments X
	dec r20; decrements r20
	brne move_to_SRAM; if r20!=0, repeat

;sets Z to 0x500
	ldi r30, LOW(0x500); set Z low to 0x00
	ldi r31, HIGH(0x500); set Z high to 0x05
;loads the first number from the SRAM into num1
	ld r17, Z+; load the value at Z into num1 low and increment Z
	ld r16, Z+; load the value at Z into num1 high and increment Z
;this loop loads subsequent numbers from the SRAM into num2, then adds it to num1
	ldi r20, 9; load 9 into r20
sum_numbers:
	ld r19, Z+; load the value at Z into num2 low and increment Z
	ld r18, Z+; load the value at Z into num2 high and increment Z
	add r17, r19; num1 low = num1 low + num2 low
	adc r16, r18; num1 high = num1 high + num2 high + carry from previous operation
	dec r20; decrements r20
	brne sum_numbers; if r20!=0, repeats

end:
	rjmp end; infinite loop

;Randomly generated 16 bit hexadecimal numbers (in pairs of 2 8 bit numbers)
.ORG 0x488; (half of 910)
NUMS: .DB 0x58, 0x4a, 0x61, 0x51, 0xfa, 0x58, 0xf, 0xb27, 0xda, 0x4d, 0xdb, 0x12, 0x75, 0x5a, 0xa4, 0xdd, 0x49, 0x96, 0x77, 0xa9