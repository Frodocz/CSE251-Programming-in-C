#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ElevatorLib.h"

/*
 * Name :        Zhang Chao
 * Description : Project 2 - The elevator controller
 */

/*
 * Name :        main()
 * Description : Program entry point.
 */

#define N 200

/* Our possible elevator states */
#define Idle        0
#define Moving      1
#define OpenDoor    2
#define ClosingDoor 3

void StateIdle();
void StateMoving();
void StateOpenDoor();
void StateClosingDoor();

int state = Idle;     /* state is global since it is before main */
bool goingUp = true;  /* going up or going down */
bool isTimerSet = false; /* record whether the timer is set or not */
double desiredSpeed = 1; /* record the desired speed of the elevator car */

// PID Controller
const double Kp = 0.45;
const double Ki = 0.55;
const double Dt = 0.001;
double errors[N] = {0};
double errorTotal = 0;
int errorLoc = 0;
double err = 0; // the error terms at time t

int main() {
    /*
     * This call starts the elevator system running
     */
    printf("Elevator Startup\n");
    ElevatorStartup();

    double Sup=0, Sdown=0, Smax=0;
    double numSup=0, numSdown=0;

    /*
     * This loop runs until we shut the elevator system down
     * by closing the window it runs in.
     */
    while (IsElevatorRunning()) { // main loop runs 1000 times per second
        switch(state) {
            case Idle:
                StateIdle();
                break;
            case Moving:
                StateMoving();
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

    gotoFloor = WhatFloorToGoTo(goingUp); // Event, get the target floor
    if (gotoFloor > 0) {
        // We need to go to the requesting floor
        printf("Request for floor %d\n", gotoFloor);
        if ((gotoFloor < currentFloor && goingUp) || (gotoFloor > currentFloor && !goingUp)) {
            goingUp = !goingUp; // change the moving direction
        }
    }

    // Idle --> OpenDoor (Check the Call Buttons outside the elevator)
    if (goingUp && GetCallLight(currentFloor, true)) { // moving up
        SetCallLight(currentFloor, true, false); // turn off the up call light
        SetDoor(currentFloor, true); // open the door
        state = OpenDoor;
        printf("Transition: from Idle to OpenDoor.\n");
        return;
    }
    if (!goingUp && GetCallLight(currentFloor, false)) { // moving down
        SetCallLight(currentFloor, false, false); // turn off the Down Call light
        SetDoor(currentFloor, true); // open the door
        state = OpenDoor;
        printf("Transition: from Idle to OpenDoor.\n");
        return;
    }

    // Idle --> OpenDoor (Check the Panel buttons inside the elevator)
    if (GetOpenDoorLight()) { // open the door event triggered
        SetOpenDoorLight(false); // turn off light
        SetDoor(currentFloor, true); // open the door
        state = OpenDoor;
        printf("Transition: from Idle to OpenDoor.\n");
        return;
    } else if (GetCloseDoorLight()) {  // close door
        SetCloseDoorLight(false); // turn off the close door light, in Idle state door must be closed
        return;
    }

    // Idle --> Moving
    if (gotoFloor > 0) {
        if (goingUp) {
            SetCallLight(currentFloor, true, false); // turn off the Up Call light
            desiredSpeed = 1; // set the desired moving up speed
        } else {
            SetCallLight(currentFloor, false, false); // turn off the Down Call light
            desiredSpeed = -1; // set the desired moving down speed
        }
        ChangeLoading();
        SetBrake(false);
        state = Moving;
        printf("Transition: from Idle to MovingUp.\n");
    }
}

// State moving
void StateMoving() {
    // Cannot open/close the door when elevator is moving
    if (GetOpenDoorLight()) {
        SetOpenDoorLight(false);
    }
    if (GetCloseDoorLight()) {
        SetCloseDoorLight(false);
    }

    // Where are we going?
    int gotoFloor = WhatFloorToGoToInThisDirection(goingUp);

    // How far are we away from the floor we are going to?
    double distance = fabs(GetFloor() - gotoFloor);

    // The elevator car gets to the end of its travel
    if (distance < FloorTolerance) {
        if (goingUp) {
            SetCallLight(gotoFloor, true, false);
        } else {
            SetCallLight(gotoFloor, false, false);
        }
        SetMotorPower(0);
        SetBrake(true);
        SetDoor(gotoFloor, true);
        state = Idle;
        return; // Optimization without calculate the power when elevator stops
    }

    if (distance < 0.5 * FloorSpacing) { // Start to decelerate, continuously update the desired speed
        desiredSpeed = goingUp ? (distance / 1.64) : (-distance / 1.64);
    }
        
    /* Compute new motor power here */
    // 1st section, propotional term = Kp * et;
    // 2nd section, integral term = Ki * Sum[for (i = 0 to N(200 which is(1/5 second))) e(t - i) * deltaT(0.001s)]
    err = desiredSpeed - GetVelocity();
    errorLoc = (errorLoc + 1) % N;
    errorTotal = errorTotal - errors[errorLoc] + err;
    errors[errorLoc] = err;
    double power = Kp * err + Ki * Dt * errorTotal; // TODO: consider if condition here for check the break status 
    SetMotorPower(power);
}

// State OpenDoor, will automatically switch to ClosingDoor state
void StateOpenDoor() {
    int currentFloor = GetNearestFloor();  // which floor we're at now

    // Close the door if the Panel Close Door Button is pressed
    if (GetCloseDoorLight()) {
        SetCloseDoorLight(false); // turn off the light
        SetDoor(currentFloor, false); // close the door
        state = ClosingDoor;
        printf("Transition: from OpenDoor to ClosingDoor.\n");
        return;
    }

    // Do nothing but turn off the Panel Open Door Button if Door is Open(ing)
    if (GetOpenDoorLight()) {
        SetOpenDoorLight(false); // turn off the light
        return;
    }

    // After door opened for 3 seconds, close the door
    if (isDoorOpen(currentFloor)) {
        if (!isTimerSet) {
            ResetTimer();
            isTimerSet = true;
            return;
        } else if (GetTimer() > 3) {
            isTimerSet = false;
            SetDoor(currentFloor, false);
            state = ClosingDoor;
            printf("Transition: from OpenDoor to ClosingDoor.\n");
            return;
        }
    }
}

// State Closing Door
void StateClosingDoor() {
    int currentFloor = GetNearestFloor();  // which floor we're at now

    // Open the door if the Panel Open Door Button is pressed
    if (GetOpenDoorLight()) {
        SetOpenDoorLight(false); // turn off the light
        SetDoor(currentFloor, true); // open the door
        state = OpenDoor;
        printf("Transition: from ClosingDoor to OpenDoor.\n");
        return;
    }

    // Do nothing but turn off the Panel Close Door Button if Door is Clos(ed/ing)
    if (GetCloseDoorLight()) {
        SetCloseDoorLight(false); // turn off the light
        return;
    }

    // After door closed, set state to Idle and wait for next command
    if (IsDoorClosed(currentFloor)) {
        state = Idle;
        printf("Transition: from ClosingDoor to Idle.\n");
        return;
    }
}
