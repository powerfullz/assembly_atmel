LDI R16, 4
LDI XL, 0x30
LDI XH, 0x1
LDI YL, 0X50
LDI YH, 0x1
LDI ZL, 0x60
LDI ZH, 0x1

CLC

L1: 
LD R18, X+
LD R19, Y+
ADC R18, R19
ST Z+, R18
DEC R16
BRNE L1

END: JMP END

.DSEG
0x130 0x32 0x32 0x34 0x33 0x21
0x150 0x45 0x37 0x38 0x23 0x45
0x160