#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "transistors.h"

void DisplayTransistor(Tran tran) {
    printf("Number: %s\n", tran.number);
    switch (tran.type) {
        case NPN:
            printf("Type: NPN\n");
            break;
        
        case PNP:
            printf("Type: PNP\n");
            break;
    }

    switch (tran.caseStyle) {
        case TO18:
            printf("caseStyle: TO18\n");
            break;
        
        case TO92A:
            printf("caseStyle: TO92A\n");
            break;

        case TO92C:
            printf("caseStyle: TO92C\n");
            break;
        
        case TO220:
            printf("caseStyle: TO220\n");
            break;

        case TO39:
            printf("caseStyle: TO39\n");
            break;
    }
    
    printf("pMax: %.3f (mW)\n", tran.pmax);
    printf("icMax: %.3f (mA)\n", tran.icmax);
}

void InputString(char *str, int max) {
    char buffer[100];
    
    /* Get a line of up to 100 characters */
    fgets(buffer, sizeof(buffer), stdin);

    /* Remove any stray newlines from the buffer */
    while (buffer[0] == '\n')
        fgets(buffer, sizeof(buffer), stdin);
    
    /* Remove any \n we may have input */
    if (strlen(buffer) > 0)
        buffer[strlen(buffer) - 1] = '\0';
        
    /* Copy up to max characters to our string */
    strncpy(str, buffer, max);
    str[max - 1] = '\0';
}

char InputChar(char *prompt) {
    char buffer[100];
    char choice = 'a';

    do {
    	printf("%s", prompt);

    	/* Get a line of up to 100 characters */
    	fgets(buffer, sizeof(buffer), stdin);

    	/* Remove any \n we may have input */
    	if (strlen(buffer) > 0)
    		buffer[strlen(buffer) - 1] = '\0';

    	sscanf(buffer, "%c", &choice);
    } while (toupper(choice) != 'Y' && toupper(choice) != 'N');

    return toupper(choice);
}

int InputTransistorType(char *prompt) {
    char buffer[100];
    int type = 0;

    do {
    	printf("%s", prompt);

    	/* Get a line of up to 100 characters */
    	fgets(buffer, sizeof(buffer), stdin);

    	/* Remove any \n we may have input */
    	if (strlen(buffer) > 0)
    		buffer[strlen(buffer) - 1] = '\0';

    	sscanf(buffer, "%d", &type);
    } while (type != 1 && type != 2);

    return type;
}

int InputTransistorCaseStyle(char *prompt) {
    char buffer[100];
    int caseStyle = 0;

    do {
    	printf("%s", prompt);

    	/* Get a line of up to 100 characters */
    	fgets(buffer, sizeof(buffer), stdin);

    	/* Remove any \n we may have input */
    	if (strlen(buffer) > 0)
    		buffer[strlen(buffer) - 1] = '\0';

    	sscanf(buffer, "%d", &caseStyle);
    } while (caseStyle < 1 || caseStyle > 5);

    return caseStyle;
}

double InputPositiveValue(char *prompt) {
    char buffer[100];
    double value = 0;

    do {
    	printf("%s", prompt);

    	/* Get a line of up to 100 characters */
	    fgets(buffer, sizeof(buffer), stdin);
	    
	    /* Remove any \n we may have input */
	    if (strlen(buffer) > 0)
	        buffer[strlen(buffer) - 1] = '\0';
	        
	    sscanf(buffer, "%lf", &value);
    } while (value <= 0);
    
    return value;
}

Tran InputTransistor() {
    Tran t1;
    
    printf("Input number: ");
    InputString(t1.number, sizeof(t1.number));
    t1.type = InputTransistorType("Input type: ");
    t1.caseStyle = InputTransistorCaseStyle("Input caseStyle: ");
    
    t1.pmax = InputPositiveValue("Input pMax: ");
    t1.icmax = InputPositiveValue("Input icMax: ");

    return t1;
}