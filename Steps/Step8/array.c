#include <stdio.h>

/* 
 * Name : Zhang Chao
 * Program to experiment with arrays
 */

#define NumMovies 10
#define MaxGrosses 5
 
int main() {
    double gross[NumMovies] = {4633070, 3856195, 3171189, 1877685, 3251622,
                               3156594, 1629735, 2659234, 2028036, 510768};

    char *names[NumMovies] = {"Hall Pass", "Unknown", "I Am Number Four", "The King's Speech", 
                         "Just Go With It", "Gnomeo and Juliet", "Drive Angry", 
                         "Justin Beiber: Never Say Never", "Big Mommas: Like Father, Like Son", 
                         "True Grit"};

    double maxGross[MaxGrosses] = {500000, 1000000, 2000000, 4000000, 10000000};
    int maxGrossIdx[MaxGrosses] = {-1, -1, -1, -1, -1}; // [<500k, 500k-1m, 1m-2m, 2m-4m, 4m-10m]

    double sum;
    int highestGrossIndex = 0;
    double highestGross = 0;

    sum = 0;        /* Initialize to zero */
    highestGross = 0;
    for (int i = 0; i < NumMovies; i++) {
        if (gross[i] > highestGross) {
            highestGrossIndex = i;
            highestGross = gross[highestGrossIndex];
        }

        printf("Movie %2d %33s: %.0f\n", i+1, names[i], gross[i]);
        sum += gross[i];

        if (gross[i] < 500000) {
            if (maxGrossIdx[0] == -1 || gross[i] > gross[maxGrossIdx[0]]) {
                maxGrossIdx[0] = i;
            }
        } else if (gross[i] < 1000000) {
            if (maxGrossIdx[1] == -1 || gross[i] > gross[maxGrossIdx[1]]) {
                maxGrossIdx[1] = i;
            }
        } else if (gross[i] < 2000000) {
            if (maxGrossIdx[2] == -1 || gross[i] > gross[maxGrossIdx[2]]) {
                maxGrossIdx[2] = i;
            }
        } else if (gross[i] < 4000000) {
            if (maxGrossIdx[3] == -1 || gross[i] > gross[maxGrossIdx[3]]) {
                maxGrossIdx[3] = i;
            }
        } else if (gross[i] < 10000000) {
            if (maxGrossIdx[4] == -1 || gross[i] > gross[maxGrossIdx[4]]) {
                maxGrossIdx[4] = i;
            }
        } else { // >= 10000000
            // if (maxGrossIdx[5] == -1 || gross[i] > gross[maxGrossIdx[5]]) {
            //     maxGrossIdx[5] = i;
            // }
        }
    }
    printf("Total gross for these films was $%.0f\n", sum);
    printf("The highest grossing film is: %s\n", names[highestGrossIndex]);

    for (int i = 0; i < MaxGrosses; i++) {
        if (maxGrossIdx[i] == -1) {
            printf("No film made less than %.0f\n", maxGross[i]);
        } else {
            printf("The highest gross less than %.0f is %.0f at %s\n", maxGross[i], gross[maxGrossIdx[i]], names[maxGrossIdx[i]]);
        }
    }
}