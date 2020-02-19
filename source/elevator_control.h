#ifndef elevator_control_h
#define elevator_control_h
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
int elevator_init();

/**
 * @brief Clears all order lights.
 * 
 */


void elevator_clear_all_order_lights();



/**
 * @brief Decides if the elevator should go up or down depending on what floor the order wants you to go to.
 * @param order_floor floor to go to 
 * @param current_floor the floor the elevator is currently on
 * @return state
 */
Software_state elevator_go_up_or_down(int order_floor,int current_floor);

/**
 * @brief Checks if the elevator is at or passing by a defined floor.
 * 
 * 
 * @return 0 if 1.st floor, 1 if 2.nd , 2 if 3.rd and 3 if 4.th. -1 between floors.
 */

int elevator_at_floor();



HardwareMovement elevator_movement_at_floor_for_moving_up(int current_floor,int order_button_matrix[4][3]);



HardwareMovement elevator_movement_at_floor_for_moving_down(int current_floor,int order_button_matrix[4][3]);




#endif