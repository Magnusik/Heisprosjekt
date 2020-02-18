#include <time.h> 
#include <stdio.h> 
#include <unistd.h>
#include "timer.h"
#include "queue.h"
#include "global.h"

int timer_3_sec() {

    time_t start_sec = time(NULL);

    float time_difference;
    while(time_difference<3){

      time_t end_sec = time(NULL);
      time_difference = difftime(end_sec,start_sec);

      //printf("%.2f",time_difference);

      int *p_order_matrix = &order_button_matrix[0][0];
      update_new_order(p_order_matrix);
    }
    return 1;
}