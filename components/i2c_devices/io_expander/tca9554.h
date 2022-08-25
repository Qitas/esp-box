#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_bus.h"

#define TCA9554_ADDR                        (0x38)  // IO 扩展
#define TCA9554_INPUT_STATUS_REG            (0x00)
#define TCA9554_OUTPUT_STATUS_REG           (0x01)
#define TCA9554_INVERSION_REG               (0x02)
#define TCA9554_DIRECTION_REG               (0x03)

#define EXPANDER_IO_PA_CTRL             0       //1=ON
#define EXPANDER_IO_MOTOR_A             1
#define EXPANDER_IO_MOTOR_B             2
#define EXPANDER_IO_LCD_CTRL            3       //0=ON 0x08
#define EXPANDER_IO_SD_CTRL             4       //0=ON
#define EXPANDER_IO_BAT_LED             5       //1=ON
#define EXPANDER_IO_CAM_CTRL            6       //0=ON 0x48
#define EXPANDER_IO_AUDIO_CTRL          7       //0=ON

esp_err_t tca9554_init(uint8_t direct,uint8_t level);
esp_err_t tca9554_set_direction(uint8_t pin, bool is_output);
esp_err_t tca9554_set_level(uint8_t bit, bool level);
esp_err_t tca9554_read_output_pins(uint8_t *pin_val);
esp_err_t tca9554_read_input_pins(uint8_t *pin_val);
esp_err_t tca9554_set_inversion(uint8_t bit);
#ifdef __cplusplus
}
#endif
