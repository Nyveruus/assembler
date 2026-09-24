// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed,
// the screen should be cleared.

@SCREEN
D=A
@address
M=D

(LOOP)
@KBD
D=M
@PRESSED
D;JGT

(NOTPRESSED)
@SCREEN
D=A
@address
M=D

@8192
D=A
@count
M=D

(NOTPRESSEDL)
@address
A=M
M=0
@address
M=M+1

@count
MD=M-1

@NOTPRESSEDL
D;JGT

@LOOP
0;JMP

(PRESSED)
@SCREEN
D=A
@address
M=D
@8192
D=A
@count
M=D

(PRESSEDL)
@address
A=M
M=-1
@address
M=M+1
@count
MD=M-1
@PRESSEDL
D;JGT

@LOOP
0;JMP
