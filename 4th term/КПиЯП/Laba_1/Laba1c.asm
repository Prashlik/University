; LabWork #1 com
; Write a program that can output 
; a string of characters to the screen   

    .model tiny
    .code
    org 100h 
    
start:   
    mov ah, 9h
    mov dx, offset string
    int 21h
    ret
string db "Lab Work 1 com by Pavel Syakachev",0Dh,0Ah,'$'
end start