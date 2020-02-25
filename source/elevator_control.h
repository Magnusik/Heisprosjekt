#ifndef elevator_control_h
#define elevator_control_h
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "queue.h"

#define OPEN 1
#define CLOSE 0


/**
 * @file 
 * @brief The states which the elevator can possibly be in.
 */

typedef enum {
  Software_state_waiting,
  Software_state_idle,
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;

/**
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
 * Lagt til fra refactoring
 * 
 */

void elevator_update_orders();


/**
 * Lagt til fra refactoring
 * 
 */
void elevator_clear_all_orders();


/**
 * Lagt til fra refactoring
 * 
 */
void elevator_clear_orders_on_floor(int floor);


/**
 * @brief Decides if the elevator should go up or down depending on what floor the order wants you to go to.
 * @param order_floor Floor to go to. 
 * @param current_floor The floor the elevator is currently in.
 * @return state
 */
Software_state elevator_movement_from_floor(int order_floor,int current_floor);

/**
 * @brief Checks if the elevator is at or passing by a defined floor.
 * 
 * 
 * @return 0 if 1.st floor, 1 if 2.nd , 2 if 3.rd and 3 if 4.th. -1 if the elevator finds itself between floors.
 */
int elevator_at_floor();

/**
 * @brief Calculates which state the elevator should enter from the state idle.
 * 
 * @param current_floor The floor the elevator is currently in.
 * @param previous_direction The direction the elevator had before it enter the idle state.
 * 
 * @return The state the elevator should enter next.
 */
Software_state elevator_movement_from_idle(int current_floor, HardwareMovement previous_direction);






HardwareMovement elevator_movement_at_floor_for_moving_up(int current_floor_is);





HardwareMovement elevator_movement_at_floor_for_moving_down(int current_floor_is);



Software_state elevator_movement_from_undef_floor(int order_floor, int floor_up);

#endif