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

  int current_floor;
  int floor_up;
  int order_floor;
  int enable_timer = 1;
  Software_state current_state;

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
  current_state = Software_state_waiting;

  elevator_clear_all_order_lights();
  hardware_command_door_open(0);
  
  while(1){

    elevator_update_orders();

    if (hardware_read_stop_signal()){
        current_state = Software_state_stop;
    }

    switch(current_state){

      case Software_state_waiting:
          if (elevator_at_floor() != NOT_IN_FLOOR){
              hardware_command_floor_indicator_on(elevator_at_floor());
          }

          current_floor = elevator_at_floor();
          order_floor = elevator_check_orders_waiting();

          if((order_floor != NOT_IN_FLOOR) && (current_floor != NOT_IN_FLOOR)){
              current_state = elevator_movement_from_floor(order_floor, current_floor);
          }

          else if((order_floor != NOT_IN_FLOOR) && (current_floor == NOT_IN_FLOOR)){
              current_state = elevator_movement_from_undef_floor(order_floor, floor_up);
          }
        break;




      case Software_state_idle:
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
          elevator_clear_orders_on_floor(current_floor);
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
              current_floor = prevent_racing_up;
              floor_up =  prevent_racing_up + 1;
            
              hardware_command_floor_indicator_on(current_floor);

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
              current_floor = prevent_racing_down;
              floor_up = prevent_racing_down;

              hardware_command_floor_indicator_on(current_floor);

              elevator_movement = elevator_movement_at_floor_for_moving_down(current_floor);


              if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
                  previous_direction = HARDWARE_MOVEMENT_DOWN;
                  current_state = Software_state_idle;
              }
          }
        break;




      case Software_state_stop:
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
          hardware_command_stop_light(ON);

          while(hardware_read_stop_signal()){

              elevator_clear_all_orders();
              if (elevator_at_floor() != NOT_IN_FLOOR){
                  hardware_command_door_open(ON);
              }
          }

          hardware_command_stop_light(OFF);

          if (elevator_at_floor() != NOT_IN_FLOOR){
              current_state = Software_state_idle;
              enable_timer = ON;
              break;
          }

          current_state = Software_state_waiting;

        break;
    }
  }
  return 0;
}