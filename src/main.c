#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <threads.h>
#include <limits.h>
#include "../headers/parseTime.h"

int main(int argc,const char * argv[]){

  if (argc < 2) {
    printf("Error: no argument given\n");
    return -1;
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
