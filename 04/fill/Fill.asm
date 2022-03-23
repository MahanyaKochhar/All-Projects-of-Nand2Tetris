// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(LOOP)
@KBD
D=A
@curr
M=D
A=M
D=M
@BLACKSCREEN
D;JNE
@WHITESCREEN
D;JEQ

(BLACKSCREEN)
@i
M=0
@SCREEN
D=A

@address
M=D

(LOOP2)

@i
D=M
@address
D=D+M
@curr
D=D-M
@END
D;JEQ

@i
D=M
@address
A=D+M
M=-1
@i
M=M+1
@LOOP2
0;JMP

(END)
@LOOP
0;JMP


(WHITESCREEN)
@i
M=0
@SCREEN
D=A

@address
M=D

(LOOP3)

@i
D=M
@address
D=D+M
@curr
D=D-M
@END
D;JEQ

@i
D=M
@address
A=D+M
M=0
@i
M=M+1
@LOOP3
0;JMP













