#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "io.h"
#include "schedule.h"

int inputMenuOption() {
    printf("1 - Insert a new event\n");
    printf("2 - Display all events\n");
    printf("3 - Now?\n");
    printf("4 - Delete expired\n");
    printf("0 - Exit\n");
    return inputInt("Please select an option: ");
}

bool isScheduleEmpty(Schedule *schedule) {
    if (schedule == NULL) return true;
    return schedule->numEvents == 0;
}

// Use a dummy node to help the insert and delete of list
void insertNewEvent(Schedule *schedule, Event *event) {
    Event *e = (event == NULL) ? createNewEvent() : event;
    if (isScheduleEmpty(schedule)) {
        schedule->head = e;
    } else {
        Event *dummy = (Event *)malloc(sizeof(Event));
        dummy->next = schedule->head;

        Event *prev = dummy, *curr = dummy->next;
        while (curr != NULL && curr->start < e->start) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = e;
        e->next = curr;

        // Update the schedule head
        schedule->head = dummy->next;
        freeEvent(dummy);
    }
    
    // Update the schedule event count
    schedule->numEvents++;

    bool firstOverlap = true;
    Event *curr = schedule->head;
    while (curr != NULL) {
        if (isOverlap(curr, e) && e != curr) {
            if (firstOverlap) 
                printf("Warning, this event overlaps: \n");
            displayEvent(curr);
        }
        curr = curr->next;
    }
}

void displayAllEvents(Schedule *schedule) {
    if (isScheduleEmpty(schedule)) {
        printf("Your calendar is empty\n");
    } else {
        Event *curr = schedule->head;
        printf("Schedule: (%d events)\n", schedule->numEvents);
        while (curr != NULL) {
            displayEvent(curr);
            curr = curr->next;
        }
    }
}

void displayActiveEvents(Schedule *schedule) {
    bool firstActive = true;
    Event *curr = schedule->head;
    while (curr != NULL) {
        if (isActive(curr)) {
            if (firstActive) {
                printf("Currently active events: \n");
                firstActive = false;
            }
            displayEvent(curr);
        }
        curr = curr->next;
    }
    if (firstActive)
        printf("No currently active events\n");
}

void deleteExpiredEvents(Schedule *schedule) {
    if (isScheduleEmpty(schedule) || !isExpired(schedule->head)) {
        printf("No expired events\n");
        return;
    }

    bool firstExpire = true;

    Event *dummy = (Event *)malloc(sizeof(Event));
    dummy->next = schedule->head;

    Event *prev = dummy, *curr = dummy->next;
    while (curr != NULL) {
        if (isExpired(curr)) {
            if (firstExpire) {
                printf("Deleting:\n");
                firstExpire = false;
            }
            displayEvent(curr);

            // do the deletion
            Event *next = curr->next; // cache the current event
            prev->next = next;
            freeEvent(curr);
            curr = next;
            schedule->numEvents--;
        } else {
            curr = curr->next;
        }
    }

    // Update the schedule head
    schedule->head = dummy->next;
    freeEvent(dummy);
    if (firstExpire)
        printf("No expired events\n");
}

void freeSchedule(Schedule *schedule) {
    if (schedule != NULL) {
        Event *curr = schedule->head;
        while (curr != NULL) {
            Event *next = curr->next;
            freeEvent(curr);
            curr = next;
        }
        schedule->numEvents = 0;
        free(schedule);
        schedule = NULL;
    }
}

/* Assume the file format is always correct */
void loadFile(const char *filename, Schedule *schedule) {
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return;

    char buffer[100];

    // Read the number of events
    fgets(buffer, sizeof(buffer), file);
    int numEvents;
    sscanf(buffer, "%d", &numEvents);

    for (int i = 0; i < numEvents; i++) {
        Event *e = (Event *) malloc(sizeof(Event));

        fgets(buffer, sizeof(buffer), file);
        /* Remove any \n we may have input */
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';

        /* Copy up to max characters to event description */
        strncpy(e->description, buffer, strlen(buffer));

        struct tm tim;

        fgets(buffer, sizeof(buffer), file);
        /* Remove any \n we may have input */
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';

        strptime(buffer, "%a %b %d %H:%M:%S %Y", &tim);
        e->date = mktime(&tim);
        e->start = e->date;

        fgets(buffer, sizeof(buffer), file);
        /* Remove any \n we may have input */
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';
        strptime(buffer, "%a %b %d %H:%M:%S %Y", &tim);
        e->end = mktime(&tim);
        e->next = NULL;

        // displayEvent(e);
        insertNewEvent(schedule, e);
    }
    fclose(file);
}

void saveFile(const char *filename, Schedule *schedule) {
    FILE *file = fopen(filename, "w");
    char buffer[100];

    fprintf(file, "%d\n", schedule->numEvents);
    Event *curr = schedule->head;
    while (curr != NULL) {
        fprintf(file, "%s\n", curr->description);
        fprintf(file, "%s", ctime(&(curr->start)));
        fprintf(file, "%s", ctime(&(curr->end)));
        curr = curr->next;
    }
    fclose(file);
}