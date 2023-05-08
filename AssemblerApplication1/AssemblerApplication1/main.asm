ldi r16, 0x12
ldi r17, 0x34
sts 0x402, r16
sts 0x403, r17
; Store a 16-bit number 0x5678 at SRAM location 0x408
ldi r16, 0x56
ldi r17, 0x78
sts 0x408, r16
sts 0x409, r17
; Sum the above two numbers and store the result in EEPROM starting location.
 