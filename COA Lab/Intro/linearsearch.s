.data
    n: .word 10
    nums: .word 10 15 17 29 32 98 12 65 34 81
    key: .word 98
    success: .string "Search Successful"
    fail: .string "Search Failed"

.text
    lw a1 n
    la a2 nums
    lw a3 key
    
    loop:
        lw x2 0(a2)
        beq x2 a3 searchsuccess
        addi a2 a2 4
        addi a1 a1 -1
        bgt a1 x0 loop
        beq a1 x0 searchfail
    
    searchsuccess:
        la a0 success
        li a7 4
        ecall
        j end
        
    searchfail:
        la a0 fail
        li a7 4
        ecall
        j end
        
    end:
        li a7 10
        ecall