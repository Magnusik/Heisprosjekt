#include <time.h> 
#include <stdio.h> 
#include <unistd.h>
#include "timer.h"
#include "queue.h"
#include "hardware.h"


int timer_3_sec() {

    time_t start_sec = time(NULL);

    float time_difference;
    while(time_difference < 3){

      time_t end_sec = time(NULL);
      time_difference = difftime(end_sec,start_sec);

      //printf("%.2f",time_difference);
      queue_update_new_order();

      if (hardware_read_stop_signal()){
        break;
      }
    }
    return 1;
}
