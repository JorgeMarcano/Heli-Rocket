#ifndef PID_H
#define PID_H

#include "globals.h"

typedef struct State {
    uint x_tilt;
    uint x_speed;
    uint y_tilt;
    uint y_speed;
    uint z_pos;
    uint z_speed;
    uint ang_speed;     // spin
} State;

typedef struct Response {
    uint servos[SERVO_COUNT];
    uint throttle;
} Response;

// Proportionality cst
#define K_P     10
// Derivative cst
#define K_D     1

// Get PID
err pid(State* curr_state, State* goal, Response* reponse);

#endif