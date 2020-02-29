/**
 * @file
 * @brief Queue module.
 * 
 * Functions for checking and modifying the queue.
 */

#ifndef QUEUE_H
#define QUEUE_H

#define ORDER_UP 0
#define ORDER_INSIDE 1
#define ORDER_DOWN 2
#define NO_ORDERS -1
#define HARDWARE_NUMBER_OF_ORDER_BUTTONS 3
#define HARDWARE_NUMBER_OF_FLOORS 4




/**
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


