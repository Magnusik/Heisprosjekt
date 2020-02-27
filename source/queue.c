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


int queue_check_order_below(int current_floor){
    if(current_floor == 0){
        return 0;
    }
    for (int f = 0; f < current_floor; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMBER_OF_ORDER_BUTTONS; order_type ++){
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
