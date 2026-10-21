#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include <math.h>

typedef struct {
  int hours;
  int minutes;
  int seconds;
  int error_code;
}
AlarmTime;

void printAlarm(char * time) {

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
      printf("%s\n", time);
    } else {
      printf(clock[i]);
    }

  }
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

int charIsNum(char c) {
  return c < 58 && c > 47;
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
          u_time.seconds = t;printf("Reading %s\n",user_time);
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

int main(int argc,
  const char * argv[]) {

  if (argc < 2) {
    printf("Error: no argument given\n");
    return -1;
  }

  AlarmTime user_time = argsToAlarmTime(argv[1]);

  printf("%d hours %d minutes %d seconds\n", user_time.hours, user_time.minutes, user_time.seconds);

  if (user_time.error_code == -1) {
    printf("Error: could not parse time given\n");
    return -1;
  }

}

//	int prev_time = 0;
//	int running = 1;
//
//	clock_t start,now;
//	float time_passed;
//	int time_in_seconds;
//
//	int target = 25;
//
//	start = clock();
//	now = clock();
//
//	printAlarm("12M:20s");

//	while(running){

//	now = clock();
//	float time_passed = (float)(now-start) / CLOCKS_PER_SEC;
//	time_in_seconds = (int) time_passed;
//	
//	if(time_in_seconds > prev_time){
//		prev_time = time_in_seconds;
//		printf("You have %d seconds left\n",(60*target)-time_in_seconds);	
//	}
//	if(timePassed(start,now) > 60*target){
//		running = 0;
//	}	
//}	
//printf("TIMER FINISHED!!!!!!\n");
