#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"


void add_order(int* p_order_matrix[][]){

        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            for (int order_type = 0; order_type < HARDWARE_NUMER_OF_ORDER_BUTTONS; order_type++ ){
                if(hardware_read_order(f, order_type)){
                    (*p_order_matrix)[f][order_type] *= 1;
                    hardware_command_order_light(f, order_type, (*p_order_matrix)[f][order_type]);        
            }
        }
    }
}
int hardware_read_order(int floor, HardwareOrder order_type);

void hardware_command_order_light(int floor, HardwareOrder order_type, int on)