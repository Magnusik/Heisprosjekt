#include <time.h> 
#include <stdio.h> 
#include <unistd.h>
#include "timer.h"
#include "queue.h"
#include "hardware.h"





int timer_active = 0;

void start_timer(){
  timer_active = 1;
  time_stamp  = time(NULL);
}

int has_timer_elapsed(){
  return(timer_active && ((time(NULL) - time_stamp) > 3));
}

void stop_timer(){
  timer_active = 0;
}

int is_timer_active(){
  return timer_active;
}

























// int timer_3_sec() {

//     time_t start_sec = time(NULL);
//     time_t end_sec = time(NULL);

    

//     float time_difference = 0;

//     while(time_difference < 3){
//       // printf("ninnenfor whilesssssssdyokiz halla.");
//       // printf("%f",time_difference);

//       end_sec = time(NULL);
//       time_difference = difftime(end_sec,start_sec);
//       queue_update_new_order();

//       if(hardware_read_obstruction_signal()){
//         //start_sec = end_sec;
//         printf("fk u OBS!k askjer her kiz```????");
//       }


//       if (hardware_read_stop_signal()){
//         break;
//       }
//     }
//     return 1;
// }







      // while (hardware_read_obstruction_signal()){

      //   printf("\n\nUtenfor while.\n\n");
      //   queue_update_new_order();
      //   if(!hardware_read_obstruction_signal()){
      //     start_sec = time(NULL);
      //     break;
      //   }

      //   if (hardware_read_stop_signal()){
      //     break;
      //   }

      // }






// while (hardware_read_obstruction_signal()){
//         start_sec = time(NULL);
//         queue_update_new_order();
//         if (hardware_read_stop_signal()){
//           break;
//         }
//       }
