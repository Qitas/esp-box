#include <string.h>
#include "esp_log.h"
#include "bsp_board.h"
#include "bsp_i2s.h"
#include "bsp_codec.h"
#include "button.h"
#include "bsp_btn.h"
#include "bsp_storage.h"
#include "tca9554.h"

// static const char *TAG = "doorlock";

#define BOARD_SI522A_ADDR       0x29        // 0x2f //  0x28
#define BOARD_ES8311_ADDR       0x18


static const board_button_t g_btns[] = {
    {BOARD_BTN_ID_BOOT, 0, GPIO_NUM_0,   0},    //按下为低电平        
    {BOARD_BTN_ID_PREV, 0, GPIO_NUM_17,  1},    //按下为高电平
};


/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
********************************************************************************/
static const board_res_desc_t g_board_lock_res = 
{
    .FUNC_LCD_EN =     (1),
    .GPIO_LCD_RST = GPIO_NUM_NC,
    .GPIO_LCD_CLK = GPIO_NUM_48,
    .GPIO_LCD_DIN = GPIO_NUM_47,
    .GPIO_LCD_DC = GPIO_NUM_38,
    .GPIO_LCD_CS = GPIO_NUM_37,
    .LCD_BUS_WIDTH =   (1),
    .LCD_IFACE_SPI =   (1),
    .LCD_HOST = SPI2_HOST,
    .LCD_CMD_BITS =8    ,
    .LCD_PARAM_BITS=8   ,
    // .LCD_DISP_IC_STR = "st7789",
    .LCD_FREQ =        (40 * 1000 * 1000),
    .LCD_SWAP_XY =     (1),
    .LCD_MIRROR_X =    (1),
    .LCD_MIRROR_Y =    (false),
    .LCD_COLOR_INV =   (false),
    .BSP_INDEV_IS_TP =         (1),
    .TOUCH_PANEL_SWAP_XY =     (0),
    .TOUCH_PANEL_INVERSE_X =   (0),
    .TOUCH_PANEL_INVERSE_Y =   (0),
    .LCD_WIDTH =       (240),
    .LCD_HEIGHT =      (320),
    .LCD_COLOR_SPACE = ESP_LCD_COLOR_SPACE_RGB,

    .GPIO_LCD_BL =     (GPIO_NUM_NC),
    .GPIO_LCD_BL_ON =  (0),

    .BSP_BUTTON_EN =  (1),
    .BUTTON_TAB =  g_btns,
    .BUTTON_TAB_LEN = sizeof(g_btns) / sizeof(g_btns[0]),

    .FUNC_I2C_EN =     (1),
    .GPIO_I2C_SCL =    (GPIO_NUM_13),
    .GPIO_I2C_SDA =    (GPIO_NUM_14),

    .FUNC_SDMMC_EN =   (1),
    .SDMMC_BUS_WIDTH = (1),
    .GPIO_SDMMC_CLK =  (GPIO_NUM_35),
    .GPIO_SDMMC_CMD =  (GPIO_NUM_36),
    .GPIO_SDMMC_D0 =   (GPIO_NUM_45),
    .GPIO_SDMMC_D1 =   (GPIO_NUM_NC),
    .GPIO_SDMMC_D2 =   (GPIO_NUM_NC),
    .GPIO_SDMMC_D3 =   (GPIO_NUM_NC),
    .GPIO_SDMMC_DET =  (GPIO_NUM_NC),

    .FUNC_I2S_EN =         (1),
    .GPIO_I2S_LRCK =       (GPIO_NUM_39),
    .GPIO_I2S_MCLK =       (GPIO_NUM_1),
    .GPIO_I2S_SCLK =       (GPIO_NUM_41),
    .GPIO_I2S_SDIN =       (GPIO_NUM_40),
    .GPIO_I2S_DOUT =       (GPIO_NUM_42),

    // .EXPANDER_IO_EN =       (1),
    .FUNC_PWR_CTRL =        (1),
    .GPIO_PWR_CTRL =        (GPIO_NUM_NC),
    .GPIO_PWR_ON_LEVEL =    (1),

    .GPIO_MUTE_NUM =   GPIO_NUM_NC,
    .GPIO_MUTE_LEVEL = 1,
};
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
********************************************************************************/
esp_err_t bsp_board_doorlock_detect(void)
{
    esp_err_t ret = ESP_OK;
    // ret = bsp_i2c_probe_addr(BOARD_SI522A_ADDR); 
    // ESP_LOGI(TAG, "SI522A status x%x",ret);
    // ret |= bsp_i2c_probe_addr(TCA9554_ADDR);  
    // ESP_LOGI(TAG, "tca9554 status x%x",ret);
    // ret |= bsp_i2c_probe_addr(BOARD_ES8311_ADDR); 
    // ESP_LOGI(TAG, "ES8311 status x%x\n",ret);
    return ESP_OK == ret ? ESP_OK : ESP_FAIL;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
********************************************************************************/
#define TOUCH_BL_LED     46
esp_err_t bsp_board_doorlock_init(void)
{
    /*!< Mute_Button on ESP32-S3-Box */
    // gpio_config_t io_conf_key;
    // io_conf_key.intr_type = GPIO_INTR_ANYEDGE;
    // io_conf_key.mode = GPIO_MODE_INPUT;
    // io_conf_key.pin_bit_mask = 1ULL << g_board_s3_box_res.GPIO_MUTE_NUM;
    // io_conf_key.pull_down_en = GPIO_PULLDOWN_DISABLE;
    // io_conf_key.pull_up_en = GPIO_PULLUP_ENABLE;
    // ESP_ERROR_CHECK(gpio_config(&io_conf_key));
    // gpio_install_isr_service(0);
    // ESP_ERROR_CHECK(gpio_isr_handler_add(g_board_s3_box_res.GPIO_MUTE_NUM, mute_btn_handler, NULL));
    // ESP_LOGI(TAG, "doorlock init");
    ESP_ERROR_CHECK(tca9554_init(0x0,0x4F));
    ESP_ERROR_CHECK(bsp_btn_init_default());
    tca9554_set_level(EXPANDER_IO_SD_CTRL, 0);
    tca9554_set_level(EXPANDER_IO_BAT_LED, 1);
    ESP_ERROR_CHECK(bsp_sdcard_init_default());
    // ESP_LOGI(TAG, "bsp_i2s_init");
    // ESP_ERROR_CHECK(bsp_i2s_init(I2S_NUM_0, 16000));
    // ESP_ERROR_CHECK(bsp_codec_init(AUDIO_HAL_16K_SAMPLES));
    tca9554_set_level(EXPANDER_IO_AUDIO_CTRL, 0);
    // vTaskDelay(pdMS_TO_TICKS(10));
    tca9554_set_level(EXPANDER_IO_PA_CTRL, 1);
    gpio_config_t led_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask =  BIT64(TOUCH_BL_LED)
    };
    gpio_config (&led_conf);
     gpio_set_level(TOUCH_BL_LED, 1);
    return ESP_OK;
}


esp_err_t bsp_board_doorlock_power_ctrl(power_module_t module, bool on)
{
    /* Control independent power domain */
    switch (module) {
    case POWER_MODULE_UVC:
        tca9554_set_level(EXPANDER_IO_CAM_CTRL, !on);
        break;
    case POWER_MODULE_LCD:
        tca9554_set_level(EXPANDER_IO_LCD_CTRL, !on);
        break;
    case POWER_MODULE_LED:
        tca9554_set_level(EXPANDER_IO_BAT_LED, on);
        break;
    case POWER_MODULE_BL:
        gpio_set_level(TOUCH_BL_LED, on);
        break;
    case POWER_MODULE_SD:
        tca9554_set_level(EXPANDER_IO_SD_CTRL, !on);
        break;
    case POWER_MODULE_AUDIO:
        tca9554_set_level(EXPANDER_IO_PA_CTRL, on);
        tca9554_set_level(EXPANDER_IO_AUDIO_CTRL, !on);
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}

const board_res_desc_t *bsp_board_doorlock_get_res_desc(void)
{
    return &g_board_lock_res;
}


