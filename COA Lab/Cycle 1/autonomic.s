.data
num: .word 21
strtrue: .string "is an Autonomic Number"
strfalse: .string "is not an Autonomic Number"

.text
    lw x1 num # to loop num times
    lw x2 num # to check if sum is equal
    add x3 x2 x0 # to add digits
    li x5 10
    loop:
        div x4 x3 x5
        