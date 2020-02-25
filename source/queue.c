#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


static int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_ORDER_BUTTONS]={
{0,0,0},
{0,0,0},
{0,0,0},
{0,0,0}};


void queue_add_order(int floor, int order_type){
    order_button_matrix[floor][order_type] = 1;
}

void queue_remove_order(int floor, int order_type){
    order_button_matrix[floor][order_type] = 0;
}

int queue_check_order(int floor, int order_type){
    return order_button_matrix[floor][order_type];
}



int queue_check_orders_waiting(){

  for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
      if(order_button_matrix[f][order_type] == 1){
        return f;
      }
    }
  }
  return -1;
}



void queue_clear_order_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){   ////////////////////////////////
        order_button_matrix[floor][order_type] = 0;
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
    return 0;
}

int queue_check_order_above(int current_floor_is){
    if(current_floor_is == (HARDWARE_NUMBER_OF_FLOORS - 1)){
        return 0;
    }
    for (int f = (current_floor_is + 1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if(order_button_matrix[f][order_type]){
                return 1;
            }
        }
    }
    return 0;
}

HardwareMovement queue_movement_at_floor_for_moving_up(int current_floor_is){

  if(current_floor_is == (HARDWARE_NUMBER_OF_FLOORS -1)){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type = 0; order_type < (HARDWARE_NUMBER_OF_ORDER_BUTTONS -1); order_type++){
    if(order_button_matrix[current_floor_is][order_type]){
      return HARDWARE_MOVEMENT_STOP;
    }
  }

  for(int f = (current_floor_is +1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
      if (order_button_matrix[f][order_type]){
        return HARDWARE_MOVEMENT_UP;
      }
    }
  }
  if (order_button_matrix[current_floor_is][2]){
    return HARDWARE_MOVEMENT_STOP;
  }

    if (current_floor_is == 0){
    return HARDWARE_MOVEMENT_UP;
  }

return HARDWARE_MOVEMENT_UP;//////////////////////////////////////////////////////////////////////////
}


HardwareMovement queue_movement_at_floor_for_moving_down(int current_floor_is){

  if(current_floor_is == 0 ){
    return HARDWARE_MOVEMENT_STOP;
  }

  for (int order_type  = 1; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS ; order_type++){
    if(order_button_matrix[current_floor_is][order_type]){
      return HARDWARE_MOVEMENT_STOP;
      
    }
  }

  if (current_floor_is == 3){
    return HARDWARE_MOVEMENT_DOWN;
  }

  for (int f = 0; f < current_floor_is; f++){
    for(int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
      if (order_button_matrix[f][order_type]){
        return HARDWARE_MOVEMENT_DOWN;
      }
    }
  }

  if (order_button_matrix[current_floor_is][0]){
    return HARDWARE_MOVEMENT_STOP;
  }
  return HARDWARE_MOVEMENT_DOWN;//////////////////////////////////////////////////////////////////////////
}




void print_matrix(){
  for(int i = 0; i < 4; i++){
    for (int j = 0; j<3; j++){
      printf("%d",order_button_matrix[i][j]);
    }
    printf("\n");
  }
}
