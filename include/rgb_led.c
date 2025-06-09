#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "rgb_led.h"

const uint8_t LED_PINS[] = {13, 11, 12}; // red, green, blue

void rgb_led_task()
{
  // Inicializa todos os LEDs
  for (uint8_t i = 0; i < 3; i++)
  {
    gpio_init(LED_PINS[i]);
    gpio_set_dir(LED_PINS[i], GPIO_OUT);
  }

  uint8_t current_led = 0;
  while (true)
  {
    // Acende apenas o LED atual
    gpio_put(LED_PINS[current_led], 1);
    vTaskDelay(500);
    gpio_put(LED_PINS[current_led], 0);

    // Passa para o próximo LED
    current_led = (current_led + 1) % 3;
  }
}