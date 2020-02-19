#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"

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


//hardware_read_order(f, order_type)


void queue_clear_all_orders(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
            order_button_matrix[f][order_type];
            hardware_command_order_light(f,order_type,0);
        }
    }
}




void queue_clear_order_on_floor(int floor){
    for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type++ ){
        order_button_matrix[floor][order_type];
        hardware_command_order_light(floor,order_type,0);
    }
}