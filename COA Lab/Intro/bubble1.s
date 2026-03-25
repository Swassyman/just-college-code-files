.data
    n: .word 5
    nums: .word 5 4 3 2 1
    space: .string " "

.text
    lw a1 n          # Load n
    lw a2 n          # Load n
    addi a2 a2 -1    # n-1
    la a4 nums       # Address of nums array
    
    li x6 0          # i control
    outloop:
        bge x6 a1 end    # If i >= n, exit
        li x2 0          # j control
        la a3 nums       # Reset address of nums for each outer loop iteration
        
        inloop:
            bge x2 a2 outnext # If j >= n-1, exit inner loop
            lw x4 4(a3)      # Load arr[j+1]
            lw x3 0(a3)      # Load arr[j]
            bge x3 x4 swap   # If arr[j] <= arr[j+1], no swap needed
            jal innext       # Continue inner loop

        swap:
            sw x4 0(a3)      # Store arr[j+1] in arr[j]
            sw x3 4(a3)      # Store arr[j] in arr[j+1]

        innext:
            addi a3 a3 4     # Move to the next array position
            addi x2 x2 1     # Increment j
            j inloop         # Continue inner loop

    outnext:
        addi x6 x6 1     # Increment i
        j outloop        # Continue outer loop

    end:
        lw x5 n
        printloop:
            lw x7 0(a4)
            mv a0 x7
            li a7 1
            ecall
    
            la a0 space
            li a7 4
            ecall
        
            addi a4 a4 4 
            addi x5 x5 -1   
            bgt x5 x0 printloop

            li a7 10
            ecall
