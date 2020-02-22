#ifndef TIMER_H
#define TIMER_H
#include <time.h> 
#include <stdio.h> 
#include <unistd.h>

int timerActive;
time_t timestamp;

void start_timer();

int has_timer_elapsed();

void stop_timer();

int is_timer_active();
#endif