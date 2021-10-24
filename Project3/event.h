#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>
#define __USE_XOPEN
#include <time.h>

#define MAX_DESCRIPTION_LEN        51

typedef struct Event {
    char description[MAX_DESCRIPTION_LEN];
    time_t date;    /* eg: 4/14/2011 */
    time_t start;   /* eg: 3:00pm */
    time_t end;;    /* eg: 4:30pm */
    struct Event *next;
} Event;


bool isOverlap(Event *a, Event *b);

bool isActive(Event *e);

bool isExpired(Event *e);

Event* createNewEvent();

void displayEvent(Event *e);

void freeEvent(Event *e);

#endif /* EVENT_H */