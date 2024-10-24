.data
    str: .string "Malayalam"
    
.text
    la a1 str
    
    loop:
        lb x1 0(a1)
        beq x1 x0 print
        
        addi a1 a1 1
        j loop
  
    print:
        addi a1 a1 -1
        lb x2 0(a1)
        
        mv a0 x2
        li a7 11
        ecall
          
        beq x2 x0 end
        j print
        

    end:
        li a7 10
        ecall
    