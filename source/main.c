#include "hardware.h"
#include "elevator_control.h"
#include "timer.h"






static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}


int main(){

  //Global variables
  int current_floor;
  int floor_up;
  int floor_down;
  int order_floor;
  Software_state current_state;
  int enable_timer = 1;
  int transistion_stop_obstruction = 0;

  HardwareMovement elevator_movement;
  HardwareMovement previous_direction;


  int error = hardware_init();
  if(error != 0){
      fprintf(stderr, "Unable to initialize hardware\n");
      exit(1);
  }

  signal(SIGINT, sigint_handler);

  current_floor = elevator_init();
  floor_up = current_floor + 1;
  floor_down = current_floor;
  current_state = Software_state_waiting;

  elevator_clear_all_order_lights();
  hardware_command_door_open(0);
  
  while(1){

    elevator_update_orders();


    if (hardware_read_stop_signal()){
        elevator_movement = HARDWARE_MOVEMENT_STOP;
        current_state = Software_state_stop;
    }
    

    switch(current_state){
      case Software_state_waiting:
        if (elevator_at_floor() != NOT_IN_FLOOR){
          hardware_command_floor_indicator_on(elevator_at_floor());
        }

        current_floor = elevator_at_floor();
        order_floor = queue_check_orders_waiting();

        printf("\n\nCurrent floor: %d\n\n", current_floor);
        printf("\n\nfloor up: %d\n\n", floor_up);

        if((order_floor != NOT_IN_FLOOR) && (current_floor != NOT_IN_FLOOR)){
            current_state= elevator_go_up_or_down(order_floor, current_floor);
        }
        else if((order_floor != NOT_IN_FLOOR) && (current_floor == NOT_IN_FLOOR)){
            if(order_floor >= floor_up){
                current_state = Software_state_moving_up;
            }
            else if(order_floor <= floor_down){
                current_state = Software_state_moving_down;
            }
        }
        break;




      case Software_state_idle:
        printf("\n\nIDLE\n\n");
        hardware_command_movement(elevator_movement);    //Muligens bare ha stopp her? skaper forvirring med en variabel.
        elevator_clear_orders_on_floor(elevator_at_floor());
        hardware_command_door_open(OPEN);
        if(enable_timer){
          timer_start();
          enable_timer = OFF;
        }

        if (hardware_read_obstruction_signal()){
          timer_start();
        }

        if(timer_has_elapsed()){
          timer_stop();
          hardware_command_door_open(CLOSE);
          current_floor = elevator_at_floor();
          current_state = elevator_movement_from_idle(current_floor, previous_direction);
          enable_timer = ON;
        }
        break;



      case Software_state_moving_up:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        int prevent_racing_up;
        if ((prevent_racing_up = elevator_at_floor()) != NOT_IN_FLOOR){
          floor_down = prevent_racing_up;   
          floor_up =  floor_down + 1;
          hardware_command_floor_indicator_on(elevator_at_floor());
          current_floor = elevator_at_floor();
          elevator_movement = elevator_movement_at_floor_for_moving_up(current_floor);

          if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_UP;
            current_state = Software_state_idle;
          }
        }
        break;




      case Software_state_moving_down:
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        int prevent_racing_down;
        if ((prevent_racing_down = elevator_at_floor()) != NOT_IN_FLOOR ){
          floor_up = prevent_racing_down;
          floor_down = floor_up - 1;
          hardware_command_floor_indicator_on(elevator_at_floor());
          current_floor = elevator_at_floor();
          elevator_movement = elevator_movement_at_floor_for_moving_down(current_floor);


          if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_DOWN;
            current_state = Software_state_idle;
          }
        }
        break;



      case Software_state_stop:
        hardware_command_movement(elevator_movement);
        
        while(hardware_read_stop_signal()){
          hardware_command_stop_light(ON);
          elevator_clear_all_orders();

          if (elevator_at_floor() != NOT_IN_FLOOR){
            hardware_command_door_open(ON);
            timer_start();
          }
          else{
            enable_timer = ON;
            current_state = Software_state_waiting;
            break;   // Vil ikke dette føre til at den hopper ut av while-løkken                      
          }          // med en gang hvis man stopper mellom to etasjer?
        }

        hardware_command_stop_light(OFF);

        if(hardware_read_obstruction_signal()){
          elevator_clear_orders_on_floor(elevator_at_floor());
          timer_start();
          transistion_stop_obstruction = 1;

        }
        else if (((transistion_stop_obstruction == 1) && hardware_read_obstruction_signal()) || hardware_read_stop_signal()) {
          timer_start();
          transistion_stop_obstruction = 0;
        }
        
        else if (timer_has_elapsed()){
          timer_stop();
          hardware_command_door_open(0);
          enable_timer = ON;
          current_state = Software_state_waiting;
        }

        break;
    }
  }
  return 0;
}