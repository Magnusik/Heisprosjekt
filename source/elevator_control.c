#include "elevator_control.h"

int elevator_init(){
  while(!(hardware_read_floor_sensor(0) || hardware_read_floor_sensor(1) || hardware_read_floor_sensor(2) || hardware_read_floor_sensor(3))){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
  }
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  for (int floor = 0; floor<HARDWARE_NUMBER_OF_FLOORS; floor++){
    if (hardware_read_floor_sensor(floor)){
      int current_floor=floor; 
      return current_floor;
    }
  }
  return -1;
}

void elevator_clear_all_order_lights(){
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

Software_state elevator_go_up_or_down(int order_floor,int current_floor){
  if(order_floor > current_floor){
    return Software_state_moving_up;

  }else if(order_floor < current_floor){
    return Software_state_moving_down;

  }else {
    return Software_state_idle;
  }
}

int elevator_at_floor(){

  for (int floor = 0; floor<HARDWARE_NUMBER_OF_FLOORS; floor++){
    if (hardware_read_floor_sensor(floor)){
      int current_floor_is = floor;
      return current_floor_is;
    }
  }
  return -1;
}



Software_state elevator_movement_from_idle(int current_floor, HardwareMovement previous_direction){

    if(queue_check_orders_waiting() == -1){
      return Software_state_waiting;
    }
    else if((current_floor == 3) && queue_check_order_below(current_floor)){
      return Software_state_moving_down;
    } 
    else if((current_floor == 0) && queue_check_order_above(current_floor)){
      return Software_state_moving_up;
    } 
    else if(((previous_direction == HARDWARE_MOVEMENT_UP) && queue_check_order_above(current_floor))){
      return Software_state_moving_up;
    }
    else if((previous_direction == HARDWARE_MOVEMENT_DOWN) && queue_check_order_below(current_floor)){
      return Software_state_moving_down;
    }
    else if ((previous_direction == HARDWARE_MOVEMENT_UP) && queue_check_order_below(current_floor)){
      return Software_state_moving_down;
    }
    else if ((previous_direction == HARDWARE_MOVEMENT_DOWN) && queue_check_order_above(current_floor)){
      return Software_state_moving_up;
    }
    else {
      return Software_state_waiting; /////////////////////////muligens feil.
    }
}
