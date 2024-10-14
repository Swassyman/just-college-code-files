.data
    msg: .string "Prime numbers: "
    noprime: .string "Not a Prime Number"
    prime: .string "Prime Number"
    num: .word 21
    space: .string " "
    
.text
    lw a1 num
    li x1 1 #iterating control
    li x2 0 #number of divisors
    li x5 1 #needed number of divisors
    loop:
        div x3 a1 x1
        mul x3 x3 x1 
        sub x4 a1 x3
        
        beq x4 x0 increment
        j next
 
increment:
    addi x2 x2 1 # i++

next:
    addi x1 x1 1 
        
    blt x1 a1 loop
    beq x2 x5 success
    bgt x2 x5 fail
    
success:
    la a0 prime
    li a7 4
    ecall
    jal end

fail:
    la a0 noprime
    li a7 4
    ecall
    
end:
    nop