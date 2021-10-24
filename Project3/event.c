#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "io.h"

// Two events A and B do not overlap if A ends before B starts or A starts after B ends. 
bool isOverlap(Event *a, Event *b) {
    return !(a->end < b->start || a->start > b->end);
}

Event* createNewEvent() {
    Event *e = (Event *) malloc(sizeof(Event));
    
    printf("What is the event: ");
    inputString(e->description, sizeof(e->description));

    e->date = inputDate("Event date: ");
    e->start = inputTime("Start time: ", e->date);
    e->end = inputTime("End time: ", e->date);
    e->next = NULL;

    return e;
}

void displayEvent(Event *e) {
    char startBuffer[20];
    char endBuffer[20];
    char *result;

    struct tm start;
    struct tm end;
    start = *localtime(&(e->start));
    end = *localtime(&(e->end));

    // 4/14/2011  2:00PM  3:00PM Prepare for CSE 251
    strftime(startBuffer, 20, "%m/%d/%Y %l:%M%p ", &start);
    strftime(endBuffer, 20, "%l:%M%p ", &end);

    printf("%s",startBuffer);
    printf("%s",endBuffer);
    printf("%s\n", e->description);
}

// An event is currently active if the current time is greater than or equal to the start time 
// and less than or equal to the end time. 
bool isActive(Event *e) {
    // Get the current time
    time_t rawtime;
    time(&rawtime);
    return (e->start <= rawtime && rawtime <= e->end);
}

bool isExpired(Event *e) {
    // Get the current time
    time_t rawtime;
    time(&rawtime);
    return (e->end < rawtime);
}

void freeEvent(Event *e) {
    if (e != NULL) {
        free(e);
        e = NULL;
    }
}
