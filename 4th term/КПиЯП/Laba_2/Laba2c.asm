; LabWork #2 com
; Write a program that can reverse  
; a characters of the words in a string   

    .model tiny
    .code
    org 100h 
         
print macro out_str
    mov ah, 9h
    mov dx, offset out_str 
    int 21h
endm   
         
start:    
    print string
    ret
string db "Lab Work 1 com by Pavel Syakachev",0Dh,0Ah,'$'
end start