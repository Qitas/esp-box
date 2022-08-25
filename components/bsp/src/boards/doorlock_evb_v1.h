#pragma once

#include "esp_err.h"
#include "bsp_board.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t bsp_board_doorlock_detect(void);

esp_err_t bsp_board_doorlock_init(void);

esp_err_t bsp_board_doorlock_power_ctrl(power_module_t module, bool on);

const board_res_desc_t *bsp_board_doorlock_get_res_desc(void);

#ifdef __cplusplus
}
#endif
