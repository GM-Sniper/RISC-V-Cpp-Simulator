addi x1, x0, 3
beq  x0, x0, loop
addi x1, x0, 4
loop:
beq x1, x0, end
addi x1, x1, -1
beq x0, x0, loop
end: