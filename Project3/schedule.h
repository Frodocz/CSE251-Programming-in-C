#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdbool.h>
#include "event.h"


/* Define the menu options */
#define EXIT		0
#define INSERT 		1
#define DISPLAY 	2
#define NOW 		3
#define DELETE		4

/* Due to a lot of insert and delete operation, use a linked list to store the events, doublely linked list should be better */
typedef struct Schedule {
	Event *head;
	int numEvents;
} Schedule;

int inputMenuOption();

/* No global variable allowed, so pass in a pointer to the current active schedule */
bool isScheduleEmpty(Schedule *schedule);

void insertNewEvent(Schedule *schedule);

void displayAllEvents(Schedule *schedule);

void displayActiveEvents(Schedule *schedule);

void deleteExpiredEvents(Schedule *schedule);

void freeSchedule(Schedule *schedule);

#endif /* SCHEDULE_H */