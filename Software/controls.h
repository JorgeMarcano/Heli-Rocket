#ifndef CONTROLS_H
#define CONTROLS_H

#include "globals.h"

#define SERVO_NEUTRAL 1000

const uint motor_pin    = 100;
const uint servo_pin[4] = {101, 102, 103, 104};

typedef struct Ctrl_setup {
    uint pin;
    uint init_value;
} Ctrl_setup;

// Setup a ctrl
err setup_ctrl(Ctrl_setup* setup);

// Set Ctrl Throttle
err set_ctrl(uint pin, uint value);

// Get Ctrl Throttle
uint get_ctrl(uint pin);

#endif