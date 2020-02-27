/**
 * @file
 * @brief Timer module.
 * 
 * Functions for keeping track of time.
 */

#ifndef TIMER_H
#define TIMER_H
#include <time.h> 
#include <stdio.h> 
#include <unistd.h>


/**
 * @file
 * @brief Starts timer.  
 */
void timer_start();

/**
 * @brief Checks if 3 seconds have passed since timer_start() were last called.
 * 
 * @return 1 if 3 seconds have passed, 0 if not.
 */
int timer_has_elapsed();

/**
 * @brief Stops timer.
 */
void timer_stop();

#endif