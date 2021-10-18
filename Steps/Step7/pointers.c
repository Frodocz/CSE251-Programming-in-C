#include <stdio.h>

/* 
 * Name : Zhang Chao
 * Program to experiment with hexadecimal
 * and pointers
 */
 
int main()
{
    int a = 0;
    int b = 5;
    int c = 0x2251;
    
    printf("a = %4d: (in hex) 0x%04x\n", a, a);
    printf("b = %4d: (in hex) 0x%04x\n", b, b);
    printf("c = %4d: (in hex) 0x%04x\n", c, c);

    printf("%lx\n", (long int)&a);

    int *pA = &a;
    int *pB = &b;
    int *p;

    printf("a=%d, pA=%x, *pA=%d\n", a, (int)pA, *pA); // a=0, pA=e31b946c, *pA=0

    a = 47;
    printf("a=%d, pA=%x, *pA=%d\n", a, (int)pA, *pA); // a=47, pA=e31b946c, *pA=47
    *pA = 99;
    printf("a=%d, pA=%x, *pA=%d\n", a, (int)pA, *pA); // a=99, pA=e31b946c, *pA=99

    printf("Next experiment:\n");
    p = pA;
    *p = 22;
    p = pB;
    *p = 18;
    p = &b;
    *p = 108;
    p = pA;
    *p = 2;
    printf("a=%d, pA=%x, *pA=%d\n", a, (int)pA, *pA); // a=2, pA=e31b946c, *pA=2
    printf("b=%d, pB=%x, *pB=%d\n", b, (int)pB, *pB); // b=108, pB=e31b9468, *pB=108
    printf("p=%x, *p=%d\n", (int)p, *p); // p=e31b946c, *p=2
}