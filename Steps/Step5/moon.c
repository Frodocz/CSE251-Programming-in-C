#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 
 * Simple lunar lander program.
 * By:  Zhang Chao
 * Best landing: Time = 15 seconds, Fuel = 85.0, Velocity = -1.95
 */
 
int main() {
    printf("Lunar Lander - (c) 2021, by Zhang Chao\n");
    double altitude = 100;  /* Meters */
    double velocity = 0;    /* Meters per second */
    double fuel = 100;      /* Kilograms */
    double power = 1.5;     /* Acceleration per kilogram of fuel */
    double g = -1.63;       /* Moon gravity in m/s^2 */
    double burn;            /* Amount of fuel to burn */
    bool valid;             /* Valid data entry flag */
    int time = 0;           /* Record the time spent */
    
    while (altitude > 0) {
        printf("Altitude: %f\n", altitude);
        printf("Velocity: %f\n", velocity);
        printf("You have %f kilograms of fuel\n", fuel);

        do {
            valid = false;   /* Assume invalid until we know otherwise */
            printf("How much fuel would you like to burn: ");
            scanf("%lf", &burn);
            if (burn < 0) {
                printf("You can't burn negative fuel\n");
            } else if (burn > fuel) {
                printf("You can't burn fuel you don't have\n");
            } else if (burn > 5) {
                printf("You can't burn more than 5 kilograms per second\n");
            } else {
                printf("Burning %.1f kilograms of fuel\n", burn);
                valid = true;
            }
        } while (!valid);

        velocity = velocity + g + power * burn;
        altitude += velocity;
        fuel -= burn;
        time++;
    }
    printf("You landed with a velocity of %.2f m/s, time spent is %d seconds, the amount of fuel remaining is %.1f kilograms\n", velocity, time, fuel);
    
    if (fabs(velocity) > 3) {
        printf("Your next of kin have been notified\n");
    }
}