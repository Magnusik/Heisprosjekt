#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator_control.h"

void update_new_order(int *p_matrix) {
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for (int order_type = 0; order_type < HARDWARE_NUMER_OF_ORDER_BUTTONS; order_type++ ){
            if(hardware_read_order(f, order_type)){
                *p_matrix = 1;
            }
            p_matrix++;
        }
    }
}