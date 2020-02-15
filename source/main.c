#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"

typedef enum {
  Software_state_waiting,
  Software_state_idle,
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;

int current_floor;

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){

  int error = hardware_init();
  if(error != 0){
      fprintf(stderr, "Unable to initialize hardware\n");
      exit(1);
  }

  signal(SIGINT, sigint_handler);

  current_floor = init_elevator();
  printf("current floor is: %d\n",current_floor+1 );

  // while(1){
  //   switch(Software_state)
  //   {
  //     case Software_state_waiting:

  //       break;
  //     case Software_state_idle:

  //       break;
  //     case Software_state_moving_up:

  //       break;
  //     case Software_state_moving_down:

  //       break;
  //     case Software_state_stop:
  //       break;
  //   }
  // }

  return 0;
}
