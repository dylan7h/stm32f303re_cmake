#include "autoconfig.h"
#include "stm32f3xx.h"

volatile uint32_t gCount_us = 0;

void Drv_Systick_Initialize(uint32_t AHBClockValue)
{
    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
    SysTick->VAL = 0;
    SysTick->LOAD = AHBClockValue / 1000000;
}

void Drv_Systick_Delau_ms(uint32_t ms)
{
    gCount_us = ms * 1000u;

    SysTick->VAL = 0;
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

    while(gCount_us != 0U);

    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void Drv_Systick_Delau_us(uint32_t us)
{
    gCount_us = us;

    SysTick->VAL = 0;
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

    while(gCount_us != 0U);

    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void SysTick_Handler(void)
{
    gCount_us--;
}