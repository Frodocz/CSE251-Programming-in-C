#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

/* Function declaration */
void PrintCard(int card, int suit);
void PrintResult(int card1, int suit1, int card2, int suit2);

/* 
 * Name : Zhang Chao
 * Program to draw playing cards
 */

int main() {
    int suit1, suit2;
    int card1, card2;
    
    /* 
     . This seeds the random number 
     . generator with the current time 
     */
    srand(time(NULL));
    
    /* Create a random card and suit */
    printf("Generateing card for Player 1\n");
    /* This will compute a random number from 0 to 3 */
    suit1 = rand() % 4;
    
    /* This will compute a random number from 1 to 13 */
    card1 = rand() % 13 + 1;
    printf("Player 1 gets ");
    PrintCard(card1, suit1);

    sleep(1);

    printf("Generateing card for Player 2\n");
    suit2 = rand() % 4;
    card2 = rand() % 13 + 1;
    
    printf("Player 2 gets ");
    PrintCard(card2, suit2);

    PrintResult(card1, suit1, card2, suit2);
}

void PrintCard(int card, int suit) {
    switch (card) {
    case 1:
        printf("Ace");
        break;
        
    case 11:
        printf("Jack");
        break;
        
    case 12:
        printf("Queen");
        break;
        
    case 13:
        printf("King");
        break;
        
    default:
        printf("%d", card);
        break;
    }
    
    printf(" of ");
    
    switch (suit) {
    case 0:
        printf("Hearts");
        break;
        
    case 1:
        printf("Diamonds");
        break;
        
    case 2:
        printf("Spades");
        break;
        
    case 3:
        printf("Clubs");
        break;
    }
    printf("\n");
}

void PrintResult(int card1, int suit1, int card2, int suit2) {
    if (card1 == card2) { // same card, compare suit
        if (suit1 > suit2) 
            printf("Player 1 wins\n");
        else if (suit1 < suit2)
            printf("Player 2 wins\n");
        else 
            printf("There is a tie\n");
    } else { // different card, compare card
        if (card1 == 1)
            printf("Player 1 wins\n");
        else if (card2 == 1)
            printf("Player 2 wins\n");
        else if (card1 < card2) 
            printf("Player 2 wins\n");
        else
            printf("Player 1 wins\n");
    } 
}

