

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


void queue_clear_orders_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
        order_button_matrix[floor][order_type] = 0;
    }
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



int pull_buttons_from(int current_floor){
    for (int floor = current_floor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++){
            
        }
    }
}













