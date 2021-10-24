#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ElevatorLib.h"

#define N 200

/* Our possible elevator states */
#define Idle        0
#define Moving      1
#define OpenDoor    2
#define ClosingDoor 3

// double calculateIntegralTerm(double errors[]);
void StateIdle();
void StateMoving();
void StateOpenDoor();
void StateClosingDoor(); 

/*
 * Name :        Zhang Chao
 * Description : Project 2 - The elevator controller
 */

/*
 * Name :        main()
 * Description : Program entry point.
 */

int state = Idle;     /* state is global since it is before main */
bool goingUp = true;  /* going up or going down */

int main() {
    
    double desiredSpeed = 1;
    double errors[N] = {0};
    double errorTotal = 0;
    int errorLoc = 0;
    int t = 0;
    double err = 0; // the error terms at t

    double Sup=0, Sdown=0, Smax=0;
    double numSup=0, numSdown=0;

    /*
     * This call starts the elevator system running
     */
    printf("Elevator Startup\n");
    ElevatorStartup();

    /*
     * This loop runs until we shut the elevator system down
     * by closing the window it runs in.
     */
    SetBrake(false);
    ChangeLoading();
    SetMotorPower(1);

    // PID Controller: Propotional, integral and differentrial (3 terms) --> P(t): Power power applied to motor, SetMotorPower(P(t)).
    while (IsElevatorRunning()) { // main loop runs 1000 times per second
        switch (state) {
            case Idle:
                StateIdle();
                break;
            case Moving:
                StateMoving();
                /* Compute new motor power here */
                // 1st section, propotional term = Kp * et;
                // 2nd section, integral term = Ki * Sum[for (i = 0 to N(200 which is(1/5 second))) e(t - i) * deltaT(0.001s)]
                double err = desiredSpeed - GetVelocity();
                errorLoc = (errorLoc + 1) % N;
                errorTotal = errorTotal - errors[errorLoc] + err;
                errors[errorLoc] = err;

                power = 0.45 * err + 0.54 * 0.001 * errorTotal;
                SetMotorPower(power);

                /* Averaging - get the average speed before the elevator starts slowing down */
                if (goingUp && GetPosition() < 1.5*FloorSpacing && GetPosition() > .5*FloorSpacing) {
                    Sup += GetVelocity();
                    numSup += 1;
                } else if (!goingUp && GetPosition() > .5*FloorSpacing && GetPosition() < 1.5*FloorSpacing) {
                    Sdown += GetVelocity();
                    numSdown += 1;
                }
                if (fabs(GetVelocity()) > fabs(Smax))
                    Smax = GetVelocity();
                break;
            case OpenDoor:
                StateOpenDoor();
                break;
            case ClosingDoor:
                StateClosingDoor();
                break;
        }
    } // End of the while(IsElevatorRunning()) loop

    Sup /= numSup;
    Sdown /= numSdown;
    printf("Average speed up: %lf\n", Sup);
    printf("Average speed down: %lf\n", Sdown);
    printf("Maximum speed: %lf\n", Smax);

    double maxAvgError = fmax(fabs(Sup-1), fabs(Sdown+1));
    double maxMaxError = fmax(fabs(Smax) - fabs(Sup), fabs(Smax) - fabs(Sdown));

    printf("Result: %lf\n", maxAvgError * maxMaxError);

    /*
     * This call shuts down the elevator system
     */
    printf("Elevator Shutdown\n");
    ElevatorShutdown();
    return 0;
}

// At state Idle, the elevator stops at a random level, door closed, waiting for a event happen for state transition
void StateIdle() {
    int gotoFloor; // target floor
    int currentFloor = GetNearestFloor();  // which floor we're at now

    gotoFloor = WhatFloorToGoTo(goingUp); // Event
    if (gotoFloor > 0) {
        // We need to go to the requesting floor
        printf("Request for floor %d\n", gotoFloor);
        state = Moving;
        printf("Transition:  from Idle to Moving.\n");
    }

    // Idle --> DoorOpen
    if (GetCallLight(currentFloor, true) || GetCallLight(currentFloor, false) ) {  // Event
        SetCallLight(currentFloor, true, false);
        SetCallLight(currentFloor, false, false);
        // Open door
        SetDoor(currentFloor, true);  // Transition
        state = OpenDoor;
        printf("Transition:  from Idle to OpenDoor.\n");
        return;
    }

    if (GetOpenDoorLight()) { // Event
        SetOpenDoorLight(false); // turn off
        SetDoor(currentFloor, true);  // Transition
        state = OpenDoor;
        printf("Transition:  from Idle to OpenDoor.\n");
        return;
    } 
    // Idle --> Idle
    else if (GetCloseDoorLight()) {  // close door
        SetCloseDoorLight(false); // turn off
        return;
    }
}

void StateMoving() {
    // Where are we going?
    int gotoFloor = WhatFloorToGoToInThisDirection(goingUp);

    // How far are we away from the floor we are going to?
    double distance = fabs(GetFloor() - gotoFloor);


    if (goingUp && GetPosition() > 2 * FloorSpacing + FloorTolerance) {
        /* We are above the third floor. Reverse direction */
        goingUp = false;
        /* SetMotorPower(-1); this should be removed */
        ChangeLoading();
        desiredSpeed = -1;
        SetBrake(true);
        if (GetCallLight(3, true)) {
            /* Button has been pressed */
            SetCallLight(3, false, true);   
        }
    }

    if (GetPosition() < 0.5 * FloorSpacing && !goingUp) {
        /* We are below the first floor. Reverse direction */
        goingUp = true;
        /* SetMotorPower(1); this should be removed */
        ChangeLoading();
        desiredSpeed = 1;
        SetBrake(true);
        /* Turn off the fisrt floor up call light */
        if (GetCallLight(1, true)) {
            /* Button has been pressed */
            SetCallLight(1, true, false);   
        }
    }
}

// when door is open
void StateOpenDoor() {
    int floor = GetNearestFloor();  // get current floor

    // When opening door, press the open door light, close door when close door button is pressed
    if (GetCloseDoorLight()) {  // event triggered
        SetCloseDoorLight(false); // turn off close door light
        SetDoor(floor, false);  // Trasition
        state = ClosingDoor;
        printf("Transition:  from OpenDoor to ClosingDoor.\n");
        return;
    }

    // When opening door, press the open door light, turn off the open door light
    if (GetOpenDoorLight()) {
        SetOpenDoorLight(false); // turn off open door light
        printf("Door is already open.\n");
        return;
    }

    // When door open successfully, close the door and switch the state to ClosingDoor
    if (IsDoorOpen(floor))  // Event, after 3s, close door
    {
        // close door
        SetDoor(floor, false); // Transition
        state = ClosingDoor;
        printf("Transition:  from OpenDoor to ClosingDoor.\n");
    } 
}

// when door is closing
void StateClosingDoor() {
    int floor = GetNearestFloor();  // current floor

    // Open the door suppose some item detected, currently not available in the library

    // When door is closing, press the open door light, open door
    if (GetOpenDoorLight()) {   // Event
        SetOpenDoorLight(false); // turn off open door light
        SetDoor(floor, true);  // Trasition
        state = OpenDoor;
        printf("Transition:  from ClosingDoor to OpenDoor.\n");
        return;
    }

    // When door is closing, press the close door light, turn off the close door light and return
    if (GetCloseDoorLight()) {  
        SetCloseDoorLight(false); // turn off close door light
        printf("Door is closing.\n");
        return;
    }

    // Door closed, set state to Idle and wait for next command
    if (IsDoorClosed(floor)) { // Event
        state = Idle;  // Transition
        printf("Transition:  from ClosingDoor to Idle.\n");
    } 
}
