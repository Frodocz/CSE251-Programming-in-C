#include <stdio.h>
#include <math.h>

/*
 * Name : Zhang Chao
 * 
 * This is my first CSE 251 C program!!!
 */


int main() {
	printf("My first C program\n");
	printf("Aren't you impressed?\n");

	double radius = 7.88;
    double height = 12.231;

	printf("The cylinder has a radius of %+5.2f and a height of %+8.3f\n", radius, height);

	int wins = 11, losses = 2;
	printf("MSU had an %d-%d season in 2010!\n", wins, losses);

	double volume, diameter, hypot;
    int games;

    volume = radius * radius * M_PI * height;
    printf("Volume = %f\n", volume);

    games = wins + losses;
    printf("Games = %d\n", games);

    double near = 10;
    double far = 22.5;

    hypot = sqrt(near * near + far * far);

    double bottleVolume = 1700;  /* Milliliters */
    double cupVolume = 350;      /* Milliliters */
    int numCups;

    numCups = (int)(bottleVolume / cupVolume);
    printf("Number of cups: %d\n", numCups);
	return 0;
}