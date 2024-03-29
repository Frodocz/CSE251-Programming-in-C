#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Name :  Zhang Chao
 * 
 * Simple Wumpus game in 2D
*/

/* Id's for things in our Cave */
#define Empty 0
#define Wumpus 1
#define End 2
#define Pit 3

/* Number of rooms in our Cave in each dimension */
#define CaveSize 10
#define ArraySize (CaveSize + 2)

/* Directions I can face */
#define Left 0
#define Up 1
#define Right 2
#define Down 3

void CreateWorld(int cave[ArraySize][ArraySize]);
int *GetEmptyRoom(int cave[ArraySize][ArraySize]);
void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir);
int DifferenceByDirection(int dir);
bool DisplayStatus(int cave[ArraySize][ArraySize], int *agent);

bool win = false;

void CreateWorld(int cave[ArraySize][ArraySize]) {
    for (int i = 0; i < ArraySize; i++) {
        for (int j = 0; j < ArraySize; j++) {
            if (i == 0 || j == 0 || i == ArraySize - 1 || j == ArraySize - 1) {
                cave[i][j] = End;
            } else {
                cave[i][j] = Empty;
            }
        }
    }

    int *room;
    room = GetEmptyRoom(cave);
    *room = Wumpus;

    for (int i = 0; i < 10; i++) {
        room = GetEmptyRoom(cave);
        *room = Pit;
    }
}

int *GetEmptyRoom(int cave[ArraySize][ArraySize]) {
    int row, col;
    int *room;
    
    do {
        /* We need a random number in each dimension */
        row = rand() % ArraySize;
        col = rand() % ArraySize;
        
        room = &cave[row][col];
    } while(*room != Empty);
    
    return room;
}

void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir) {
    int row, col;
    int *room;
    
    /* Loop over the rows of the cave */
    for (row = 1; row <= CaveSize + 1; row++) {
        /* 
         * This loop lets us print an up direction 
         * above the agent or a v below the agent
         */
        for (col = 1; col <= CaveSize; col++) {
            if (&cave[row][col] == agent && agentDir == Up) {
                printf(" ^  ");
            } else if (&cave[row - 1][col] == agent && agentDir == Down) {
                printf(" v  ");
            } else {
                printf("    ");
            }
        }

        printf("\n");
        if(row > CaveSize)
            break;

        /*
         * This loop prints the agent or the room contents
         */ 
        for (col = 1; col <= CaveSize; col++) {
            room = &cave[row][col];
            if(room == agent) {
                switch (agentDir) {
                    case Left: printf("<A  "); break;  
                    case Right: printf(" A> "); break;
                    default: printf(" A  "); break;
                }
                continue;
            }

            switch (*room) {
                case Wumpus: printf("-W- "); break;
                case Pit: printf(" X  "); break;
                default: printf(" .  "); break;    
            }
        }
        printf("\n");
    }


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
    switch (dir) {
        case Up:
            return -ArraySize;
            
        case Down:
            return ArraySize;
            
        case Left:
            return -1;
            
        case Right:
            return 1;
    }
}

bool DisplayStatus(int cave[ArraySize][ArraySize], int *agent) {
    /* We will return true to indicate we are dead or win! */
    if (win) {
        printf("Congratuations!!! You have successfully killed the Wumpus\n");
        return true;
    }

    if (*agent == Wumpus) {
        printf("You have been eaten by the Wumpus\n");
        return true;
    } 

    if (*agent == Pit) {
        printf("You fell into a pit\n");
        return true;
    }

    if (*(agent + 1) == Wumpus || *(agent - 1) == Wumpus || *(agent - ArraySize) == Wumpus || *(agent + ArraySize) == Wumpus) {
        printf("I smell a Wumpus\n");
    }

    if (*(agent + 1) == Pit || *(agent - 1) == Pit || *(agent - ArraySize) == Pit || *(agent + ArraySize) == Pit) {
        printf("I feel a draft\n");
    }

    return false;
}
 
int main() {
    int cave[ArraySize][ArraySize];
    int *agentRoom;
    int agentDirection;
    char command[20];
    
    /* Seed the random number generator */
    srand(time(NULL));

    CreateWorld(cave);

    agentRoom = GetEmptyRoom(cave);
    agentDirection = rand() % 4;

    /* The game loop */
    while (true) {
        if(DisplayStatus(cave, agentRoom))
            break;

        DisplayWorld(cave, agentRoom, agentDirection);

        /* Get the command */
        printf("Command: ");
        scanf("%20s", command);
        if (strcmp(command, "quit") == 0) {
            /* Exit, we are doing */
            break;
        } else if(strcmp(command, "move") == 0) {
            int direction = DifferenceByDirection(agentDirection);
            if(*(agentRoom + direction) != End)
                agentRoom += direction;
            else { // small improvement, notify the player to make a turn
                printf("Reaching the end of the cave. Let's make a turn and kill the Wumpus.\n");
            }
        } else if(strcmp(command, "turn") == 0) {
            agentDirection = (agentDirection + 1) % 4;
        } else if(strcmp(command, "fire") == 0) {
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