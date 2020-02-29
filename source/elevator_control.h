/**
 * @file
 * @brief Elevator control module.
 * 
 * Functions for deciding the behavior of the elevator system.
 */

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
 * @brief The states which the elevator can possibly be in, after initializing.
 */

typedef enum {
  Software_state_waiting,
  Software_state_idle,     //Elevator has active orders, but is at a halt. 
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;



/**
 * @brief Which orders should be prioritised in @c elevator_movement_from_idle.
 */
typedef enum {
    PRIORITY_DOWN,
    PRIORITY_UP,
    PRIORITY_RESET
} Order_priority;



/**
 * @brief Checks if the elevator is at a defined floor or passing by a defined floor.
 * 
 * @return 0 if 1.st floor, 1 if 2.nd , 2 if 3.rd and 3 if 4.th.
 * -1 if the elevator finds itself between floors.
 */
int elevator_at_floor();



/**
*@brief Initializes the elevator to reach a defined floor. Default direction down.

*@return The floor the elevator finds.
*/
int elevator_init();



/**
 * @brief Clears all order lights.
 */
void elevator_clear_all_order_lights();


/**
 * @brief Checks if any order is given.
 * 
 * @return Floor where the order was given, -1 if no orders.
 */
int elevator_check_orders_waiting();



/**
 * @brief Takes new orders and updates lights accordingly
 */
void elevator_update_orders();


/**
 * @brief Removes all orders and extinguishes all order lights.
 */
void elevator_clear_all_orders();


/**
 * @brief Removes all orders on @p floor, and extinguishes lights accordingly.
 * 
 * @param floor The floor the lights should be extinguished in.
 * 
 */
void elevator_clear_orders_on_floor(int floor);


/**
 * @brief Decides which state the elevator should enter from the state idle.
 * 
 * @param order_floor Floor of the order given. 
 * @param current_floor The floor the elevator is currently in.
 * 
 * @return state
 */
Software_state elevator_movement_from_floor(int order_floor,int current_floor);



/**
 * @brief Decides which state the elevator should enter from the state idle.
 * 
 * @param current_floor The floor the elevator is currently in.
 * @param previous_direction The direction the elevator had before it enter the idle state.
 * 
 * @return The state the elevator should enter next.
 */
Software_state elevator_movement_from_idle(int current_floor, HardwareMovement previous_direction);




/**
 * @brief Calculates whether or not the elevator should stop at the floor that it just entered.
 * Takes into account that the elevator is entering the floor from the moving up state.
 * 
 * @param Current_floor The floor that the elevator enters.
 * 
 * @return The elevators next movement.
 */

HardwareMovement elevator_movement_at_floor_for_moving_up(int current_floor);



/**
 * @brief Calculates whether or not the elevator should stop at the floor that it just entered.
 * Takes into account that the elevator is entering the floor from the moving down state.
 * 
 * @param Current_floor The floor that the elevator enters.
 * 
 * @return The elevators next movement.
 */

HardwareMovement elevator_movement_at_floor_for_moving_down(int current_floor);


/**
 * @brief Calculates which direction the elevator should go when it is resting between two floors.
 * 
 * @param order_floor The floor the order is given to.
 * @param floop_up The floor above the elevator.
 * 
 * @return state.
 */
Software_state elevator_movement_from_undef_floor(int order_floor, int floor_up);

#endif