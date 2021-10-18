#include <stdio.h>
#include <math.h>

/*
 * Name : Zhang Chao
 * 
 * This is my first CSE 251 C program!!!
 */

int main() {
    double capacitance, inductance, frequency;
    printf("Input Capacitance (microfarads): ");
    scanf("%lf", &capacitance);
    printf("Input Inductance (millihenrys): ");
    scanf("%lf", &inductance);

    frequency = 1.0 / sqrt((inductance / 1000) * (capacitance / 1000000)) / (2 * M_PI);
    printf("Resonant Frequency is %.3f\n", frequency);
}