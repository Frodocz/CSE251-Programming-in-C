#include <stdio.h>
#include <math.h>

/*
 * Name : Zhang Chao
 * 
 * This is my first CSE 251 C program!!!
 */

int main() {
    double capacitance, inductance, frequency, omega;
    printf("Input Capacitance (microfarads): ");
    scanf("%lf", &capacitance);
    /* Test to see if the user entered an invalid value */    
    if(capacitance < 0)
        printf("You moron, you entered a negative inductance!\n");
    else
        printf("Okay, I guess that's reasonable\n");
    printf("Input Inductance (millihenrys): ");
    scanf("%lf", &inductance);
    if(inductance < 0)
        printf("You moron, you entered a negative inductance!\n");
    else
        printf("Okay, I guess that's reasonable\n");

    omega = 1.0 / sqrt((inductance / 1000) * (capacitance / 1000000));
    frequency = omega / (2 * M_PI);
    printf("Resonant Frequency is %.3f\n", frequency);
}