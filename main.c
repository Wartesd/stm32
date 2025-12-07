#include <stdint.h>
#include "stm32f10x.h"


void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;     

        
        GPIOC->ODR ^= (1U << 13);
    }
}

int main(void)
{
    
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 

 
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x1 << 20);

   
    GPIOB->CRL &= ~(0xF << 0);
    GPIOB->CRL |=  (0x2 << 2);  
    GPIOB->ODR |=  (1U << 0);   

    
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1RSTR |=  RCC_APB1RSTR_TIM2RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;

    
    TIM2->PSC = 40000 - 1;  
    TIM2->ARR = 500 - 1;    

    
    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);

   
    TIM2->CR1 |= TIM_CR1_CEN;

    
    uint8_t btn_prev = 1;
    uint32_t debounce = 0;

    while (1)
    {
        uint8_t raw = (GPIOB->IDR & (1U << 0)) ? 1 : 0;
        uint8_t pressed = raw ? 0 : 1;  

        if (pressed != btn_prev) {
            debounce = 0;
        } else {
            if (debounce++ > 3000) {
                if (pressed == 1) {
                    
                    TIM2->PSC <<= 1;
                    if (TIM2->PSC > 500000)
                        TIM2->PSC = 1000;
                }
            }
        }

        btn_prev = pressed;
    }
}
