// movl $3, -12(%rbp) >>> 3
// movl $7, -8(%rbp) >>> 7
// movl -12(%rbp), %edx
// movl -8(%rbp), %eax
// addl %edx, %eax >>> + 
// movl %eax, -4(%rbp)
// movl -4(%rbp), %eax
// movl %eax, %esi
// leaq .LC0(%rip), %rdi
// movl $0, %eax
// call printf@PLT >>> printf
// movl $0, %eax

#include <stdio.h>
int main()
{
    int a = 3, b = 7;
    int c = a + b;
    printf("%d\n", c);
    return 0;
}