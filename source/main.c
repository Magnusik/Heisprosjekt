#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"
#include "queue.h"
#define HARDWARE_NUMER_OF_ORDER_BUTTONS 3

typedef enum {
  Software_state_waiting,
  Software_state_idle,
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;

//Global variables
int current_floor;
Software_state state; 
static int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMER_OF_ORDER_BUTTONS];



static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){



  for (int i = 0;i<4;i++){
    for (int j = 0; j<3;j++){
      order_button_matrix[i][j] = 0;

    }
  }







  int error = hardware_init();
  if(error != 0){
      fprintf(stderr, "Unable to initialize hardware\n");
      exit(1);
  }

  signal(SIGINT, sigint_handler);

  current_floor = init_elevator();
  printf("current floor is: %d\n",current_floor+1 );
  state=Software_state_waiting;
  
  while(1){
    switch(state)
    {
      case Software_state_waiting:
        ;
        int *ap;
        ap = &(order_button_matrix[0][0]);
        update_new_order(ap);

        break;
      case Software_state_idle:

        break;
      case Software_state_moving_up:

        break;
      case Software_state_moving_down:

        break;
      case Software_state_stop:
        break;
    }
  }

  return 0;
}
