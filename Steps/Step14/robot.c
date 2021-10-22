#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "RobotLib.h"

void OnMachineRequest(int machine);

/*
 * Name :        Zhang Chao
 * Description : Robot scheduler program
 */

struct Request {
    int machine;
    struct Request *next;
};

struct Request *firstInLine = NULL;
struct Request *lastInLine = NULL;

/*
 * Name :        main()
 * Description : Program entry point.
 */
int main() {
    int request = 0;
    /*
     * This call starts the system running
     */
    printf("Robot System Startup\n");
    SimulatorStartup();

    SetMachineRequestHandler(OnMachineRequest);

    /*
     * This loop runs until we shut the simulator down
     * by closing the window it runs in.
     */
    bool hasStopped = false;
    while (IsSimulatorRunning()) {
        if (!IsRobotBusy()) {
            if (firstInLine != NULL) {
                RobotGoTo(firstInLine->machine);
                /* Remove the first item from the queue */
                struct Request *wasFirst = firstInLine;
                firstInLine = firstInLine->next;

                free(wasFirst);
            } else { /* Handle an empty queue */
                if (!hasStopped) {
                    hasStopped = true;
                    lastInLine = NULL;
                    ResetTimer();
                } else {
                    if (GetTimer() > 3) {
                        RobotGoTo(0);
                        hasStopped = false;
                    }
                }
            }
        }
    }

    /*
     * This call shuts down the elevator system
     */
    printf("Robot System Shutdown\n");
    SimulatorShutdown();
    return 0;
}

void OnMachineRequest(int machine) {
    printf("Robot request from machine %d\n", machine);
    struct Request *newRequest = malloc(sizeof(struct Request));
    newRequest->machine = machine;
    
    if (lastInLine != NULL) {
        /* This is the new last in the line */
        lastInLine->next = newRequest;
    } else {
        /* The queue is empty, make this the first request */
        firstInLine = newRequest;
    }
    lastInLine = newRequest;
    newRequest->next = NULL;
    printf("There are %d pending requests\n", CountRequests());
}

int CountRequests() {
    int cnt = 0;
    struct Request *request = firstInLine;
    while (request != NULL) {
        cnt++;
        request = request->next;
    }
    
    return cnt;
}

