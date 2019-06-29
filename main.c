#include <cmsis_boot/stm32f10x.h>
#include <stm_lib/inc/stm32f10x_rcc.h>
#include <stm_lib/inc/stm32f10x_gpio.h>
#include <stm_lib/inc/stm32f10x_tim.h>
#include <stm_lib/inc/misc.h>

#include <stdio.h>

#include <tic120.h>

void led_init();
void delay();

int main(void) {
    led_init();

    tic120_init();
    tic120_clear();
    tic120_write_string_pos("Hello", 5, 0);
    tic120_write_string_pos("world!", 15, 1);

    u32 cnt = 0;
    while(1) {
        delay();
        GPIOC->ODR ^= GPIO_Pin_13;
        tic120_printf("%d", 5, 3, cnt++);
    }
}

/**
 * @brief  Delay loop.
 */
void delay() {
    for(u32 i = 0; i < 1000000; i++) {
    }
}

/**
 * @brief  Initializes the LED.
 */
void led_init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOC->ODR |= GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
