#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"

typedef enum {
  Software_state_waiting,
  Software_state_idle,
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;

/**
*@file
*@brief initializes the program to reach a defined floor. Starts with @c hardware_command_movement direction down.
*@return int of @p current_floor, -1 if it didnt reach a floor sensor.
*/
int init_elevator();

/**
 * @brief checks for orders in order matrix.
 * @param order_matrix matrix containing all order buttons.
 * @return loor where the order was given.
 */

int check_orders_wating(int order_matrix[4][3]);

/**
 * @brief Decides if the elevator should go up or down depending on what floor the order wants you to go to.
 * @param order_floor floor to go to 
 * @param current_floor the floor the elevator is currently on
 * @return state
 */
Software_state go_up_or_down(int order_floor,int current_floor);






int elevator_at_floor();



HardwareMovement elevator_stop_at_floor_for_moving_up(int current_floor);



HardwareMovement elevator_stop_at_floor_for_moving_down(int current_floor);