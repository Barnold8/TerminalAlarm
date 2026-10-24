#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <threads.h>
#include <limits.h>
#include "../headers/parseTime.h"

FILE* openFile(const char* path){

	FILE *fptr;

	fptr = fopen(path, "r");
	
	if(fptr == NULL){
		fprintf(stderr, "Error opening file at path %s", path);
		return NULL;
	} 

	return fptr;
}

int main(int argc,const char * argv[]){

  const char* USAGE = "Alarm <xxH:xxM:xxS> [command_to_run_when_alarm_finished]";
  FILE *fptr;

  if (argc < 2) {
    printf("Error: no argument given\n");
    printf(USAGE);
    return -1;
  }
  if(argc == 3){
	printf("printing: %s \n",argv[2]);
	openFile("FFF.txt"); 
  }

  AlarmTime user_time = argsToAlarmTime(argv[1]);

  if (user_time.error_code == -1) {
    printf("Error: could not parse time given\n");
    return -1;
  }
  int time_to_wait = toSeconds(user_time);
 
  timer(time_to_wait);
  
  return 0;
}
