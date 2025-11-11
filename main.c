#include "stm32f10x.h"
#include <stdint.h>

static inline void delay(volatile uint32_t d) {
    while (d--) __NOP();
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x1 << 20);

    GPIOB->CRL &= ~(0xF << 0);
    GPIOB->CRL |=  (0x2 << 2);   // input with pull-up/pull-down
    GPIOB->ODR &= ~(1U << 0);    // pull-down

    const uint32_t SLOW = 600000;
    const uint32_t FAST = 200000;
    uint32_t delay_time = SLOW;

    while (1) {
        uint8_t pressed = (GPIOB->IDR & (1U << 0)) ? 1 : 0;

        if (pressed) delay_time = FAST;
        else delay_time = SLOW;

        GPIOC->ODR ^= (1U << 13);
        delay(delay_time);
    }
}
