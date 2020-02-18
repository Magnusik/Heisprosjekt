#include "elevator_control.h"



int init_elevator(){
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


int check_orders_wating(int order_matrix[4][3]){

  for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
      if(order_matrix[f][order_type]==1){
        return f;
      }
    }
  }
  return -1;
}


Software_state go_up_or_down(int order_floor,int current_floor){
  if(order_floor > current_floor){
    return Software_state_moving_up;

  }else if(order_floor > current_floor){
    return Software_state_moving_down;

  }else {
    return Software_state_idle;
  }
}




int elevator_at_floor(){

  for (int floor = 0; floor<HARDWARE_NUMBER_OF_FLOORS; floor++){
    if (hardware_read_floor_sensor(floor)){
      int current_floor=floor;
      return current_floor;
    }
  }
  return -1;
}





HardwareMovement elevator_stop_at_floor_for_moving_up(int current_floor, int order_button_matrix[4][3]){

  if(current_floor == (HARDWARE_NUMBER_OF_FLOORS -1)){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type = 0; order_type < (HARDWARE_NUMBER_OF_ORDER_BUTTONS -1); order_type++){
    if(order_button_matrix[current_floor][order_type]){
      printf("yp");
      return HARDWARE_MOVEMENT_STOP;
    }
  }

  for(int f = (current_floor +1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
      if (order_button_matrix[f][order_type]){
        return HARDWARE_MOVEMENT_UP;
      }
    }
  }
return HARDWARE_MOVEMENT_UP;
}

















HardwareMovement elevator_stop_at_floor_for_moving_down(int current_floor,int order_button_matrix[4][3]){

  if(current_floor == 0 ){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type  = 1; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS ; order_type++){
    if(order_button_matrix[current_floor][order_type]){
      return HARDWARE_MOVEMENT_STOP;
    }
  }
  for(int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
    for(int f = 0; f < current_floor; f++){
      if (order_button_matrix[f][order_type]){
        return HARDWARE_MOVEMENT_DOWN;
      }
    }
  }
  return HARDWARE_MOVEMENT_DOWN;
}



