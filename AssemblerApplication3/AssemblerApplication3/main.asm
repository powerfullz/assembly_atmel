.EQU MYLOC = 0x200
LDI R16, 62
STS MYLOC, R16
LDI R31, 63
LDS R30, 0
TST R30
BRNE NEXT
LDI R30, 210
ADIW R31:R30, 55
STS MYLOC,R31

NEXT: JMP NEXT