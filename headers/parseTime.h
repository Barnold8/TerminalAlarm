#ifndef PARSETIME
#define PARSETIME

#include "utils.h"

typedef struct {
  int hours;
  int minutes;
  int seconds;
  int error_code;
}
AlarmTime;

int toSeconds(AlarmTime t){

	int seconds = 0;

	if(!(t.hours || t.minutes || t.seconds)){
	 	return 0;
	}

	if(t.hours > 0){
		seconds += t.hours * 3600;
	}	
	if(t.minutes > 0){
		seconds += t.minutes*60;
	}
	if(t.seconds > 0){
		seconds += t.seconds;
	}
	
	return seconds;
}



void printAlarm(int time) {

  // ascii art of clock
  char * clock[] = {
    "       .--.\n",
    "  .-._;.--.;_.-.\n",
    " (_.'_..--.._'._)\n",
    "  /.' .    . '.\\ \n",
    " // .        . \\\\\n",
    "|; .          . |;\n",
    "",
    "|; .          . |;\n",
    " \\\\ .        . //\n",
    "  \\'._'    '_.'/\n",
    "   '-._'--'_.-'\n",
    "       `\"\"`\n"

  };

  // "||      ()      ||\n",

  size_t clock_size = sizeof(clock) / sizeof(clock[0]);
  int mid_point = 6;
  for (size_t i = 0; i < clock_size; i++) {
    if (i == mid_point) {
      printf("%d\n", time);
    } else {
      printf(clock[i]);
    }

  }
}

AlarmTime argsToAlarmTime(const char * user_time) {

  AlarmTime u_time = {
    -1,
    -1,
    -1,
    -1
  };

  int string_len = strlen(user_time);
  int t = 0;
  int segment = 0;
  int traverse = 0;

  for (int i = string_len - 1; i >= 0; i--) {

    if (charIsNum(user_time[i])) {
      t += (user_time[i] - 48) * pow(10, traverse);
      traverse++;
    } else {

      switch (user_time[i]) {

      case 'H':
        segment = 2;
        traverse = 0; 
        break;
      
      case 'M':
	segment = 1;
        traverse = 0;
	break;
      
      case 'S':
	segment = 0; // not really needed but for completeness sakes
        traverse = 0;
        break;
      
      case ':':
        switch (segment) {
        case 0:
          u_time.seconds = t;
          break;
        case 1:
          u_time.minutes = t;
          break;
        case 2:
          u_time.hours = t;
          break;

        default:
          printf("Error: an unexpected character '%c' was encountered in the input %s\n", user_time[i], user_time);
          return u_time;
          break;
        }
	t = 0;
      }
    }
  }

  if(t > 0){

	  // assumes some information is left to be parsed
  
  	  switch(segment){
	
	  case 0:
            u_time.seconds = t;printf("Reading %s\n",user_time);
            break;
          case 1:
            u_time.minutes = t;
	    break;
        
	  case 2: 
            u_time.hours = t;
            break;

          default:
           printf("Error: arrived at end of input with data remaining and no way to apply it. %d was left with a segment of %d\n",t,segment);
           return u_time;
           break;
        }	
  }
  u_time.error_code = 0;
  return u_time;

}

float timePassed(clock_t start, clock_t now) {
  return (float)(now - start) / CLOCKS_PER_SEC;
}

int isAlarm(clock_t start, clock_t now, float target_duration) {

  if (timePassed(start, now) > target_duration) {
    return 1;
  }
  return 0;
}

void timer(int seconds){

    struct timespec start, now;

    int prev_time = 0;
    int running = 1;
    int seconds_left = INT_MAX;

    timespec_get(&start, TIME_UTC);

    int target = seconds;
    struct timespec delay = {.tv_sec = 0, .tv_nsec = 50000000};

    clearTerminal(); // flush any previous user terminal usage before running the timer

    while(running) {

	thrd_sleep(&delay, NULL); // Sleep thread for delay amount
        timespec_get(&now, TIME_UTC);

        int time_in_seconds = (int)(now.tv_sec - start.tv_sec);

        if(time_in_seconds > prev_time) {

	    prev_time = time_in_seconds;

            int seconds_left = target - time_in_seconds;
            if (seconds_left >= 0){
              	   printAlarm(seconds_left);
                   clearTerminal();
	    }
        }

        if(time_in_seconds >= target) {
            running = 0;
        }
    }
}

#endif
