#include "sl_emlib_gpio_simple_init.h"
#include "sl_emlib_gpio_init_BTN_config.h"
#include "sl_emlib_gpio_init_LED_config.h"
#include "sl_emlib_gpio_init_left_led_control_config.h"
#include "sl_emlib_gpio_init_left_motor_fw_config.h"
#include "sl_emlib_gpio_init_left_motor_fw_bw_config.h"
#include "sl_emlib_gpio_init_left_sensor_input_config.h"
#include "sl_emlib_gpio_init_motor_driver_enable_config.h"
#include "sl_emlib_gpio_init_right_led_control_config.h"
#include "sl_emlib_gpio_init_right_motor_fw_config.h"
#include "sl_emlib_gpio_init_right_motor_fw_bw_config.h"
#include "sl_emlib_gpio_init_right_sensor_input_config.h"
#include "em_gpio.h"
#include "em_cmu.h"

void sl_emlib_gpio_simple_init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_BTN_PORT,
                  SL_EMLIB_GPIO_INIT_BTN_PIN,
                  SL_EMLIB_GPIO_INIT_BTN_MODE,
                  SL_EMLIB_GPIO_INIT_BTN_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_LED_PORT,
                  SL_EMLIB_GPIO_INIT_LED_PIN,
                  SL_EMLIB_GPIO_INIT_LED_MODE,
                  SL_EMLIB_GPIO_INIT_LED_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_PORT,
                  SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_PIN,
                  SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_MODE,
                  SL_EMLIB_GPIO_INIT_LEFT_LED_CONTROL_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PORT,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_PIN,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_MODE,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PORT,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_PIN,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_MODE,
                  SL_EMLIB_GPIO_INIT_LEFT_MOTOR_FW_BW_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_PORT,
                  SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_PIN,
                  SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_MODE,
                  SL_EMLIB_GPIO_INIT_LEFT_SENSOR_INPUT_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_PORT,
                  SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_PIN,
                  SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_MODE,
                  SL_EMLIB_GPIO_INIT_MOTOR_DRIVER_ENABLE_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_PORT,
                  SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_PIN,
                  SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_MODE,
                  SL_EMLIB_GPIO_INIT_RIGHT_LED_CONTROL_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PORT,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_PIN,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_MODE,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PORT,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_PIN,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_MODE,
                  SL_EMLIB_GPIO_INIT_RIGHT_MOTOR_FW_BW_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_PORT,
                  SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_PIN,
                  SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_MODE,
                  SL_EMLIB_GPIO_INIT_RIGHT_SENSOR_INPUT_DOUT);
}
