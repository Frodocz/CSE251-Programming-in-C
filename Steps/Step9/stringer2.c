#include <stdio.h>
#include <string.h>
#include <ctype.h> // char functions

/* 
 * Name : Zhang Chao
 * Program to experiment with strings
 */
  
int StringLength(char str[]);
void PrintLength(char str[]);
void Reverse(char str[]);
int NumberOfSpaces(char str[]);
int NumberOfAppearances(char str[], char ch);

int main() {
    char mySentence[80];
    int len;
    
    printf("Enter a sentence: ");
    fgets(mySentence, 80, stdin);
    len = strlen(mySentence);
    mySentence[len - 1] = '\0';
    printf("The entered sentence is: %s\n", mySentence);
    printf("The number of spaces is: %d\n", NumberOfSpaces(mySentence));
    char charToCheck = 'i';
    printf("The number of character %c appearance is: %d\n", charToCheck, NumberOfAppearances(mySentence, charToCheck));
    // NumberOfAppearances("I really like that I can do this", 'i') --> 4
   
    PrintLength(mySentence);

    Reverse(mySentence);
    printf("The reversed sentence is: %s\n", mySentence);
}

void PrintLength(char str[]) {
    printf("The string \"%s\" is %lu characters long\n", str, strlen(str));
}


int StringLength(char str[]) {
    int numChars = 0;
    
    while(str[numChars] != '\0') {
        numChars++;
    }
    
    return numChars;
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

int NumberOfSpaces(char str[]) {
    int numSpaces = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        // printf("Location %d: %c\n", i, str[i]);
        if(str[i] == ' ')
            numSpaces++;
    }
    return numSpaces;
}

int NumberOfAppearances(char str[], char ch) {
    int numAppearances = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        // printf("Location %d: %c\n", i, str[i]);
        if(toupper(str[i]) == toupper(ch))
            numAppearances++;
    }
    return numAppearances;
}