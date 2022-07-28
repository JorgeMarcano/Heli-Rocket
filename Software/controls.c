#include "controls.h"

#include "hardware/pwm.h"

// Turn 0.1% accuracy into proper PWM duty cycle value
#define DUTY_MIN    1000
#define DUTY_MAX    2000
uint16_t duty_cycle(uint permille);

// Setup a ctrl
err setup_ctrl(Ctrl_setup* setup) {
    // TODO: Setup PWM for this pin
    gpio_set_function(setup->pin, GPIO_FUNC_PWM);

    // Get PWM slice for this pin
    uint slice = pwm_gpio_to_slice_num(setup->pin);
    uint channel = pwm_gpio_to_channel(setup->pin);

    // TODO: Get frequency, if not matching, set proper freq
    // Set to the correct frequency

    // Setup to the correct value for this channel
    pwm_set_chan_level(slice, channel, duty_cycle(setup->init_value));

    // Start PWM if not already started
    pwm_set_enabled(slice, true);

    return SUCC;
}

// Set Ctrl Throttle
err set_ctrl(uint pin, uint value) {
    uint slice = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);
    
    pwm_set_chan_level(slice, channel, duty_cycle(value));

    return SUCC;
}

// Get Ctrl Throttle
uint get_ctrl(uint pin) {
    // TODO: Get PWM value for pin
    return 0;
}

// Turn 0.1% accuracy into proper PWM duty cycle value
uint16_t duty_cycle(uint permille) {
    uint16_t returnVal = permille;
    returnVal += DUTY_MIN;
    return returnVal > DUTY_MAX ? DUTY_MAX : returnVal;
}