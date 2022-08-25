
#include "esp_log.h"
#include "bsp_i2c.h"
#include "esp_check.h"
#include "bsp_board.h"
#include "tca9554.h"

static const char *TAG = "tca9554a";


static i2c_bus_device_handle_t tca9554_handle = NULL;

static uint8_t outlevel_reg = 0;
static uint8_t direction_reg = 0;

static esp_err_t tca9554_read_byte(uint8_t reg_addr, uint8_t *data)
{
    return i2c_bus_read_byte(tca9554_handle, reg_addr, data);
}

static esp_err_t tca9554_write_byte(uint8_t reg_addr, uint8_t data)
{
    return i2c_bus_write_byte(tca9554_handle, reg_addr, data);
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
********************************************************************************/
esp_err_t tca9554_init(uint8_t direct,uint8_t level)
{
    esp_err_t ret = ESP_OK;
    if (NULL != tca9554_handle) {
        return ESP_FAIL;
    }
    bsp_i2c_add_device(&tca9554_handle, TCA9554_ADDR);
    if (NULL == tca9554_handle) {
        return ESP_FAIL;
    }
    direction_reg = direct;
    outlevel_reg = level;
    ret |= tca9554_write_byte(TCA9554_DIRECTION_REG, direction_reg);
    ret |= tca9554_write_byte(TCA9554_OUTPUT_STATUS_REG, outlevel_reg);
    // ESP_LOGW(TAG, "0x%02x 0x%02x",direction_reg,outlevel_reg);
    return ESP_OK == ret ? ESP_OK : ESP_FAIL;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
********************************************************************************/
esp_err_t tca9554_set_direction(uint8_t pin, bool is_output)
{
    ESP_RETURN_ON_FALSE(NULL != tca9554_handle, ESP_FAIL, TAG, "tca9554 is not initialized");
    ESP_RETURN_ON_FALSE(pin < 8, ESP_FAIL, TAG, "pin is invailed");
    if (is_output) {
        direction_reg &= ~BIT(pin);
    } else {
        direction_reg |= BIT(pin);
    }
    ESP_LOGW(TAG, "tca9554 direction 0x%02x ",direction_reg);
    return tca9554_write_byte(TCA9554_DIRECTION_REG, direction_reg);
}

esp_err_t tca9554_set_level(uint8_t bit, bool level)
{
    ESP_RETURN_ON_FALSE(NULL != tca9554_handle, ESP_FAIL, TAG, "tca9554 is not initialized");
    ESP_RETURN_ON_FALSE(bit < 8, ESP_FAIL, TAG, "pin is invailed");
    if (level) {
        outlevel_reg |= BIT(bit);
    } else {
        outlevel_reg &= ~BIT(bit);
    }
    // ESP_LOGW(TAG, "tca9554 outlevel 0x%02x ",outlevel_reg);
    return tca9554_write_byte(TCA9554_OUTPUT_STATUS_REG, outlevel_reg);
}

esp_err_t tca9554_set_inversion(uint8_t bit)
{
    ESP_RETURN_ON_FALSE(NULL != tca9554_handle, ESP_FAIL, TAG, "tca9554 is not initialized");
    ESP_RETURN_ON_FALSE(bit < 8, ESP_FAIL, TAG, "pin is invailed");
    return tca9554_write_byte(TCA9554_INVERSION_REG, BIT(bit));
}

esp_err_t tca9554_read_output_pins(uint8_t *pin_val)
{
    ESP_RETURN_ON_FALSE(NULL != tca9554_handle, ESP_FAIL, TAG, "tca9554 is not initialized");
    esp_err_t ret = tca9554_read_byte(TCA9554_OUTPUT_STATUS_REG, &outlevel_reg);
    *pin_val = outlevel_reg;
    return ret;
}

esp_err_t tca9554_read_input_pins(uint8_t *pin_val)
{
    ESP_RETURN_ON_FALSE(NULL != tca9554_handle, ESP_FAIL, TAG, "tca9554 is not initialized");
    return tca9554_read_byte(TCA9554_INPUT_STATUS_REG, pin_val);
}

