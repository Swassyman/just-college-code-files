.data
str: .string "EducAtIon"
vows: .string "aeiouAEIOU"
output: .string "Number of vowels: "
.text
la a1 str
la a2 vows
li x3 0 #count variable
loop:
    lb x1 0(a1) #load each character in str
    la a2 vows #load vows
    beq x1 x0 print #check is str is terminated
    innerloop:
        lb x2 0(a2) #load each character in vows
        
        beq x2 x0 nextouter #continue if vow is terminated
        beq x1 x2 increment #check 
        j nextinner #skip increment
        
        increment:
            addi x3 x3 1 #increment
            j nextouter #skip rest of inner loop
    
    nextinner:
        addi a2 a2 1 #go to next character in vow
        bne x2 x0 innerloop
nextouter:    
    addi a1 a1 1 #go to next character in st
    bne x1 x0 loop   

print:
    la a0 output
    li a7 4
    ecall
    
    mv a0 x3
    li a7 1
    ecall

end: 
    nop