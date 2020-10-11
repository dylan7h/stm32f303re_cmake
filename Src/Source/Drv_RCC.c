#include "autoconfig.h"
#include "stm32f3xx.h"
#include "Drv_RCC.h"

#ifndef HSI_CLOCK_VALUE
#define HSI_CLOCK_VALUE (8000000U)
#endif  /* HSI_CLOCK_VALUE */

#ifndef HSE_CLOCK_VALUE
#define HSE_CLOCK_VALUE (16000000U)
#endif  /* HSE_CLOCK_VALUE */

static uint32_t Drv_RCC_AHB_GetPrescaleValue(AHBPrescaler_t eAHBPrescaler)
{
    volatile uint32_t AHBPrescalerValue;

    switch (eAHBPrescaler)
    {
    case AHBPrescaler_1:
        AHBPrescalerValue = 1U;
        break;
    case AHBPrescaler_2:
        AHBPrescalerValue = 2U;
        break;
    case AHBPrescaler_4:
        AHBPrescalerValue = 4U;
        break;
    case AHBPrescaler_8:
        AHBPrescalerValue = 8U;
        break;
    case AHBPrescaler_16:
        AHBPrescalerValue = 16U;
        break;
    case AHBPrescaler_64:
        AHBPrescalerValue = 64U;
        break;
    case AHBPrescaler_128:
        AHBPrescalerValue = 128U;
        break;
    case AHBPrescaler_256:
        AHBPrescalerValue = 256U;
        break;
    case AHBPrescaler_512:
        AHBPrescalerValue = 512U;
        break;
    default:
        AHBPrescalerValue = 0U;
        break;
    }

    return AHBPrescalerValue;
}

static uint32_t Drv_RCC_APB_GetPrescaleValue(APBPrescaler_t eAPBPrescaler)
{
    volatile uint32_t APBPrescalerValue;

    switch (eAPBPrescaler)
    {
    case APBPrescaler_1:
        APBPrescalerValue = 1U;
        break;
    case APBPrescaler_2:
        APBPrescalerValue = 2U;
        break;
    case APBPrescaler_4:
        APBPrescalerValue = 4U;
        break;
    case APBPrescaler_8:
        APBPrescalerValue = 8U;
        break;
    case APBPrescaler_16:
        APBPrescalerValue = 16U;
        break;
    default:
        APBPrescalerValue = 0U;
        break;
    }

    return APBPrescalerValue;
}

/* The PLL output frequency must be set in the range 16-72 MHz */
void Drv_RCC_PLL_SetClock(PLLSource_t ePLLSource, PllPreviousDivider_t ePllPreviousDivider, PllMultiplier_t ePllMultiplier)
{
    /* 01. Disable the PLL by setting PLLON to 0. */
    RCC->CR &= ~RCC_CR_PLLON_Msk;

    /* 02. Wait until PLLRDY is cleared. The PLL is now fully stopped. */
    while((RCC->CR & RCC_CR_PLLRDY_Msk) != 0);

    /* 03. Change the desired parameter. */
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC_Msk | RCC_CFGR_PLLMUL_Msk);
    RCC->CFGR |= ((uint32_t)ePLLSource << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)ePllMultiplier << RCC_CFGR_PLLMUL_Pos);

    RCC->CFGR2 &= ~RCC_CFGR2_PREDIV_Msk;
    RCC->CFGR2 |= ((uint32_t)ePllPreviousDivider << RCC_CFGR2_PREDIV_Pos);

    /* 04. Enable the PLL again by setting PLLON to 1. */
    RCC->CR |= RCC_CR_PLLON_Msk;
}

void Drv_RCC_AHB_SetClock(SystemClockSource_t eSystemClockSource, AHBPrescaler_t eAHBPrescaler)
{
    volatile uint32_t AHBPrescalerValue;
    volatile uint32_t SystemClockValue;
    volatile uint32_t TargetAHBClockValue;

    /* Set System Clock Value */
    switch (eSystemClockSource)
    {
    case SystemClockSource_HSI:
        SystemClockValue = HSI_CLOCK_VALUE;
        break;
    case SystemClockSource_HSE:
        SystemClockValue = HSE_CLOCK_VALUE;
        break;
    case SystemClockSource_PLL:
        SystemClockValue = Drv_RCC_PLL_GetClock();
        break;

    default:
        break;
    }

    /* Set AHB Prescale Value */
    AHBPrescalerValue = Drv_RCC_AHB_GetPrescaleValue(eAHBPrescaler);

    /* Calculate Target AHB Clock Value */
    TargetAHBClockValue = SystemClockValue / AHBPrescalerValue;

    /* Set Flash Latency */
    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
    if(TargetAHBClockValue < 24000000U) {
        FLASH->ACR |= (0 << FLASH_ACR_LATENCY_Pos);
    }
    else if(TargetAHBClockValue < 48000000U) {
        FLASH->ACR |= (1 << FLASH_ACR_LATENCY_Pos);
    }
    else {
        FLASH->ACR |= (2 << FLASH_ACR_LATENCY_Pos);
    }

    /* Set AHB Prescaler & Source Clock */
    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_SW_Msk);
    RCC->CFGR |= ((uint32_t)eSystemClockSource << RCC_CFGR_SW_Pos) | ((uint32_t)eAHBPrescaler << RCC_CFGR_HPRE_Pos);
}

void Drv_RCC_APB_SetClock(APBNumber_t eAPBNumber, APBPrescaler_t eAPBPrescaler)
{
    switch (eAPBNumber)
    {
    case APBNumber_1:
        RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
        RCC->CFGR |= ((uint32_t)eAPBPrescaler << RCC_CFGR_PPRE1_Pos);
        break;
    case APBNumber_2:
        RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
        RCC->CFGR |= ((uint32_t)eAPBPrescaler << RCC_CFGR_PPRE2_Pos);
        break;
    default:
        break;
    }
}

uint32_t Drv_RCC_PLL_GetClock(void)
{
    PLLSource_t ePLLSource;
    PllPreviousDivider_t ePllPreviousDivider;
    PllMultiplier_t ePllMultiplier;

    volatile uint32_t SourceClockValue;
    volatile uint32_t DividerValue;
    volatile uint32_t MuliplierValue;

    volatile uint32_t PLLClockValue;

    ePLLSource          = (PLLSource_t)((RCC->CFGR & RCC_CFGR_PLLSRC_Msk) >> RCC_CFGR_PLLSRC_Pos);
    ePllPreviousDivider = (PllPreviousDivider_t)((RCC->CFGR2 & RCC_CFGR2_PREDIV_Msk) >> RCC_CFGR2_PREDIV_Pos);
    ePllMultiplier      = (PllMultiplier_t)((RCC->CFGR & RCC_CFGR_PLLMUL_Msk) >> RCC_CFGR_PLLMUL_Pos);

    if(ePLLSource == PLLSource_HSE) {
        SourceClockValue = HSE_CLOCK_VALUE;
    }
    else {
        SourceClockValue = (ePLLSource == PLLSource_HSI) ? HSI_CLOCK_VALUE : (HSI_CLOCK_VALUE / 2U);
    }

    DividerValue = (uint32_t)ePllPreviousDivider + 1U;

    MuliplierValue = (uint32_t)ePllMultiplier + 2U;

    PLLClockValue = SourceClockValue / DividerValue * MuliplierValue;

    return PLLClockValue;
}

uint32_t Drv_RCC_System_GetClock(void)
{
    volatile SystemClockSource_t eSystemClockSource;
    volatile uint32_t SystemClockValue;

    eSystemClockSource = (volatile SystemClockSource_t)((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos);

    /* Get System Clock Value */
    switch (eSystemClockSource)
    {
    case SystemClockSource_HSI:
        SystemClockValue = HSI_CLOCK_VALUE;
        break;
    case SystemClockSource_HSE:
        SystemClockValue = HSE_CLOCK_VALUE;
        break;
    case SystemClockSource_PLL:
        SystemClockValue = Drv_RCC_PLL_GetClock();
        break;

    default:
        SystemClockValue = 0U;
        break;
    }

    return SystemClockValue;
}

uint32_t Drv_RCC_AHB_GetClock(void)
{
    volatile AHBPrescaler_t eAHBPrescaler;
    volatile uint32_t AHBPrescaleValue;
    volatile uint32_t AHBClockValue;
    volatile uint32_t SystemClockValue;

    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_SWS_Msk);

    eAHBPrescaler = (AHBPrescaler_t)((RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos);

    SystemClockValue = Drv_RCC_System_GetClock();

    AHBPrescaleValue = Drv_RCC_AHB_GetPrescaleValue(eAHBPrescaler);

    AHBClockValue = SystemClockValue / AHBPrescaleValue;

    return AHBClockValue;
}

uint32_t Drv_RCC_APB_GetClock(APBNumber_t eAPBNumber)
{
    volatile uint32_t AHBClockValue;
    volatile uint32_t APBClockValue;
    volatile uint32_t APBPrescaleValue;
    volatile APBPrescaler_t eAPBPrescaler;

    switch (eAPBNumber)
    {
    case APBNumber_1:
        eAPBPrescaler = (APBPrescaler_t)((RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos);
        break;
    case APBNumber_2:
        eAPBPrescaler = (APBPrescaler_t)((RCC->CFGR & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos);
        break;
    default:
        break;
    }

    APBPrescaleValue = Drv_RCC_APB_GetPrescaleValue(eAPBPrescaler);
    AHBClockValue = Drv_RCC_AHB_GetClock();

    APBClockValue = AHBClockValue / APBPrescaleValue;

    return APBClockValue;
}

void Drv_RCC_APB2_ControlPeripheral(BUS_Control_t eBUS_Control, APB2Peripheral_t eAPB2Peripheral)
{
    if(eBUS_Control == BUS_Control_Reset) {
        RCC->APB2RSTR |= (1U << (uint32_t)eAPB2Peripheral);
    }
    else {
        RCC->APB2ENR &= ~(1U << (uint32_t)eAPB2Peripheral);
        RCC->APB2ENR |= ((uint32_t)eBUS_Control << (uint32_t)eAPB2Peripheral);
    }
}

void Drv_RCC_APB1_ControlPeripheral(BUS_Control_t eBUS_Control, APB1Peripheral_t eAPB1Peripheral)
{
    if(eBUS_Control == BUS_Control_Reset) {
        RCC->APB1RSTR |= (1U << (uint32_t)eAPB1Peripheral);
    }
    else {
        RCC->APB1ENR &= ~(1U << (uint32_t)eAPB1Peripheral);
        RCC->APB1ENR |= ((uint32_t)eBUS_Control << (uint32_t)eAPB1Peripheral);
    }
}

void Drv_RCC_AHB_ControlPeripheral(BUS_Control_t eBUS_Control, AHBPeripheral_t eAHBPeripheral)
{
    if(eBUS_Control == BUS_Control_Reset) {
        RCC->AHBRSTR |= (1U << (uint32_t)eAHBPeripheral);
    }
    else {
        RCC->AHBENR &= ~(1U << (uint32_t)eAHBPeripheral);
        RCC->AHBENR |= ((uint32_t)eBUS_Control << (uint32_t)eAHBPeripheral);
    }
}

void Drv_RCC_USART_SetSourceClock(uint32_t Channel, RCC_USART_SourceClock_t eRCC_USART_SourceClock)
{
    volatile uint32_t RCC_CFGR3_USART_CHANNEL_Pos;

    switch (Channel)
    {
    case 1:
        RCC_CFGR3_USART_CHANNEL_Pos = 0;
        break;
    case 2:
        RCC_CFGR3_USART_CHANNEL_Pos = 16;
        break;
    case 3:
        RCC_CFGR3_USART_CHANNEL_Pos = 18;
        break;
    case 4:
        RCC_CFGR3_USART_CHANNEL_Pos = 20;
        break;
    case 5:
        RCC_CFGR3_USART_CHANNEL_Pos = 22;
        break;
    default:
        break;
    }

    RCC->CFGR3 &= ~(3U << RCC_CFGR3_USART_CHANNEL_Pos);
    RCC->CFGR3 |= ((uint32_t)eRCC_USART_SourceClock << RCC_CFGR3_USART_CHANNEL_Pos);
}

void Drv_RCC_TIMER_SetSourceClock(uint32_t Channel, RCC_TIMER_SourceClock_t eRCC_TIMER_SourceClock)
{
    volatile uint32_t RCC_CFGR3_TIMER_CHANNEL_Pos;

    switch (Channel)
    {
    case 1:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 8;
        break;
    case 2:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 24;
        break;
    case 3: case 4:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 25;
        break;
    case 8:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 9;
        break;
    case 15:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 10;
        break;
    case 16:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 11;
        break;
    case 17:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 13;
        break;
    case 20:
        RCC_CFGR3_TIMER_CHANNEL_Pos = 15;
        break;
    default:
        break;
    }

    RCC->CFGR3 &= ~(1U << RCC_CFGR3_TIMER_CHANNEL_Pos);
    RCC->CFGR3 |= ((uint32_t)eRCC_TIMER_SourceClock << RCC_CFGR3_TIMER_CHANNEL_Pos);
}

void Drv_RCC_I2C_SetSourceClock(uint32_t Channel, RCC_I2C_SourceClock_t eRCC_I2C_SourceClock)
{
    volatile uint32_t RCC_CFGR3_I2C_CHANNEL_Pos;

    switch (Channel)
    {
    case 1:
        RCC_CFGR3_I2C_CHANNEL_Pos = 4;
        break;
    case 2:
        RCC_CFGR3_I2C_CHANNEL_Pos = 5;
        break;
    case 3:
        RCC_CFGR3_I2C_CHANNEL_Pos = 6;
        break;
    default:
        break;
    }

    RCC->CFGR3 &= ~(1U << RCC_CFGR3_I2C_CHANNEL_Pos);
    RCC->CFGR3 |= ((uint32_t)eRCC_I2C_SourceClock << RCC_CFGR3_I2C_CHANNEL_Pos);
}
