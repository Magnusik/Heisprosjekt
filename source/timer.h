#ifndef TIMER_H
#define TIMER_H
#include <time.h> 
#include <stdio.h> 
#include <unistd.h>

/**
 * @file
 * @brief 1 if timer is active, 0 if timer is inactive.
 */
int timer_active;

/**
 * @brief A time reference.
 */
time_t time_stamp;


/**
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