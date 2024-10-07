.data

n: .word 20
msg: .string "Fibonacci Series is " 
space: .string " "

.text
li x1,0
li x2,1
lw a2,n
la a0,msg
li a7,4
ecall

loop:
    mv a0,x1
    li a7,1
    ecall

    la a0,space
    li a7,4
    ecall

    add x3,x1,x2
    mv x1,x2
    mv x2,x3
    addi a2,a2,-1
    bne a2,x0,loop

end:
    nop