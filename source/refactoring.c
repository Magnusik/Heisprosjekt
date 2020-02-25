

// FUNKSJONER TIL QUEUE:

void queue_add_order(int floor, int order_type){
    order_button_matrix[floor][order_type] = 1;
}

void queue_remove_order(int floor, int order_type){
    order_button_matrix[floor][order_type] = 0;
}

int queue_check_order(int floor, int order_type){
    return order_button_matrix[floor][order_type];
}

//FUNKSJONER TIL ELEVATOR CONTROL:



void elevator_update_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_TYPES; order_type++){
            if (hardware_read_order(floor, order_type)){
                queue_add_order(floor, order_type);
            }
        }
    }
}


void elevator_update_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type; order_type < HARDWARE_NUMBER_OF_ORDER_TYPES; order_type++){
            if (hardware_read_order(floor, order_type)){
                queue_add_order(floor, order_type);
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



void elevator_update_order_lights(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if (queue_check_order(floor, order_type)){
                hardware_command_order_light(floor, order_type, 1);
            }
        }
    }
}

void elevator_clear_order_lights_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
        hardware_command_order_light(floor, order_type, 0);
    }
}

void elevator_clear_all_lights(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
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











int pull_buttons_from(int current_floor){
    for (int floor = current_floor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            
        }
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

  for(int f = (current_floor_is +1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
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














