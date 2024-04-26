addi x12, zero, 0
addi x11, zero, 3
addi x10, zero, 2
LOOP:
slti x13, x12, 20
beq x13, zero, END
add x10, x10, x11
addi x12, x12, 1
beq x0, x0, LOOP
END:
addi x20, zero, 900