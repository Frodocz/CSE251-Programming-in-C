#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
	double annualIncome, standDecuction, totalDeduction, taxableIncome, tax;
	int filingStatus, numDependent, numChildren;
	printf("Enter your annual income: ");
	scanf("%lf", &annualIncome);
	if (annualIncome < 9350) {
		tax = 0;
		printf("%.2lf\n", tax);
		exit(1);
	}
	printf("What is your filing status?\n");
	printf("1) single\n");
	printf("2) married filing jointly\n");
	printf("3) married filing separately\n");
	printf("Please enter a number: ");
	scanf("%d", &filingStatus);
	switch (filingStatus) {
		case 1:
		case 3:
			numDependent = 1;
			standDecuction = 5700;
			break;
		case 2:
			printf("How many children do you have? ");
			scanf("%d", &numChildren);
			numDependent = 2 + numChildren;
			standDecuction = 11400;
			break;
		default:
			break;
	}

	totalDeduction = numDependent * 3650 + standDecuction;
	taxableIncome = annualIncome - totalDeduction;

	if (taxableIncome <= 16750) {
		tax = taxableIncome * 0.1;
	} else if (taxableIncome <= 68000) {
		tax = 1675 + (taxableIncome - 16750) * 0.15;
	} else if (taxableIncome <= 137300) {
		tax = 9362.5 + (taxableIncome - 68000) * 0.25;
	} else {
		tax = 26687.5 + (taxableIncome - 137300) * 0.28;
	}
	printf("%.2f\n", tax);
	return 0;
}