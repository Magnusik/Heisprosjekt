#include "hardware.h"

/**
 * @file 
 * @brief Takes order from user and updates @p order_button_matrix and sets lights accordingly.
 * 
 * @param p_order_matrix A pointer to the @p order_button_matrix.
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


