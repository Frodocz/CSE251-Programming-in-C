#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Name :  Zhang Chao
 * 
 * Simple Wumpus game in 1D
*/

/* Add any #defines here */
/* Id's for things in our Cave */
#define Empty 0
#define Wumpus 1
#define End 2

/* Number of rooms in our Cave */
#define CaveSize 20
#define ArraySize (CaveSize + 2) // rooms with two ends

/* Directions I can face */
#define Left 0
#define Right 1

/* Add any function prototypes here */
void CreateWorld(int cave[]);
int *GetEmptyRoom(int cave[]);
void DisplayWorld(int cave[], int *agent, int agentDir);
int DifferenceByDirection(int dir);
bool DisplayStatus(int cave[], int *agent);

bool win = false; // use the global variable to stop the game as soon as we win

void CreateWorld(int cave[]) {
    int *room;

    /* Set the ends */
    cave[0] = End;
    cave[ArraySize - 1] = End;

    /* Initialize cave to empty */
    for (int i = 1; i < ArraySize - 1; i++) {
        cave[i] = Empty;
    }

    /* Get a random empty room and put the Wumpus in it */
    room = GetEmptyRoom(cave);
    *room = Wumpus;
}

int *GetEmptyRoom(int cave[]) {
    int room;
    
    do {
        room = rand() % ArraySize;
    } while(cave[room] != Empty);
    
    return &cave[room];
}

void DisplayWorld(int cave[], int *agent, int agentDir) {
    int *room;
    
    for (room = cave + 1; *room != End; room++) {
        if (room == agent) {
            switch (agentDir) {
                case Left:
                    printf("<A  ");
                    break;
                    
                case Right:
                    printf(" A> ");
            }
            continue;
        }

        switch (*room) {
            case Wumpus:
                printf("-W- ");
                break;
            default:
                printf(" .  ");
                break;    
        }
    }
    printf("\n");
}

int DifferenceByDirection(int dir) {
    if (dir == Left)
        return -1;
    else
        return 1;
}

bool DisplayStatus(int cave[], int *agent) {
    /* We will return true to indicate we are dead or win! */
    if (win) {
        printf("Congratuations!!! You have successfully killed the Wumpus\n");
        return true;
    }

    if (*agent == Wumpus) {
        printf("You have been eaten by the Wumpus\n");
        return true;
    } 

    if (*(agent + 1) == Wumpus || *(agent - 1) == Wumpus) {
        printf("I smell a Wumpus\n");
    }

    return false;
}

int main() {
    int cave[ArraySize];
    int *agentRoom;
    int agentDirection;
    char command[20];

    /* Seed the random number generator */
    srand(time(NULL));
    
    CreateWorld(cave);

    agentRoom = GetEmptyRoom(cave);
    agentDirection = rand() % 2;

    /* The game loop */
    while (true) {
        if(DisplayStatus(cave, agentRoom))
            break;

        /* DisplayWorld(cave, agentRoom, agentDirection); */
        DisplayWorld(cave, agentRoom, agentDirection);

        /* Get the command */
        printf("Command: ");
        scanf("%20s", command);

        if (strcmp(command, "quit") == 0) {
            /* Exit, we are doing */
            break;
        } else if (strcmp(command, "move") == 0) {
            /* Move command */
            /* What way do we need to go? */
            int direction = DifferenceByDirection(agentDirection);
            if( *(agentRoom + direction) != End)
                agentRoom += direction;
            else { // small improvement, notify the player to make a turn
                printf("Reaching the end of the cave. Let's make a turn and kill the Wumpus.\n");
            }
        } else if (strcmp(command, "turn") == 0) {
            agentDirection = !agentDirection;
        } else if (strcmp(command, "fire") == 0) {
            /* Fire command */
            /* What way do we need to fire? */
            int direction = DifferenceByDirection(agentDirection);
            int *room = agentRoom;
            for (int i = 0; i < 3 && *room != End; i++) {
                room += direction;
                if (*room == Wumpus) {
                    /* Do something here */
                    *room = Empty;
                    win = true;
                    break;
                }
            }
        } else {
            printf("I don't know what you are talking about\n");
        }

    }
}