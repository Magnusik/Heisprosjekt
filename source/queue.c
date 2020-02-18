#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"

void update_new_order(int *p_matrix) {
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            if(hardware_read_order(f, order_type)){
                *p_matrix = 1;
                //printf("ordertype: %d floor: %d pressed = %d",order_type,f,*p_matrix);
                hardware_command_order_light(f,order_type,1);
            }
            p_matrix++;
        }
    }
}


//hardware_read_order(f, order_type)


void clear_all_orders(int *p_matrix){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            *p_matrix = 0;
            hardware_command_order_light(f,order_type,0);
            p_matrix++;
        }
    }
}




void clear_order_on_floor(int *p_matrix, int floor){
    
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){

        *(p_matrix+(order_type+floor*3)) = 0;
        hardware_command_order_light(floor,order_type,0);
    }
}