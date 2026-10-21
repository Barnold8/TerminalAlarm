#include <stdio.h>
#include <time.h>


typedef struct {
	int hours;
	int minutes;
	int seconds;
} AlarmTime;

void printAlarm(char* time){

	// ascii art of clock
	char* clock[] = {
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

	size_t clock_size = sizeof(clock)/sizeof(clock[0]);
		int mid_point = 6;
	for(size_t i = 0; i < clock_size; i++){
		if(i == mid_point){
			printf("%s\n",time);
		}else{
			printf(clock[i]);
		}
		
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

	printAlarm("12M:20s");

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
}
