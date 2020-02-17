#include "hardware.h"

/**
 * @file 
 * @brief Takes order from user and updates @p p_matrix and sets lights accordingly.
 * 
 * @param p_matrix A pointer to the @p order_button_matrix.
 * 
 * @warning Changes @p order_button_matrix.
 */

void update_new_order(int *p_matrix);
/**
 * @brief Clears all current orders and sets extinguishes all order lights.
 * 
 * @param p_order_matrix A pointer to the @p order_button_matrix.
 * 
 * @warning Changes @p order_button_matrix.
 */

void clear_all_orders(int *p_matrix);

/**
 * @brief Clears all orders on given @p floor in the matrix  that pointer @p p_matrix points to.
 * @param p_matrix A pointer to a matrix
 * @param floor A value that represents the floor of type int
 * @warning changes @p p_matrix and dereferences value pointed to.
 */



void clear_order_on_floor(int *p_matrix, int floor);


