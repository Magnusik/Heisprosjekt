#include "elevator_control.h"



int elevator_at_floor(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        if (hardware_read_floor_sensor(floor)){
            return floor;
        }
    }
    return -1;
}



int elevator_init(){
    while(elevator_at_floor() == NOT_IN_FLOOR){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    return elevator_at_floor();
}



void elevator_clear_all_order_lights(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            hardware_command_order_light(floor, order_type, OFF);
        }
    }
}


int elevator_check_orders_waiting(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            if(queue_check_order(f, order_type)){
                return f;
            }
        }
    }
    return -1;
}



void elevator_update_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if (hardware_read_order(floor, order_type)){
                queue_add_order(floor, order_type);
                hardware_command_order_light(floor, order_type, ON);
            }
        }
    }
}



void elevator_clear_all_orders(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            queue_remove_order(floor, order_type);
            hardware_command_order_light(floor, order_type, OFF);
        }
    }
}



void elevator_clear_orders_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
        queue_remove_order(floor, order_type);
        hardware_command_order_light(floor, order_type, OFF);
    }
}



static Order_priority priority = PRIORITY_RESET;



Software_state elevator_movement_from_floor(int order_floor_is,int current_floor_is){
    if(order_floor_is > current_floor_is){
        return Software_state_moving_up;

    }
    else if(order_floor_is < current_floor_is){
        return Software_state_moving_down;

    }
    else {
        priority = PRIORITY_RESET;
        return Software_state_idle;
    }
}



Software_state elevator_movement_from_idle(int current_floor, HardwareMovement previous_direction){
    if(elevator_check_orders_waiting() == NO_ORDERS){
        return Software_state_waiting;
    }

    else if((current_floor == (HARDWARE_NUMBER_OF_FLOORS - 1)) && queue_check_order_below(current_floor)){
        return Software_state_moving_down;
    } 

    else if((current_floor == 0) && queue_check_order_above(current_floor)){
        return Software_state_moving_up;
    } 

    else if((priority == PRIORITY_DOWN) && queue_check_order_below(current_floor)){
        return Software_state_moving_down;
    }

    else if((priority == PRIORITY_UP) && queue_check_order_above(current_floor)){
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

    return Software_state_waiting;
}



HardwareMovement elevator_movement_at_floor_for_moving_up(int current_floor){
    if(current_floor == (HARDWARE_NUMBER_OF_FLOORS -1)){
        priority = PRIORITY_RESET;
        return HARDWARE_MOVEMENT_STOP;
    }

    if (current_floor == 0){
        priority = PRIORITY_RESET;
        return HARDWARE_MOVEMENT_UP;
    }

    for (int order_type = 0; order_type < (HARDWARE_NUMBER_OF_ORDER_BUTTONS -1); order_type++){  //Sjekker om det er ordre i samme retning eller ordre fra kabinen, i den etasjen den kommer til.
        if(queue_check_order(current_floor, order_type)){
            priority = PRIORITY_RESET; 
            return HARDWARE_MOVEMENT_STOP;
        }
    }

    for(int f = (current_floor + 1); f < HARDWARE_NUMBER_OF_FLOORS; f++ ){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if (queue_check_order(f, order_type)){
                priority = PRIORITY_RESET; 
                return HARDWARE_MOVEMENT_UP;
            }
        }
    }

    if (queue_check_order(current_floor, 2)){
        priority = PRIORITY_DOWN; 
        return HARDWARE_MOVEMENT_STOP;
    }

    priority = PRIORITY_RESET; 
    return HARDWARE_MOVEMENT_UP;
}



HardwareMovement elevator_movement_at_floor_for_moving_down(int current_floor){
    if(current_floor == 0 ){
        priority = PRIORITY_RESET;
        return HARDWARE_MOVEMENT_STOP;
    }

    if(current_floor == 3){
        priority = PRIORITY_RESET;
        return HARDWARE_MOVEMENT_DOWN;
    }

    for(int order_type  = 1; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS ; order_type++){ //Sjekker om det er ordre i samme retning eller ordre fra kabinen, i den etasjen den kommer til.
        if(queue_check_order(current_floor, order_type)){
            priority = PRIORITY_RESET;
            return HARDWARE_MOVEMENT_STOP; 
        }
    }

    for(int f = 0; f < current_floor; f++){
        for(int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            if (queue_check_order(f, order_type)){
                priority = PRIORITY_RESET; 
                return HARDWARE_MOVEMENT_DOWN;
            }
        }
    }

    if(queue_check_order(current_floor, 0)){
        priority = PRIORITY_UP; 
        return HARDWARE_MOVEMENT_STOP;
    }

    priority = PRIORITY_RESET;
    return HARDWARE_MOVEMENT_DOWN;
}


Software_state elevator_movement_from_undef_floor(int order_floor, int floor_up){
    if(order_floor >= floor_up){
        return Software_state_moving_up;
    }
    else {
        return Software_state_moving_down;
    }
}
