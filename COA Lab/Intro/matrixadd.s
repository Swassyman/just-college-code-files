.data
    nums1: .word 1 2 3 4 5
    n: .word 5
    nums2: .word 11 22 33 44 55
    space: .string " "
    
.text
    la a1 nums1
    lw a2 n
    la a3 nums2
    li x2 0
    
    loop:
        lw x1 0(a1)
        lw x2 0(a3)
        
        add x3 x1 x2
        
        mv a0 x3
        li a7 1
        ecall
        
        la a0 space
        li a7 4
        ecall
        
        addi a1 a1 4
        addi a3 a3 4
        addi a2 a2 -1
        bgt a2 x0 loop

    end:
        li a7 10
        ecall
    

        
