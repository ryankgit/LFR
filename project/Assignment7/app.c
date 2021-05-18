/*******************************************************************************
 * Ryan Kirsch
 * CSCI 469 - Embedded Systems Design
 * 4/15/21
 * Assignment 7 - Final project (Line following robot)
 *
 ******************************************************************************/
#include "sl_emlib_gpio_init_BTN_config.h"
#include "sl_emlib_gpio_init_LED_config.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"
#include "stdio.h"
#include "sl_sleeptimer.h"

#include "sl_emlib_gpio_init_motor_driver_enable_config.h"  // PC03: enable motor driver
// motor control pins
#include "sl_emlib_gpio_init_right_motor_fw_config.h"       // PB00: right motor forward
#include "sl_emlib_gpio_init_right_motor_fw_bw_config.h"    // PB04: right motor forward, backward
#include "sl_emlib_gpio_init_left_motor_fw_config.h"        // PC06: left motor forward
#include "sl_emlib_gpio_init_left_motor_fw_bw_config.h"     // PB03: left motor forward, backward
// IR sensor control pins
#include "sl_emlib_gpio_init_right_sensor_input_config.h"   // PB01: right IR phototransistor sensor
#include "sl_emlib_gpio_init_right_led_control_config.h"    // PD02: right IR LED control
#include "sl_emlib_gpio_init_left_sensor_input_config.h"    // PC02: left IR phototransistor sensor
#include "sl_emlib_gpio_init_left_led_control_config.h"     // PC01: left IR LED control

// function definitions
void correct_right(void);
void correct_left(void);
void forward_movement(void);
void stop_movement(void);
void update_IR_sensors(void);
void on_btn_press(uint8_t pin);

bool start;
uint8_t right_sensor;
uint8_t left_sensor;
sl_sleeptimer_timer_handle_t timer;

/*******************************************************************************
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
    GPIO_ExtIntConfig(SL_EMLIB_GPIO_INIT_BTN_PORT, SL_EMLIB_GPIO_INIT_BTN_PIN, SL_EMLIB_GPIO_INIT_BTN_PIN, false, true, true);
    // init GPIOINT driver
    GPIOINT_Init();
    // register BTN callback function
    GPIOINT_CallbackRegister(SL_EMLIB_GPIO_INIT_BTN_PIN, on_btn_press);
}

/*******************************************************************************
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
    // wait for button press interrupt before starting
    __WFI();

    // initial assignment of IR sensor values
    update_IR_sensors();

    while (start)
    {
        // if both sensors are reflecting, go straight
        if (!right_sensor && !left_sensor)
        {
            forward_movement();
        }
        // if the right sensor is not reflecting, make a slight-right correction
        if (right_sensor && !left_sensor)
        {
            correct_right();
        }
        // if the left sensor is not reflecting, make a slight-left correction
        if (!right_sensor && left_sensor)
        {
            correct_left();
        }
        // if neither sensors are reflecting, stop
        if (right_sensor && left_sensor)
        {
            stop_movement();
        }
    }
}

/*****************************************************************************
 * Motor controls.
 ******************************************************************************/
void correct_right(void)
{
    stop_movement();
    // allot time for motors to stop
    sl_sleeptimer_delay_millisecond(65);

    // left motor forward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PIN);
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PIN);

    // right motor backward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PIN);

    // turn for 25ms
    sl_sleeptimer_delay_millisecond(23);
    // clear motor pins, update IR sensors
    stop_movement();
}

void correct_left(void)
{
    stop_movement();
    // allot time for motors to stop
    sl_sleeptimer_delay_millisecond(65);

    // right motor forward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PIN);
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PIN);

    // left motor backward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PIN);

    // turn for 25ms
    sl_sleeptimer_delay_millisecond(23);
    // clear motor pins, update IR sensors
    stop_movement();
}

void forward_movement(void)
{
    // stop and delay to prevent motors from going too fast and overshooting turns
    stop_movement();
    // allot time for motors to stop
    sl_sleeptimer_delay_millisecond(65);

    // set right motor forward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PIN);
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PIN);
    // set left motor forward
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PIN);
    GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PIN);

    // go forward for 17ms
    // note: increase time to increase speed
    // note: if this delay is not here the robot will never move forward
    sl_sleeptimer_delay_millisecond(17);
    // check IR sensors after moving forward
    update_IR_sensors();
}

void stop_movement(void)
{
    // clear right motor pins
    GPIO_PinOutClear(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PIN);
    GPIO_PinOutClear(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PIN);
    // clear left motor pins
    GPIO_PinOutClear(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PIN);
    GPIO_PinOutClear(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PORT, SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PIN);

    // check IR sensors now that motors have stopped
    // robot could have been moving too fast to take in readings
    update_IR_sensors();
}

/*****************************************************************************
 * Update left and right IR phototransistor values.
 ******************************************************************************/
void update_IR_sensors(void)
{
    right_sensor = GPIO_PinInGet(SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_PORT, SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_PIN);
    left_sensor = GPIO_PinInGet(SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_PORT, SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_PIN);
}

/*****************************************************************************
 * Button ISR.
 ******************************************************************************/
void on_btn_press(uint8_t pin)
{
    // toggle motor driver pin
    GPIO_PinOutToggle(SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_PORT, SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_PIN);

    // toggle right and left IR LED pins
    GPIO_PinOutToggle(SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_PORT, SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_PIN);
    GPIO_PinOutToggle(SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_PORT, SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_PIN);

    // toggle mikrocontroller LED to indicate running program
    GPIO_PinOutToggle(SL_EMLIB_GPIO_INIT_LED_PORT, SL_EMLIB_GPIO_INIT_LED_PIN);

    // toggle start boolean
    start = !start;
    // wake-up CPU
    (void) pin;
}
