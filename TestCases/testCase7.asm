
addi s0, zero, 100 
addi s1, zero, 5 
jal ra, Sum
ecall
Sum:
addi s2, zero, 0
addi t0, zero, 0
Loop:
bge t0, s1, break
lw t2, 0(s0)
addi s0, s0, 4
add s2, s2, t2
addi t0, t0, 1
jal ra, Loop
break:
add x1, zero, s2
ecall