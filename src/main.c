#include <stdio.h>
#include <time.h>

void printAlarm(char* time){

	// ascii art of clock
	char* clock[] = {
		".--.\n",
		".-._;.--.;_.-.\n",
		"(_.'_..--.._'._)\n",
		"/.' . 60 . '.\\n"
	}; 
	size_t clockSize = sizeof(clock)/sizeof(clock[0]);
	
	int midPoint = 5;
	for(size_t i = 0; i < clockSize; i++){
		printf(clock[i]);
	}
	
}

float timePassed(clock_t start, clock_t now){
	return (float)(now-start) / CLOCKS_PER_SEC;
}

int is_alarm(clock_t start, clock_t now, float target_duration){

	if(timePassed(start,now) > target_duration){
		return 1;
	}
	return 0;
}

int main(){
	
	int prev_time = 0;
	int running = 1;

	clock_t start,now;
	float time_passed;
	int time_in_seconds;

	int target = 25;

	start = clock();
	now = clock();

	while(running){
		
		now = clock();
		float time_passed = (float)(now-start) / CLOCKS_PER_SEC;
		time_in_seconds = (int) time_passed;
		
		if(time_in_seconds > prev_time){
			prev_time = time_in_seconds;
			printf("You have %d seconds left\n",(60*target)-time_in_seconds);	
		}
		if(timePassed(start,now) > 60*target){
			running = 0;
		}	
	}	
	printf("TIMER FINISHED!!!!!!\n");
}
