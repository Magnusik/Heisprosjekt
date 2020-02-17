#include "elevator_control.h"
#include "hardware.h"

int init_elevator(){
  while(!(hardware_read_floor_sensor(0) || hardware_read_floor_sensor(1) || hardware_read_floor_sensor(2) || hardware_read_floor_sensor(3))){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
  }
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  for (int floor = 0; floor<HARDWARE_NUMBER_OF_FLOORS; floor++){
    if (hardware_read_floor_sensor(floor)){
      int current_floor=floor;
      return current_floor;
    }
  }
  return -1;
}


