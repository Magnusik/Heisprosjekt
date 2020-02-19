#include "hardware.h"
#include "elevator_control.h"
#include "queue.h"
#include "timer.h"



//Global variables
int current_floor;
int previous_floor;
Software_state current_state;



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

  current_floor = elevator_init();
  printf("current floor is: %d\n",current_floor+1 );
 current_state= Software_state_waiting;

  elevator_clear_all_order_lights();
  
  while(1){


    queue_update_new_order();

    if (hardware_read_stop_signal()){
       current_state= Software_state_stop;
    }



    switch(state){
      case Software_state_waiting:
      ;

        int order_floor = elevator_check_orders_waiting(order_button_matrix);
        if(order_floor !=-1){
         current_state= elevator_go_up_or_down(order_floor, current_floor);
        } else if(){

          
        }
        //printf("wait");
        break;
      case Software_state_idle:
        ;
        printf("idle");
        int *p_clear_floor= &order_button_matrix[0][0];
        queue_clear_order_on_floor(p_clear_floor, current_floor);

        break;
      case Software_state_moving_up:
        //hardware_command_movement(HARDWARE_MOVEMENT_UP);
    
        if (elevator_at_floor()!=-1){
          //printf("%d",elevator_at_floor());
          elevator_stop = elevator_stop_at_floor_for_moving_up(elevator_at_floor(),order_button_matrix);
          hardware_command_movement(elevator_stop);
          //printf("%d",elevator_stop);
        }
        //printf("%d",order_button_matrix[2][0]);



        //printf("up");

        break;
      case Software_state_moving_down:

        //hardware_command_movement(HARDWARE_MOVEMENT_DOWN);

        if (elevator_at_floor()!=-1){
          current_floor = elevator_at_floor();
          elevator_stop =elevator_stop_at_floor_for_moving_down(current_floor,order_button_matrix);
          hardware_command_movement(elevator_stop);
          //printf("Current floor: %d",current_floor);
        }




        printf("down");

        break;
      case Software_state_stop:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        printf("stop");

        queue_clear_all_orders();

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
       current_state= Software_state_waiting;
        

        break;
    }
  }

  return 0;
}
