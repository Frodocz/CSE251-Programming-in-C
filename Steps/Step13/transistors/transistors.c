#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "transistors.h"

/*
 * Name :  Zhang Chao
 * Description : Simple transistor description example program
*/

int main() {
    int i;
    Tran *trans;
    int numTrans = 0;
    char addOne;
    
    printf("transistors!\n");

    /* Allocate space for one transistor */
    trans = malloc(sizeof(Tran));
    numTrans = 1;
    
    /* Input the transistor */
    trans[0] = InputTransistor();

    while (true) {
        addOne = InputChar("Would you like to enter another transistor (Y/N)? ");
        if (addOne == 'Y') { // already converted to upper case
            /* Increase the space by one transistor */
            trans = realloc(trans, sizeof(Tran) * (numTrans + 1));
            trans[numTrans++] = InputTransistor();
        } else { // only 'Y' and 'N' will be returned
            /* Output the transistors */
            printf("\nThe transistors:\n");
            for (i = 0; i < numTrans; i++) {
                DisplayTransistor(trans[i]);
            }
            break;
        }
    }
    
    /* Free the memory */
    free(trans);
}