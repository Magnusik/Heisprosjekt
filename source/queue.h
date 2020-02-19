#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"

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



void queue_clear_order_on_floor(int *p_matrix, int floor);


#endif


