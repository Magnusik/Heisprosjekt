#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"

#define ORDER_UP 0
#define ORDER_INSIDE 1
#define ORDER_DOWN 2


#define NO_ORDERS -1



/**
 * @file
 * @brief Adds order to queue.
 * 
 * @param floor Floor the order was given to.
 * @param order_type Type of order; up, inside or down.
 * 
 * @warning Changes @p order_button_matrix.
 */
void queue_add_order(int floor, int order_type);




/**
 * @brief Removes order from queue.
 * 
 * @param floor Floor the order was given to.
 * @param order_type Type of order; up, inside or down.
 * 
 * @warning Changes @p order_button_matrix.
 */
void queue_remove_order(int floor, int order_type);


/**
 * @brief Checks if a specific order is active.
 * 
 * @param floor Floor the order was given to.
 * @param order_type Type of order; up, inside or down.
 * 
 * @return 1 if the order is active, 0 if not.
 */
int queue_check_order(int floor, int order_type);



/**
 * @brief Checks if any order is given.
 * 
 * @return Floor where the order was given, -1 if no orders.
 */
int queue_check_orders_waiting();




/**
 * @brief Checks if there are orders to floors below the @p current_floor.
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

#endif


