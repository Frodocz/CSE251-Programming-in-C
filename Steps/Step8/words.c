#include <stdio.h>
// #include <string.h>

/* 
 * Name : Zhang Chao
 * Program to experiment with character arrays
 */

#define MaxWord 20

void strCopy(char src[], char dest[], int sz) {
	for (int i = 0; i <= sz; ++i) {
		dest[i] = src[i];
	}
}
 
int main() {
    char c;
    char str[MaxWord + 1];
    int len = 0;
    int sum = 0, cnt = 0;
    int maxLen = 0;
    char maxStr[MaxWord + 1];
    puts ("Enter text. Include a dot ('.') to end a sentence to exit:");
    do {
        c = getchar();
        if (c != ' ' && c != '.' && c != '\n') {
        	/* This is a character of a word */
        	if (len < MaxWord) {
        		str[len] = c;
            	len++;
        	}
        } else {
        	/* The word is done */
        	if (len != 0) {
        		str[len] = 0;
            	sum += len;
            	cnt++;
            	// printf("%s, curSum = %d, curCnt = %d\n", str, sum, cnt);
            	printf("%s\n", str);

            	if (len > maxLen) {
            		maxLen = len;
            		strCopy(str, maxStr, len);
            		// strcpy(maxStr, str);
            	}
            	len = 0;
        	}
        }
    } while (c != '.');

    printf("The average length of %d words is %f.\n", cnt, (double)sum / cnt);
    printf("The longest word of length %d is %s\n", maxLen, maxStr);
}
