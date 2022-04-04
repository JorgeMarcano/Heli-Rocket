#include <stdio.h>

#include "globals.h"
#include "controls.h"
#include "pid.h"

int main() {
    stdio_init_all();

    // Initialize all motors and servos to neutral
    Ctrl_setup* ctrl_setup = malloc(sizeof(Ctrl_setup));
    ctrl_setup->pin = motor_pin;
    ctrl_setup->init_value = 0;
    if (setup_ctrl(ctrl_setup) != SUCC) {
        printf("Error Initializing motor\n");
        while (true);
    }

    ctrl_setup->init_value = SERVO_NEUTRAL;
    for (uint i = 0; i < SERVO_COUNT; i++) {
        ctrl_setup->pin = servo_pin[i];
        if (setup_ctrl(ctrl_setup) != SUCC) {
            printf("Error Initializing servo #%d\n", i);
            while (true);
        }
    }

    free(ctrl_setup);
    
    // TODO: Init all sensors

    // TODO: Attach to the control channels of receiver (irq)

    // TODO: Setup sensor channel irq for receiver

    // TODO: Setup all sensors to the sensor channel of receiver

    // In loop, update sensor values
    // Check to see if need to update servos to keep desired heading (PID)
    State* currState = malloc(sizeof(State));
    State* goalState = malloc(sizeof(State));
    Response* resp = malloc(sizeof(Response));
    uint i = 0;
    while (true) {
        // TODO: Update sensors

        // TODO: Form current state from sensor data

        // TODO: Form goal state from receiver data (also a sensor)

        // Get PID for next state, if fails, ignore it
        if (pid(currState, goalState, resp) != SUCC)
            continue;

        // Update controls with new values
        set_ctrl(motor_pin, resp->throttle);

        for (i = 0; i < SERVO_COUNT; i++)
            set_ctrl(servo_pin[i], resp->servos[i]);

        // TODO: Perhaps add log

        // TODO: Perhaps add a delay

    }

    // Should never reach here, but if it does, free all memory
    free(currState);
    free(goalState);
    free(resp);
}