#include <stdio.h>
#include <string.h>

#include "io.h"

void inputString(char *str, int max) {
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

time_t inputDate(char *prompt) {
    char buffer[100];
    char *result;
    struct tm date;

    do {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if(strlen(buffer) > 0)
            buffer[strlen(buffer)-1] = '\0';

        result = strptime(buffer, "%m/%d/%Y", &date);

    } while (result == NULL);

    /* Convert to time_t format */
    date.tm_min = 0;
    date.tm_hour = 0;
    date.tm_sec = 0;
    date.tm_isdst = 1;

    return mktime(&date);
}

time_t inputTime(char *prompt, time_t date) {
    char buffer[100];
    char *result;
    struct tm time;

    time = *localtime(&date);

    do {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if(strlen(buffer) > 0)
            buffer[strlen(buffer)-1] = '\0';

        result = strptime(buffer, "%I:%M%p", &time);

    } while(result == NULL);

    return mktime(&time);
}

int inputInt(char *prompt) {
    char buffer[100];
    int option = -1;

    do {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);
        
        /* Remove any \n we may have input */
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';
            
        sscanf(buffer, "%d", &option);
    } while (option < 0 || option > 4);
    
    return option;
}
