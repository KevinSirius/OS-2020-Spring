.global sumto
sumto:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $8, %esp
        cmpl    $1, 8(%ebp)
        jg      .L2
        movl    $1, %eax
        jmp     .L3
.L2:
        movl    8(%ebp), %eax
        subl    $1, %eax
        subl    $12, %esp
        pushl   %eax
        call    sumto
        addl    $16, %esp
        movl    8(%ebp), %edx
        addl    %edx, %eax
.L3:
        leave
        ret