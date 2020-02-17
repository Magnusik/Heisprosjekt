#include "elevator_control.h"
#include "hardware.h"

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
    for (int order_type = 0; order_type < HARDWARE_NUMER_OF_ORDER_BUTTONS; order_type++ ){
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

