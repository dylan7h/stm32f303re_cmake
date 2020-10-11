#include <stdbool.h>
#include <stdint.h>
#include "autoconfig.h"
#include "stm32f3xx.h"
#include "Drv_RCC.h"
#include "Drv_GPIO.h"
#include "Drv_USART.h"

USART_TypeDef* USARTx[] = { USART1, USART2, USART3, UART4, UART5 };

void Drv_USART_Initialize(USART_t* pUSART)
{
    volatile uint32_t Channel = pUSART->eUSART_Channel;
    volatile uint32_t USARTDIV;
    volatile uint32_t USART_InputClockValue;
    volatile uint32_t ErrorRate_x8;
    volatile uint32_t ErrorRate_x16;

    if(Channel == USART_Channel_1) {
        Drv_RCC_APB2_ControlPeripheral(BUS_Control_Enable, APB2Peripheral_USART1);
    }
    else {
        Drv_RCC_APB1_ControlPeripheral(BUS_Control_Enable, APB1Peripheral_USART2 + (Channel - 1U));
    }

    Drv_RCC_USART_SetSourceClock(2, pUSART->eRCC_USART_SourceClock);
    switch (pUSART->eRCC_USART_SourceClock)
    {
    case RCC_USART_SourceClock_HSI:
        USART_InputClockValue = HSI_CLOCK_VALUE;
        break;
    case RCC_USART_SourceClock_LSE:
        USART_InputClockValue = LSE_CLOCK_VALUE;
        break;
    case RCC_USART_SourceClock_PCLK:
        USART_InputClockValue = (Channel == USART_Channel_1) ? Drv_RCC_APB_GetClock(APBNumber_2) : Drv_RCC_APB_GetClock(APBNumber_1);
        break;
    case RCC_USART_SourceClock_SYSCLK:
        USART_InputClockValue = Drv_RCC_System_GetClock();
        break;
    default:
        break;
    }

    /* Disable UART */
    USARTx[Channel]->CR1 &= ~USART_CR1_UE_Msk;

    /* 0: x16 , 1: x8 */
    USARTx[Channel]->CR1 |= (1 << USART_CR1_OVER8_Pos);

    /* Enable Transmit & Recv */
    USARTx[Channel]->CR1 |= USART_CR1_TE_Msk | USART_CR1_RE_Msk;

    USARTx[Channel]->CR1 &= ~USART_CR1_OVER8_Msk;
    ErrorRate_x8 = (2 * USART_InputClockValue) % pUSART->eUSART_Baudrate;
    ErrorRate_x16 = (USART_InputClockValue) % pUSART->eUSART_Baudrate;
    if(ErrorRate_x8 < ErrorRate_x16)
    {
        /* x8: Baud = (2 * InClk) / USARTDIV */
        USARTDIV = (2 * USART_InputClockValue) / pUSART->eUSART_Baudrate;
        USARTx[Channel]->BRR = (USARTDIV & 0xFFF0U) | ((USARTDIV >> 1U) & 0x07U);
        USARTx[Channel]->CR1 |= (1 << USART_CR1_OVER8_Pos);
    }
    else
    {
        /* x16: Baud = InClk / USARTDIV */
        USARTDIV = (USART_InputClockValue) / pUSART->eUSART_Baudrate;
        USARTx[Channel]->BRR = USARTDIV;
    }

    /* Enable UART */
    USARTx[Channel]->CR1 |= USART_CR1_UE_Msk;
}

void Drv_USART_Send(USART_t* pUSART, uint8_t* buffer, uint32_t length)
{
    volatile uint32_t i = 0;

    for(i = 0; i < length; i++)
    {
        USART2->TDR = buffer[i];
        while((USART2->ISR & USART_ISR_TXE_Msk) != USART_ISR_TXE_Msk);
    }
}

void Drv_USART_Recv(USART_t* pUSART, uint8_t* buffer, uint32_t length)
{
    volatile uint32_t i = 0;

    for(i = 0; i < length; i++)
    {
        while((USART2->ISR & USART_ISR_RXNE_Msk) != USART_ISR_RXNE_Msk);
        buffer[i] = USART2->TDR;
    }
}
