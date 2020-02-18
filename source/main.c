#include "hardware.h"
#include "elevator_control.h"
#include "queue.h"
#include "timer.h"
#include "global.h"





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

  HardwareMovement elevator_stop;


  int error = hardware_init();
  if(error != 0){
      fprintf(stderr, "Unable to initialize hardware\n");
      exit(1);
  }

  signal(SIGINT, sigint_handler);

  current_floor = init_elevator();
  printf("current floor is: %d\n",current_floor+1 );
  state = Software_state_waiting;

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
        //printf("wait");
        break;
      case Software_state_idle:
        ;
        printf("idle");
        int *p_clear_floor= &order_button_matrix[0][0];
        clear_order_on_floor(p_clear_floor, current_floor);

        break;
      case Software_state_moving_up:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        previous_floor = current_floor;
        if (previous_floor == current_floor+1){

        }

        //printf("up");

        break;
      case Software_state_moving_down:

        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);

        if (elevator_at_floor()!=-1){
          current_floor = elevator_at_floor();
          elevator_stop =elevator_stop_at_floor_for_moving_down(current_floor);
          hardware_command_movement(elevator_stop);
          printf("Current floor: %d",current_floor);
        }




        printf("down");

        break;
      case Software_state_stop:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        printf("stop");
        int *p_clear_order= &order_button_matrix[0][0];
        clear_all_orders(p_clear_order);

        while(hardware_read_stop_signal()){
          hardware_command_stop_light(1);

          if (elevator_at_floor() != -1){
            hardware_command_door_open(1);
          }

        }
        hardware_command_stop_light(0);
        if (elevator_at_floor() != -1){
          
          timer_3_sec();
          hardware_command_door_open(0);
        }
        printf("døren er lukket!");
        state = Software_state_waiting;
        

        break;
    }
  }

  return 0;
}
