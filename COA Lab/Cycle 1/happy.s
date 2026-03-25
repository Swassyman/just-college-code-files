.data
num: .word 17
strsuccess: .string " is a Happy Number"
strfail: .string " is Not a Happy Number"

.text
    lw x7 num
    li x2 10
    li x8 1
    li x9 9
loop:
    add x1 x7 x0  #store num in x1
    sub x7 x7 x7 #clear x7
  
    split:
        div x3 x1 x2 #x3 = x1/10
        mul x4 x2 x3 #x4 = x3*10
        sub x5 x1 x4 #x5 = x4 - x3 gives last digit
        
        mul x6 x5 x5
        add x7 x7 x6
        
        div x1 x4 x2 
        bgt x1 x0 split #check if number > 0
     
    bgt x7 x9 loop #check if the number is two digit
    
    #printing the number
    lw a0 num
    li a7 1
    ecall
    
    beq x7 x8 success
    bne x7 x8 fail
        
success:
    la a0 strsuccess
    li a7 4
    ecall
    jal end
    
fail:
    la a0 strfail
    li a7 4
    ecall
end:
    nop