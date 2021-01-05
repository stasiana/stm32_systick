#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

static volatile int xxx = 0;

void sys_tick_handler(void) {
  xxx++;
  if (xxx == 100) {
    xxx = 0;
    gpio_toggle(GPIOC, GPIO13);
  }
}

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {

  rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);

  while (true) {
    __asm__("nop");
  }

  return 0;
}
