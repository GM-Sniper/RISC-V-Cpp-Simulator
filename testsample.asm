# Sample assembly code

# Load immediate values into registers
lui x1, 100
addi x2, x1, 50

# Perform arithmetic operations
add x3, x1, x2
sub x4, x3, x2

# Store the result in memory
sw x4, 0(x2)

# Jump and link to a label
jal x5, loop

# Loop label
loop:
    addi x6, x6, 1
    bne x6, x3, loop
