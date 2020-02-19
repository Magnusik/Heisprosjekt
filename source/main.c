#include "hardware.h"
#include "elevator_control.h"
#include "queue.h"
#include "timer.h"



//Global variables
int current_floor;
int previous_floor;
int floor_up;
int floor_down;
Software_state current_state;



static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}



int main(){

  HardwareMovement elevator_movement;
  HardwareMovement previous_direction;


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
       current_state = Software_state_stop;
    }



    switch(state){
      case Software_state_waiting:
      ;

        int order_floor = queue_check_orders_waiting(order_button_matrix);
        if(order_floor !=-1 ){
            if(current_floor != -1){
                current_state= elevator_go_up_or_down(order_floor, current_floor);
            }
            else{
                if(order_floor >= floor_up){
                  current_state = Software_state_moving_up;
                }
                else if(order_floor <= floor_down){
                  current_state = Software_state_moving_down;
                }
            }
        } 

          
    
        //printf("wait");
        break;
      case Software_state_idle:
        ;
        //printf("idle");
        queue_clear_order_on_floor(elevator_at_floor());
        hardware_command_door_open(1);
        while(hardware_read_obstruction_signal()){
            queue_update_new_order;
            if (hardware_read_stop_signal()){
                current_state = Software_state_stop;
                break;
            }
        }
        if (current_state == Software_state_idle){
            timer_3_sec();
        }
        current_floor = elevator_at_floor();

        current_state = elevator_movement_from_idle(current_floor, previous_direction);

        break;
      case Software_state_moving_up:
        //hardware_command_movement(HARDWARE_MOVEMENT_UP);
    
        if (elevator_at_floor()!=-1){
          //printf("%d",elevator_at_floor());
          floor_down = elevator_at_floor();
          floor_up = floor_down +1;
          elevator_movement = elevator_movement_at_floor_for_moving_up(elevator_at_floor());
          hardware_command_movement(elevator_movement);
          //printf("%d",elevator_movement);
        }
        //printf("%d",order_button_matrix[2][0]);


        if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_UP;
            state = Software_state_idle;
        }
        //printf("up");

        break;
      case Software_state_moving_down:

        //hardware_command_movement(HARDWARE_MOVEMENT_DOWN);

        if (elevator_at_floor()!=-1){
          floor_up = elevator_at_floor();
          floor_down = floor_up +1;
          elevator_movement = elevator_movement_at_floor_for_moving_down(elevator_at_floor());
          hardware_command_movement(elevator_movement);
          //printf("Current floor: %d",current_floor);
        }


        if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_DOWN;
            state = Software_state_idle;
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

          while(hardware_read_obstruction_signal()){
            queue_update_new_order();
          }
          timer_3_sec();
          hardware_command_door_open(0);
        }
        printf("døren er lukket!");
       current_state = Software_state_waiting;
        

        break;
    }
  }

  return 0;
}
