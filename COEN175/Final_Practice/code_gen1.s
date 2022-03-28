f:
    pushl   %ebp
    movl    %esp, %ebp
    subl    $8, %esp

    movl    a, %eax
    imull   b, %eax
    movl    %eax, -8(%ebp)

    movl    a, %eax
    cltd
    idivl   b
    movl    %edx, -4(%ebp)

    pushl   -8(%ebp)
    pushl   -4(%ebp)
    call    g
    addl    $8, %esp

    movl    %ebp, %esp
    popl    %ebp
    ret