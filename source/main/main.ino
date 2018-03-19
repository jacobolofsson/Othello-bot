enum state {WAITING, AI_THINKING, MAKING_MOVE, READ_BOARD};
enum state current_state;

void setup() {
  current_state = WAITING;

}

void loop() {
  switch(current_state) {
    case WAITING:
      break;
    case AI_THINKING:
      current_state = MAKING_MOVE;
      break;
    case MAKING_MOVE:
      break;
    case READ_BOARD:
      break;
  }

}
