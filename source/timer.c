#include <time.h> 
#include <stdio.h> 
#include <unistd.h>
#include "timer.h"
#include "queue.h"
#include "hardware.h"


time_t time_stamp;

int timer_active = 0;

void timer_start(){
  timer_active = 1;
  time_stamp  = time(NULL);
}

int timer_has_elapsed(){
  return(timer_active && ((time(NULL) - time_stamp) > 3));
}

void timer_stop(){
  timer_active = 0;
}


