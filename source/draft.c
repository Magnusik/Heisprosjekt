#include <hfiles>

typedef enum {
  Software_state_waiting,
  Software_state_idle,
  Software_state_moving_up,
  Software_state_moving_down,
  Software_state_stop
}Software_state;

int current_floor;


main(){

  int error = hardware_init();
  if(error != 0){
      fprintf(stderr, "Unable to initialize hardware\n");
      exit(1);
  }

  signal(SIGINT, sigint_handler);

  current_floor = init_elevator();
  printf("current floor is: %d\n",current_floor );

  while(1){
    switch(Software_state)
    {
      case Software_state_waiting:

        break;
      case Software_state_idle:

        break;
      case Software_state_moving_up:

        break;
      case Software_state_moving_down:

        break;
      case Software_state_stop:
        break;
    }
  }

  return 0;
}
