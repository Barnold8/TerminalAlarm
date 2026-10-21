#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../headers/parseTime.h"

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
