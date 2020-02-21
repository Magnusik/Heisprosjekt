#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"



int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_ORDER_BUTTONS];

/**
 * @file 
 * @brief Takes order from user and updates @p p_matrix and sets lights accordingly.
 * 
 * @param p_matrix A pointer to the @p order_button_matrix.
 * 
 * @warning Changes @p order_button_matrix.
 */

void queue_update_new_order();


/**
 * @brief checks for orders in order matrix.
 * 
 * @return Floor where the order was given, -1 if no orders.
 */

int queue_check_orders_waiting();





/**
 * @brief Clears all current orders and sets extinguishes all order lights.
 * 
 * @param p_order_matrix A pointer to the @p order_button_matrix.
 * 
 * @warning Changes @p order_button_matrix.
 */

void queue_clear_all_orders();

/**
 * @brief Clears all orders on given @p floor in the matrix  that pointer @p p_matrix points to.
 * @param p_matrix A pointer to a matrix
 * @param floor A value that represents the floor of type int
 * @warning changes @p p_matrix and dereferences value pointed to.
 */

void queue_clear_order_on_floor(int floor);



/**
 * @brief Checks if there are orders to floors below the current floor.
 * 
 * @param Current_floor The floor the elevator is currently in.
 * 
 * 
 * @return 1 of there are orders below, 0 if not.
 * 
 */

int queue_check_order_below(int current_floor);



/**
 * @brief Checks if there are orders to floors above the current floor.
 * 
 * @param Current_floor The floor the elevator is currently in.
 * 
 * 
 * @return 1 of there are orders above, 0 if not.
 * 
 */

int queue_check_order_above(int current_floor);



HardwareMovement queue_movement_at_floor_for_moving_up(int current_floor_is);

HardwareMovement queue_movement_at_floor_for_moving_down(int current_floor_is);


void print_matrix();

#endif


