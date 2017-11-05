   .data
x: .space 8
y: .space 4
   .text
...
   li   $v0, 5
   syscall
   sw   $v0, y
...
   lw   $t0, y
   addi $t0, $t0, 2000
   lw   $t1, y
   addi $t1, $t1, 3000
   mult $t0, $t1      # (Hi,Lo) = $t0 * $t1
   mfhi $t0
   sw   $t0, x        # top 32 bits of product
   mflo $t0
   sw   $t0, x+4      # bottom 32 bits of product


// long x;   // assume 8 bytes
// int  y;   // assume 4 bytes
// ...
// scanf("%d", &y);
// ...
// x = (y + 2000) * (y + 3000);