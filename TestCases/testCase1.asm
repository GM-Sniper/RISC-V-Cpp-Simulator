addi x2, x0, 1
jal ra, add1 
addi x3, x0, 3
ecall
add1:
addi a0, x0, 5
jalr x0, 0(ra)
