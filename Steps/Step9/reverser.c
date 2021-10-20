#include <stdio.h>
#include <string.h>

/* 
 * Name : Zhang Chao
 * Program to experiment with files
 */

void Reverse(char str[]);

int main(int argc, char *argv[]) {
    if(argc < 4) {
        printf("Insufficient arguments\n");
        return 1;
    }
    
    // printf("%s\n", argv[0]); 
    
    printf("Copy from file: %s\n", argv[1]);
    printf("Copy to file: %s\n", argv[2]);
    printf("Write backwards to file: %s\n", argv[3]);

    FILE *inFile;
    FILE *outFile;
    char line[120];

    inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }

    outFile = fopen(argv[2], "w");
    if (outFile == NULL) {
        printf("Unable to open file %s\n", argv[2]);
        return 1;
    }

    /* While we are not at the end of the file */
    while (!feof(inFile)) {
        /* Read a line of text from the file */
        fgets(line, sizeof(line), inFile);

        /* Remove the new line at the end of the line */
        if (strlen(line) > 0)
            line[strlen(line) - 1] = '\0';

        Reverse(line);
        fprintf(outFile, "%s\n", line);
    }

    fclose(inFile);
    fclose(outFile);

    char out[] = "On a clear disk, you can seek forever"; 
    outFile = fopen(argv[3], "w");
    Reverse(out);
    fprintf(outFile, "%s\n", out);
    fclose(outFile);
}

void Reverse(char str[]) {
    int front = 0;       
    int back = strlen(str) - 1;  
    char t;             /* A temporary place to put a character */
    
    while (front < back) {
        t = str[front];
        str[front] = str[back];
        str[back] = t;
        front++;
        back--;
    }
}