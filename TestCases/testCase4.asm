addi x1, x0, 10
addi x2, x0, 4
beq  x0, x0, loop
addi x1, x0, 4
loop:
blt x1, x2, end
addi x1, x1, -1
beq x0, x0, loop
end: