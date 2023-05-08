ldi r16, 0x12    ; Load high byte of the number into register r16
ldi r17, 0x34    ; Load low byte of the number into register r17
sts 0x402, r16   ; Store high byte at SRAM location 0x402
sts 0x403, r17   ; Store low byte at SRAM location 0x403
