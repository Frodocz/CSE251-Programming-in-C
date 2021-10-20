#include <stdio.h>
#include <string.h>

/* 
 * Name : Zhang Chao
 * Program to experiment with strings
 */
 
int StringLength(char str[]);
void PrintLength(char str[]);
void GetValidStartOfStdin();

int main() {
    char word[] = "chudge";
    char myWord[80];
    char mySentence[80];
    int i;
    int len;
    
    printf("Enter a word: ");
    scanf("%79s", myWord);
    len = strlen(mySentence);
    mySentence[len - 1] = '\0';
    myWord[79] = '\0';
    printf("The entered word is: %s\n", myWord);

    // fflush(stdin); // there's cache in the stdin not flushed
    GetValidStartOfStdin();

    printf("Enter a sentence: ");
    fgets(mySentence, 80, stdin);
    len = strlen(mySentence);
    mySentence[len - 1] = '\0';
    printf("The entered sentence is: %s\n", mySentence);
    
    PrintLength(word);
    PrintLength(myWord);
    PrintLength(mySentence);
}

int StringLength(char str[]) {
    int numChars = 0;
    while (str[numChars] != '\0') {
        numChars++;
    }
    return numChars;
}

void PrintLength(char str[]) {
    printf("The string \"%s\" is %lu characters long\n", str, strlen(str));
}

void GetValidStartOfStdin() {
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}