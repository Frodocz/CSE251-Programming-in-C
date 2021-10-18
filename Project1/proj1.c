/*
 * CSE 251 Project 1
 * By: Zhang Chao
 *
 * Complete the following table:
 ∗
 * a b n estimate
 * −1 1 1883 1.178979838
 * 0 10 2028 0.489888070
 * −1000 1000 18861 0.999796418
 * 10 15 1515 0.016860599
 * 0.1 0.2 138 0.096211811
 */

#include <stdio.h>
#include <math.h>

int main() {
	double a, b, estimate, delta, err;

	printf("Enter a value for a: ");
	scanf("%lf", &a);
	printf("Enter a value for b: ");
	scanf("%lf", &b);

	printf("Integral evaluation\n");
	int n = 10;
	estimate = 0;
	delta = (b - a) / n;
	for (int i = 1; i <= n; ++i) {
		double x = a + (i - 0.5) * delta;
		double sinc = (x == 0) ? 1 : sin(M_PI * x) / (M_PI * x);
		estimate += sinc * delta;
	}
	double prev = estimate;
	printf("%d: %.9f\n", n, prev);

	n = 11;
	while (n < 100000) {
		estimate = 0;
		delta = (b - a) / n;
		for (int i = 1; i <= n; ++i) {
			double x = a + (i - 0.5) * delta;
			double sinc = (x == 0) ? 1 : sin(M_PI * x) / (M_PI * x);
			estimate += sinc * delta;
		}
		err = (estimate > prev) ? (estimate - prev) : (prev - estimate);
		printf("%d: %.9f %e\n", n, estimate, err);
		if (err < 1e-10) break;
		prev = estimate;
		++n;
	}
	printf("The integral result is %.9f\n", estimate);
	return 0;
}