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
static int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMER_OF_ORDER_BUTTONS]={
{0,0,0},
{0,0,0},
{0,0,0},
{0,0,0}};





static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}



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
  state=Software_state_waiting;

  clear_all_order_lights();
  
  while(1){
    switch(state)
    {
      case Software_state_waiting:
        ;
        int *p_order_matrix = &order_button_matrix[0][0];
        update_new_order(p_order_matrix);
        int *p_clear_order= &order_button_matrix[0][0];
        clear_all_orders(p_clear_order);
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
