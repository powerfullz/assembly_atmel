.include "m328pdef.inc"

.equ    SRAM_START = 0x100
.equ    EEPROM_START = 0x400

.cseg
.org    0x0000
    rjmp    RESET   ; Reset handler

.org    0x001C
    rjmp    INT0_vect   ; External Interrupt Request 0

.org    SRAM_START + 2
    .dw     0x1234      ; Store a 16-bit number 0x1234 at SRAM location 0x402

.org    SRAM_START + 8
    .dw     0x5678      ; Store a 16-bit number 0x5678 at SRAM location 0x408

.org    EEPROM_START
    .dw     0           ; Sum of the above two numbers and store the result in EEPROM starting location.

.org    SRAM_START + 512
sum:
    .dw     10          ; Store 10 16-bit numbers starting from 0x0910 (at Program Memory location using the ASM code and store the sum of 10 numbers in 0x0200 SRAM location. Use X pointer to transverse the 10 numbers stored.
    
RESET:
    ldi     r16, hi8(RAMEND)
    out     SPH, r16
    ldi     r16, lo8(RAMEND)
    out     SPL, r16

main:
    ldi     ZH, hi8(sum)
    ldi     ZL, lo8(sum)
    
    ldi     r18, hi8(SRAM_START + 512)
    ldi     r19, lo8(SRAM_START + 512)
    
sum_loop:
    ld      r20, Z+
    ld      r21, Z+
    
    add     r18, r20
    adc     r19, r21
    
    cpi     r22, lo8(10*2)
    brne    sum_loop
    
sum_done:
    st      X+, r18
    st      X+, r19
    
end: