.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    # return 3
    movl $3, %eax
    leave
    ret
