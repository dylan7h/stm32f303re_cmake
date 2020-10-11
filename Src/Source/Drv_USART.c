#include <stdbool.h>
#include <stdint.h>
#include "autoconfig.h"
#include "stm32f3xx.h"
#include "Drv_RCC.h"
#include "Drv_GPIO.h"
#include "Drv_USART.h"

USART_TypeDef* USARTx[] = { USART1, USART2, USART3, UART4, UART5 };

static uint32_t Drv_USART_GetInputClock(USART_Channel_t eUSART_Channel, RCC_USART_SourceClock_t eRCC_USART_SourceClock)
{
    uint32_t USART_InputClockValue;

    switch (eRCC_USART_SourceClock)
    {
    case RCC_USART_SourceClock_HSI:
        USART_InputClockValue = HSI_CLOCK_VALUE;
        break;
    case RCC_USART_SourceClock_LSE:
        USART_InputClockValue = LSE_CLOCK_VALUE;
        break;
    case RCC_USART_SourceClock_PCLK:
        USART_InputClockValue = (eUSART_Channel == USART_Channel_1) ? Drv_RCC_APB_GetClock(APBNumber_2) : Drv_RCC_APB_GetClock(APBNumber_1);
        break;
    case RCC_USART_SourceClock_SYSCLK:
        USART_InputClockValue = Drv_RCC_System_GetClock();
        break;
    default:
        USART_InputClockValue = HSI_CLOCK_VALUE;
        break;
    }

    return USART_InputClockValue;
}

static void Drv_USART_SetBaudrate(USART_Channel_t eUSART_Channel, uint32_t USART_InputClockValue, USART_Baudrate_t eUSART_Baudrate)
{
    uint32_t ErrorRate_x8, ErrorRate_x16;
    uint32_t USARTDIV;

    /* Clear Oversampling bit */
    USARTx[eUSART_Channel]->CR1 &= ~USART_CR1_OVER8_Msk;

    /* Calculate Error Rate */
    ErrorRate_x8 = (2 * USART_InputClockValue) % eUSART_Baudrate;
    ErrorRate_x16 = (USART_InputClockValue) % eUSART_Baudrate;
    if(ErrorRate_x8 < ErrorRate_x16)
    {
        /* x8: Baud = (2 * InClk) / USARTDIV */
        USARTDIV = (2 * USART_InputClockValue) / eUSART_Baudrate;
        USARTx[eUSART_Channel]->BRR = (USARTDIV & 0xFFF0U) | ((USARTDIV >> 1U) & 0x07U);

        /* Set Oversampling x8 */
        USARTx[eUSART_Channel]->CR1 |= (1 << USART_CR1_OVER8_Pos);
    }
    else
    {
        /* x16: Baud = InClk / USARTDIV */
        USARTDIV = (USART_InputClockValue) / eUSART_Baudrate;
        USARTx[eUSART_Channel]->BRR = USARTDIV;
    }
}

void Drv_USART_Initialize(USART_t* pUSART)
{
    uint32_t USART_InputClockValue;

    /* Enable Power Of USART */
    if(pUSART->eUSART_Channel == USART_Channel_1) {
        Drv_RCC_APB2_ControlPeripheral(BUS_Control_Enable, APB2Peripheral_USART1);
    }
    else {
        Drv_RCC_APB1_ControlPeripheral(BUS_Control_Enable, APB1Peripheral_USART2 + (pUSART->eUSART_Channel - 1U));
    }

    /* Set USART Source Clock */
    Drv_RCC_USART_SetSourceClock(2, pUSART->eRCC_USART_SourceClock);

    /* Disable USART */
    USARTx[pUSART->eUSART_Channel]->CR1 &= ~USART_CR1_UE_Msk;

    /* Enable Transmit & Recv */
    USARTx[pUSART->eUSART_Channel]->CR1 |= (USART_CR1_TE_Msk | USART_CR1_RE_Msk);

    /* Set Data Width */
    USARTx[pUSART->eUSART_Channel]->CR1 &= ~(USART_CR1_M1_Msk | USART_CR1_M0_Msk);
    switch (pUSART->eUSART_Width)
    {
    case USART_Width_8:
        break;
    case USART_Width_9:
        USARTx[pUSART->eUSART_Channel]->CR1 |= USART_CR1_M0_Msk;
        break;
    case USART_Width_7:
        USARTx[pUSART->eUSART_Channel]->CR1 |= USART_CR1_M1_Msk;
        break;
    default:
        break;
    }

    /* Set Stop Bit */
    USARTx[pUSART->eUSART_Channel]->CR2 &= ~USART_CR2_STOP_Msk;
    USARTx[pUSART->eUSART_Channel]->CR2 |= (pUSART->eUSART_Stop << USART_CR2_STOP_Pos);

    /* Set Parity Bit */
    USARTx[pUSART->eUSART_Channel]->CR1 &= ~USART_CR1_PCE_Msk;
    if(pUSART->eUSART_Parity != USART_Parity_None) {
        USARTx[pUSART->eUSART_Channel]->CR1 |= ( USART_CR1_PCE_Msk | (pUSART->eUSART_Parity << USART_CR1_PS_Pos) );
    }

    /* Get USART Source Clock Value */
    USART_InputClockValue = Drv_USART_GetInputClock(pUSART->eUSART_Channel, pUSART->eRCC_USART_SourceClock);

    /* Set Baudrate */
    Drv_USART_SetBaudrate(pUSART->eUSART_Channel, USART_InputClockValue, pUSART->eUSART_Baudrate);

    /* Enable USART */
    USARTx[pUSART->eUSART_Channel]->CR1 |= USART_CR1_UE_Msk;
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
