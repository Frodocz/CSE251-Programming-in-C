#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main() {
    /* Section 2 */
    /* double angle;
    int numSteps = 40;
    double maxAngle = M_PI * 2;
    double sinVal;
    int i;

    for (i = 0; i <= numSteps; i++) {
        angle = (double)i / (double)numSteps * maxAngle;
        sinVal = sin(angle);
        printf("%3d: %5.2f %6.3f ", i, angle, sinVal);
        int numSpaces = 30 + sinVal * 30;
        for (int j = 0; j < numSpaces; j++) {
            printf(" "); 
        }
        printf("*\n");
    } */

    /* Section 3 for submission */
    int numSteps;
    while (true) {
        printf("Input the number of steps: ");
        scanf("%d", &numSteps);
        if (numSteps > 2) break;
    }
    double angle;
    double maxAngle = M_PI * 2;
    double sinVal;
    bool increasing = true;
    for (int i = 0; i <= numSteps; i++) {
        angle = (double)i / (double)numSteps * maxAngle;
        sinVal = sin(angle);
        // printf("%3d: %5.2f %6.3f ", i, angle, sinVal);
        printf("%3d: %5.2f ", i, angle);
        int numSpaces = 30 + sinVal * 30;
        for (int j = 0; j < numSpaces; j++) {
            printf(" "); 
        }
        if (sinVal == 1.0 || sinVal == -1.0) {
            increasing = !increasing;
            printf("*\n");
        } else if (increasing) {
            printf("\\\n");
        } else {
            printf("/\n");
        }
    }
}