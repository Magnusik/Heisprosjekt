#pragma once
#include "hardware.h"
#include "elevator_control.h"




//Global variables
int current_floor;
int previous_floor;
Software_state state; 
static int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMER_OF_ORDER_BUTTONS]={
{0,0,0},
{0,0,0},
{0,0,0},
{0,0,0}};



