#ifndef PARSETIME_H
#define PARSETIME_H


#include <time.h>
#include <string.h>
#include <math.h>
#include <threads.h>
#include <limits.h>
#include "utils.h"

typedef struct {
  int hours;
  int minutes;
  int seconds;
  int error_code;
}
AlarmTime;

int toSeconds(AlarmTime t);

AlarmTime toAlarmTime(int s);

void printAlarm(int seconds);

AlarmTime argsToAlarmTime(const char * user_time);

float timePassed(clock_t start, clock_t now);

int isAlarm(clock_t start, clock_t now, float target_duration);

void timer(int seconds, const char * command);

#endif
