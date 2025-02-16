#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int botao_vermelho = 28;
const int botao_verde = 26;
const int led_vermelho = 4;
const int led_verde = 6;

volatile int led_r_status = 0;
volatile int led_g_status = 0;

void btn_callback(uint gpio, uint32_t events){
  if(events == 0x4){// queda do botao
    led_r_status = !led_r_status;
  }
  if(events == 0x8){
    led_g_status = !led_g_status;
  }




}


int main() {
  stdio_init_all();

  gpio_init(botao_vermelho);
  gpio_set_dir(botao_vermelho, GPIO_IN);
  gpio_pull_up(botao_vermelho);

  gpio_init(botao_verde);
  gpio_set_dir(botao_verde, GPIO_IN);
  gpio_pull_up(botao_verde);

  gpio_init(led_vermelho);
  gpio_set_dir(led_vermelho,GPIO_OUT);

  gpio_init(led_verde);
  gpio_set_dir(led_verde,GPIO_OUT);

    gpio_set_irq_enabled_with_callback(botao_vermelho, GPIO_IRQ_EDGE_FALL, true,
      &btn_callback);

    gpio_set_irq_enabled(botao_verde, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
      gpio_put(led_vermelho, led_r_status);

      gpio_put(led_verde, led_g_status);
    




  }
}
