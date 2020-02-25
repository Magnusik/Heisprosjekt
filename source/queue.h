#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"



/**
 * Lagt til fra refactoring
 */
void queue_add_order(int floor, int order_type);




/**
 * Lagt til fra refactoring
 */
void queue_remove_order(int floor, int order_type);


/**
 * Lagt til fra refactoring
 */
int queue_check_order(int floor, int order_type);



/**
 * @file
 * @brief Checks for orders in @p order_button_matrix.
 * 
 * @return Floor where the order was given, -1 if no orders.
 */
int queue_check_orders_waiting();




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






void print_matrix();

#endif


