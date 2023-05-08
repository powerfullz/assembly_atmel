ldi r16, 0x56    ; Load high byte of the number into register r16
ldi r17, 0x78    ; Load low byte of the number into register r17
sts 0x408, r17   ; Store high byte at SRAM location 0x402
sts 0x409, r16   ; Store low byte at SRAM location 0x403

ldi r18, 0x12    ; Load high byte of the number into register r18
ldi r19, 0x34    ; Load low byte of the number into register r19
sts 0x402, r18   ; Store high byte at SRAM location 0x402
sts 0x403, r19   ; Store low byte at SRAM location 0x403
