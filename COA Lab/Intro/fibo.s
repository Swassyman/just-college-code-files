.data
n: .word 4
nums: .word 10 12 14 16
str: .string "Sum: "
space: .string " "

.text
    lw a2 n
    la a3 nums
    
loop:
    lw x2 0(a3) 
    addi x1 x1 0
    add x1 x1 x2

    addi a3 a3 4
    addi a2 a2 -1
    bgt a2 x0 loop
    
    mv a0 x1
    li a7 1
    ecall