#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GarageLib.h"

/* 
 * Name : Zhang Chao
 * Program to simulate a garage door
 */

/* Our possible garage door states */
#define DoorClosed  1
#define DoorOpening 2
#define DoorOpen    3
#define DoorClosing 4

void StateDoorClosed(int *state);
void StateDoorOpening(int *state);
void StateDoorOpen(int *state);
void StateDoorClosing(int *state);

void StateDoorClosed(int *state) {
    if (WasButtonPressed()) {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}

void StateDoorOpening(int *state) {
    if (GetDoorPosition() >= (DoorHeight - DoorTolerance)) {
        SetMotorPower(0);
        *state = DoorOpen;
        /* Reset the timer */
        ResetTimer();
    } else if (WasButtonPressed()) {
        SetMotorPower(-1);
        *state = DoorClosing;
    }
}

void StateDoorOpen(int *state) {
    if ((WasButtonPressed() || GetTimer() > 10 ) && !IsBeamBroken()) {
        SetMotorPower(-1);
        *state = DoorClosing;
    }
}

void StateDoorClosing(int *state) {
    if (GetDoorPosition() < DoorTolerance) {
        SetMotorPower(0);
        *state = DoorClosed;
    } else if (WasButtonPressed() || IsBeamBroken()) {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}

int main() {
    int state = DoorClosed;

    printf("Garage Startup\n");
    GarageStartup();

    while(IsGarageRunning()) {
        switch (state) {
            case DoorClosed:
                StateDoorClosed(&state);
                break;
            case DoorOpening:
                StateDoorOpening(&state);
                break;
            case DoorOpen:
                StateDoorOpen(&state);
                break;
            case DoorClosing:
                StateDoorClosing(&state);
                break;
        }

    }

    printf("Garage Shutdown\n");
    GarageShutdown();
    return 0;
}

