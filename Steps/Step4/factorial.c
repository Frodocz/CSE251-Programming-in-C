#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main() {
	int f;      /* Number we compute the factorial of */
    int fac = 1;    /* Initial value of factorial */
    bool running = true;
    while (running) {
        printf("Number to compute the factorial of: ");
        scanf("%d", &f);
        if (f < 0) break;
        int original = f;
        while (f > 0) {
            fac = fac * f;
            f--;
        }
        printf("%d! = %d\n", original, fac);
    }
}