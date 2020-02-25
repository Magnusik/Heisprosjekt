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


void elevator_update_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if (hardware_read_order(floor, order_type)){
                queue_add_order(floor, order_type);
                hardware_command_order_light(floor, order_type, 1);
            }
        }
    }
}




void elevator_clear_all_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            queue_remove_order(floor, order_type);
            hardware_command_order_light(floor, order_type, 0);
        }
    }
}


void elevator_clear_orders_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
        queue_remove_order(floor, order_type);
        hardware_command_order_light(floor, order_type, 0);
    }
}



Software_state elevator_go_up_or_down(int order_floor_is,int current_floor_is){
  if(order_floor_is > current_floor_is){
    return Software_state_moving_up;

  }else if(order_floor_is < current_floor_is){
    return Software_state_moving_down;

  }else {
    return Software_state_idle;
  }
}

int elevator_at_floor(){
  for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
    if (hardware_read_floor_sensor(floor)){
      return floor;
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




HardwareMovement elevator_movement_at_floor_for_moving_up(int current_floor_is){

  if(current_floor_is == (HARDWARE_NUMBER_OF_FLOORS -1)){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type = 0; order_type < (HARDWARE_NUMBER_OF_ORDER_BUTTONS -1); order_type++){
    if(queue_check_order(current_floor_is, order_type)){
      return HARDWARE_MOVEMENT_STOP;
    }
  }

  for(int f = (current_floor_is + 1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
      if (queue_check_order(f, order_type)){
        return HARDWARE_MOVEMENT_UP;
      }
    }
  }
  if (queue_check_order(current_floor_is, 2)){
    return HARDWARE_MOVEMENT_STOP;
  }

    if (current_floor_is == 0){
    return HARDWARE_MOVEMENT_UP;
  }

return HARDWARE_MOVEMENT_UP;
}





HardwareMovement elevator_movement_at_floor_for_moving_down(int current_floor_is){

  if(current_floor_is == 0 ){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type  = 1; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS ; order_type++){
    if(queue_check_order(current_floor_is, order_type)){    
      return HARDWARE_MOVEMENT_STOP;
      
    }
  }

  if (current_floor_is == 3){
    return HARDWARE_MOVEMENT_DOWN;
  }

  for (int f = 0; f < current_floor_is; f++){
    for(int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
      if (queue_check_order(f, order_type)){ 
        return HARDWARE_MOVEMENT_DOWN;
      }
    }
  }

  if (queue_check_order(current_floor_is, 0)){ 
    return HARDWARE_MOVEMENT_STOP;
  }
  return HARDWARE_MOVEMENT_DOWN;
}

