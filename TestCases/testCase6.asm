addi a0, zero, 70
addi a1, zero, 28
jal ra, gcd

ecall

gcd:
beq a0, a1, exit
blt a1, a0, L1
sub a1, a1, a0
beq zero, zero, gcd
L1:
sub a0, a0, a1
beq zero, zero, gcd
exit:
jalr zero, 0(ra)