#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_ORDER_BUTTONS]={
{0,0,0},
{0,0,0},
{0,0,0},
{0,0,0}};


void queue_update_new_order() {
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            if(hardware_read_order(f, order_type)){
                order_button_matrix[f][order_type] = 1;
                hardware_command_order_light(f,order_type,1);
            }
        }
    }
}




int queue_check_orders_waiting(){

  for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
      if(order_button_matrix[f][order_type]==1){
        return f;
      }
    }
  }
  return -1;
}



void queue_clear_all_orders(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            order_button_matrix[f][order_type]=0;
            hardware_command_order_light(f,order_type,0);
        }
    }
}




void queue_clear_order_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
        order_button_matrix[floor][order_type]=0;
        hardware_command_order_light(floor,order_type,0);
    }
}



int queue_check_order_below(int current_floor){
    if(current_floor == 0){
        return 0;
    }
    for (int f = 0; f < current_floor; f++){
        for (int order_type = 0; order_type <HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type ++){
            if(order_button_matrix[f][order_type]){
                return 1;
            }
        }
    }
    return -1;
}

int queue_check_order_above(int current_floor){
    if(current_floor == (HARDWARE_NUMBER_OF_FLOORS - 1)){
        return 0;
    }
    for (int f = (current_floor + 1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if(order_button_matrix[f][order_type]){
                return 1;
            }
        }
    }
    return -1;
}

HardwareMovement queue_movement_at_floor_for_moving_up(int current_floor){

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
return HARDWARE_MOVEMENT_STOP;//////////////////////////////////////////////////////////////////////////
}


HardwareMovement queue_movement_at_floor_for_moving_down(int current_floor){

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
  return HARDWARE_MOVEMENT_DOWN;//////////////////////////////////////////////////////////////////////////
}
