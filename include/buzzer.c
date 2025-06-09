#include "buzzer.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "FreeRTOS.h"
#include "task.h"

static volatile bool buzzer_suspended = false;
static uint slice_num;
static uint channel;

void buzzer_init(void)
{
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    channel = pwm_gpio_to_channel(BUZZER_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);
    pwm_set_chan_level(slice_num, channel, 0);
}

void buzzer_task(void *pvParameters)
{
    buzzer_init();

    while (true)
    {
        if (!buzzer_suspended)
        {
            pwm_set_chan_level(slice_num, channel, 125);
            pwm_set_wrap(slice_num, 250);
            vTaskDelay(pdMS_TO_TICKS(100));
            pwm_set_chan_level(slice_num, channel, 0);
            vTaskDelay(pdMS_TO_TICKS(900));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

void suspend_buzzer_task(void)
{
    buzzer_suspended = true;
    pwm_set_chan_level(slice_num, channel, 0);
}

void resume_buzzer_task(void)
{
    buzzer_suspended = false;
}