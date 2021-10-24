#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"

int main() {
    int option;
    Schedule *schedule = (Schedule *)malloc(sizeof(Schedule));
    schedule->head = NULL;
    schedule->numEvents = 0;

    loadFile(FILE_NAME, schedule);

    while (true) {
        option = inputMenuOption();
        if(feof(stdin))
            return 0;

        if (option == INSERT) {
            insertNewEvent(schedule, NULL);
            saveFile(FILE_NAME, schedule);
        } else if (option == DISPLAY) {
            displayAllEvents(schedule);
        } else if (option == NOW) {
            displayActiveEvents(schedule);
        } else if (option == DELETE) {
            deleteExpiredEvents(schedule);
            saveFile(FILE_NAME, schedule);
        } else {
            printf("Thank you for using the scheduler\n");
            break;
        }
    }

    /* Free the memory */
    freeSchedule(schedule);
    return 0;
}