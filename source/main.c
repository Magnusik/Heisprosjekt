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
  int enable_timer=1;
  int a;

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
  current_state= Software_state_waiting;

  elevator_clear_all_order_lights();
  hardware_command_door_open(0);
  
  while(1){


    queue_update_new_order();

    if (hardware_read_stop_signal()){
        elevator_movement = HARDWARE_MOVEMENT_STOP;
        current_state = Software_state_stop;
    }
    

    switch(current_state){
      case Software_state_waiting:

        //print_matrix();

        if (elevator_at_floor() != -1){
          hardware_command_floor_indicator_on(elevator_at_floor());
        }

        current_floor = elevator_at_floor();  ////////////////////////// mulig kilde
        order_floor = queue_check_orders_waiting();


        if((order_floor !=-1) && (current_floor != -1)){
            current_state= elevator_go_up_or_down(order_floor, current_floor);
        }
        else if((order_floor !=-1) && (current_floor == -1)){
            if(order_floor >= floor_up){
                current_state = Software_state_moving_up;
            }
            else if(order_floor <= floor_down){
                current_state = Software_state_moving_down;
            }
        }
        break;




      case Software_state_idle:

        hardware_command_movement(elevator_movement);
        queue_clear_order_on_floor(elevator_at_floor());
        hardware_command_door_open(1);
        if(enable_timer){
          start_timer();
          enable_timer=0;
        }

        if (hardware_read_obstruction_signal()){
          start_timer();
        }

        if(has_timer_elapsed()){
          stop_timer();
          hardware_command_door_open(0);
          current_floor = elevator_at_floor();
          current_state = elevator_movement_from_idle(current_floor, previous_direction);
          enable_timer=1;
        }
        break;



      case Software_state_moving_up:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    
        if (elevator_at_floor() != -1){               //Hvis heisen er i en etasje, vil den gå inn i if-setningen.
          hardware_command_floor_indicator_on(elevator_at_floor());
          floor_down = elevator_at_floor();
          floor_up = floor_down +1;
          current_floor = elevator_at_floor();
          elevator_movement = queue_movement_at_floor_for_moving_up(current_floor); // Kanskje feil.

          if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_UP;
            current_state = Software_state_idle;
          }
        }

        break;




      case Software_state_moving_down:
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);

        if (elevator_at_floor()!=-1){
          hardware_command_floor_indicator_on(elevator_at_floor());
          floor_up = elevator_at_floor();
          floor_down = floor_up - 1;
          current_floor = elevator_at_floor();
          elevator_movement = queue_movement_at_floor_for_moving_down(current_floor); //muligens feil her


          if(elevator_movement == HARDWARE_MOVEMENT_STOP){        
            previous_direction = HARDWARE_MOVEMENT_DOWN;
            current_state = Software_state_idle;
          }
        }
        break;



      case Software_state_stop:
        hardware_command_movement(elevator_movement);
        
        while(hardware_read_stop_signal()){
          hardware_command_stop_light(1);
          queue_clear_all_orders();

          if (elevator_at_floor() != -1){
            hardware_command_door_open(1);
            start_timer();
          }
        }

        hardware_command_stop_light(0);

        if(hardware_read_obstruction_signal()){
          stop_timer();
          a = 2;

        }
        else if ((elevator_at_floor() != -1) && (a == 2)) {
          start_timer();
          a = 0;
        }

        if (elevator_at_floor() == -1){
          current_state = Software_state_waiting;
        }
        else if (has_timer_elapsed()){
          stop_timer();
          hardware_command_door_open(0);
          current_state = Software_state_waiting;
        }


        break;
    }
  }

  return 0;
}



