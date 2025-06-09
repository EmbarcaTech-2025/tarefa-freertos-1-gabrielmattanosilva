#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "include/rgb_led.h"

int main()
{
  stdio_init_all();

  xTaskCreate(rgb_led_task, "RGB_LED_Task", 256, NULL, 1, NULL);
  vTaskStartScheduler();

  while (1)
  {
  };
}