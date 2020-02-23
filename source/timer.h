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
void start_timer();

/**
 * @brief Checks if 3 seconds have passed since start_timer() were last called.
 * 
 * @return 1 if 3 seconds have passed, 0 if not.
 */
int has_timer_elapsed();

/**
 * @brief Stops timer.
 */
void stop_timer();

int is_timer_active(); //Muligens fjerne?
#endif