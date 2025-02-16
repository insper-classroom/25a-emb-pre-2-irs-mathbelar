#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int botao_stats= 0;
volatile int botao_mudou =0;


void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    botao_stats = 1;
  } else if (events == 0x8) { // rise edge
    botao_stats = 0;
  }


  botao_mudou = 1;
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {

    if(botao_mudou){
      // reseta estado do botao para o codigo verificar tudo de novo e ver se ta fall ou rise
      botao_mudou = 0;

      if (botao_stats){
        printf("fall \n");

      }
      if(!botao_stats){
        printf("rise \n");
      }
    }
  }
}
