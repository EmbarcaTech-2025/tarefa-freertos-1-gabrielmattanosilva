#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "FreeRTOS.h"
#include "task.h"
#include "buttons.h"
#include "rgb_led.h"
#include "buzzer.h"

/* Handles das tarefas */
TaskHandle_t rgb_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;

/* Variáveis de estado */
static bool led_suspended = false;
static bool buzzer_suspended = false;

/* Callback para o botão A (controle do LED) */
static void button_a_handler(void)
{
  if (led_suspended)
  {
    resume_led_task();
    printf("LED Task resumed\n");
  }
  else
  {
    suspend_led_task();
    printf("LED Task suspended\n");
  }
  led_suspended = !led_suspended;
}

/* Callback para o botão B (controle do buzzer) */
static void button_b_handler(void)
{
  if (buzzer_suspended)
  {
    resume_buzzer_task();
    printf("Buzzer Task resumed\n");
  }
  else
  {
    suspend_buzzer_task();
    printf("Buzzer Task suspended\n");
  }
  buzzer_suspended = !buzzer_suspended;
}

/* Função principal */
int main(void)
{
  /* Inicializações básicas */
  stdio_init_all();

  /* Configuração dos botões */
  buttons_init();
  register_button_a_callback(button_a_handler);
  register_button_b_callback(button_b_handler);
  printf("Buttons initialized!\n");

  /* Criação das tarefas */
  xTaskCreate(rgb_led_task,
              "RGB Task",
              256,
              NULL,
              1,
              &rgb_task_handle);

  xTaskCreate(buzzer_task,
              "Buzzer Task",
              256,
              NULL,
              1,
              &buzzer_task_handle);

  /* Inicia o escalonador */
  printf("Starting scheduler...\n");
  vTaskStartScheduler();

  /* Nunca deverá chegar aqui */
  while (true)
  {
    printf("ERROR: Scheduler exited!\n");
    sleep_ms(1000);
  }
}