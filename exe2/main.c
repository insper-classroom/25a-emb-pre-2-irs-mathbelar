#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int const botao = 28;
int const led = 4;

volatile int led_status = 0;


void led_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { 
    led_status = !led_status;
  }


}

int main() {
  stdio_init_all();

  gpio_init(botao);
  gpio_set_dir(botao,GPIO_IN);
  gpio_pull_up(botao);

  gpio_set_irq_enabled_with_callback(
    botao, GPIO_IRQ_EDGE_FALL, true, &led_callback);

  gpio_init(led);
  gpio_set_dir(led,GPIO_OUT);


  while (true) {
    if(led_status == 1){
      gpio_put(led,1);
    }
    if(led_status == 0 ){
      gpio_put(led,0);
    }
  }
}
