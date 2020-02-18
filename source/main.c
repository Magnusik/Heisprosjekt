#include "hardware.h"
#include "elevator_control.h"
#include "queue.h"
#define HARDWARE_NUMER_OF_ORDER_BUTTONS 3



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

    int *p_order_matrix = &order_button_matrix[0][0];
        update_new_order(p_order_matrix);

    if (hardware_read_stop_signal()){
        state = Software_state_stop;
    }



    switch(state){
      case Software_state_waiting:
      ;

        int order_floor = check_orders_wating(order_button_matrix);
        if(order_floor !=-1){
          state = go_up_or_down(order_floor, current_floor);
        }
        printf("wait");
        break;
      case Software_state_idle:
        printf("idle");
        int *p_clear_floor= &order_button_matrix[0][0];
        clear_order_on_floor(p_clear_floor, current_floor);

        break;
      case Software_state_moving_up:
        printf("up");

        break;
      case Software_state_moving_down:
        printf("down");

        break;
      case Software_state_stop:
        printf("stop");
        int *p_clear_order= &order_button_matrix[0][0];
        clear_all_orders(p_clear_order);

        while(hardware_read_stop_signal()){
          hardware_command_stop_light(1);

          if (#####at_floor()){
            hardware_command_door_open(1);
          }

        }
        hardware_command_stop_light(0);
        if (#####at_floor()){
          //wait 3 sec.
          hardware_command_door_open(0);
        }
        state = Software_state_waiting;

        break;
    }
  }

  return 0;
}
