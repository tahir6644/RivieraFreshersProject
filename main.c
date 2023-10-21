#include <stdio.h>
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#include "mcp9808.h"

#define SDA_PIN GPIO_NUM_21
#define SCL_PIN GPIO_NUM_22
#define clkspd 400000

void app_main(void)
{
  // Initialize I2C Communication
  i2c_config_t i2c_config = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = SDA_PIN,
      .scl_io_num = SCL_PIN,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = clkspd};

  i2c_param_config(I2C_NUM_0, &i2c_config);
  i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

  mcp9808_config_t mcp_config;
  mcp_config.address = 0x18;
  mcp_config.i2c_num = I2C_NUM_0;

  mcp9808_handle_t mcp;
  uint16_t mcp_manuf_id;
  uint16_t mcp_device_id;

  if (mcp9808_init(&mcp_config, &mcp, &mcp_manuf_id, &mcp_device_id) != ESP_OK)
    {
        return;
    }

    float temperature;

    if (mcp9808_ambient_temp(mcp, &temperature) != ESP_OK)
    {
        return;
    }

    ESP_LOGI("TAG", "Temperature: %f", temperature);
    esp_log_level_set("TAG", ESP_LOG_INFO);

    mcp9808_delete(mcp);
}