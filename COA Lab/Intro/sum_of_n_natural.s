.data
n: .word 5
str: .string "Sum: "

.text
    lw a2 n
    li x1 0
    li x2 0
loop:
    addi x1 x1 1
    add x2 x1 x2

    addi a2 a2 -1
    bgt a2 x0 loop

    la a0 str
    li a7 4
    ecall
    mv a0 x2
    li a7 1
    ecall
end:
    nop