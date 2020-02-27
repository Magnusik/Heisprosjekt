

hardware_command_movement(elevator_movement);
hardware_command_stop_light(ON);

while(hardware_read_stop_signal()){

    
}
hardware_command_stop_light(OFF);
