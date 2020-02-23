#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"

/**
 * @file
 * @brief A matrix containing 12 elements which represents the different order-button-types.
 * An element is 1 if an order is active, and 0 if an order is inactive.
 */
int order_button_matrix[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_ORDER_BUTTONS];

/**
 * @brief Read order from user and updates @p order_button_matrix and sets lights accordingly.
 * 
 * @warning Changes @p order_button_matrix.
 */
void queue_update_new_order();


/**
 * @brief Checks for orders in @p order_button_matrix.
 * 
 * @return Floor where the order was given, -1 if no orders.
 */
int queue_check_orders_waiting();



/**
 * @brief Clears all current orders and extinguishes all order lights.
 * 
 * @warning Sets all elements in @p order_button_matrix to 0.
 */
void queue_clear_all_orders();

/**
 * @brief Clears all orders on given @p floor in the @p order_button_matrix and extinguishes lights accordingly.
 * 
 * @param floor The floor that the orders should be cleared in.
 * 
 * @warning changes @p order_button_matrix.
 */
void queue_clear_order_on_floor(int floor);



/**
 * @brief Checks if there are orders to floors below the current floor.
 * 
 * @param Current_floor The floor the elevator is currently in.
 * 
 * @return 1 of there are orders below, 0 if not.
 */
int queue_check_order_below(int current_floor);



/**
 * @brief Checks if there are orders to floors above the current floor.
 * 
 * @param Current_floor The floor the elevator is currently in.
 * 
 * @return 1 of there are orders above, 0 if not.
 */
int queue_check_order_above(int current_floor);



HardwareMovement queue_movement_at_floor_for_moving_up(int current_floor_is);

HardwareMovement queue_movement_at_floor_for_moving_down(int current_floor_is);


void print_matrix();

#endif


