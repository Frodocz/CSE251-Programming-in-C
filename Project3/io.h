#ifndef IO_H
#define IO_H

#define __USE_XOPEN
#include <time.h>

void inputString(char *str, int max);
time_t inputDate(char *prompt);
time_t inputTime(char *prompt, time_t date);
int inputInt(char *prompt);

#endif /* IO_H */