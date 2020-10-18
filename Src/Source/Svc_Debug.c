#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Drv_RCC.h"
#include "Drv_GPIO.h"
#include "Drv_USART.h"
#include "Svc_Debug.h"

USART_t tUSART = {
    .eUSART_Channel             = USART_Channel_2,
    .eUSART_Async               = USART_Async_None,
    .eUSART_Baudrate            = USART_Baudrate_115200,
    .eRCC_USART_SourceClock     = RCC_USART_SourceClock_PCLK,
    .eUSART_Width               = USART_Width_8,
    .eUSART_Parity              = USART_Parity_None,
    .eUSART_Stop                = USART_Stop_1
};

void Svc_Debug_Initialize()
{
    GPIO_t tGPIO = {
        .ePort = GPIO_PORT_A,
        .eMode = GPIO_Mode_AlternateFunction,
        .eOutputType = GPIO_OutputType_PushPull,
        .eOutputSpeed = GPIO_OutputSpeed_High,
        .eDriveStrength = GPIO_DriveStrength_None,
        .eGPIO_Pins = GPIO_PIN_2 | GPIO_PIN_3,
        .eGPIO_AlternateFunction = GPIO_AlternateFunction_7
    };
    
    Drv_GPIO_Initialize(&tGPIO);

    Drv_USART_Initialize(&tUSART);
}

int Svc_Debug_Printf(const char* cond, const char* format, ...)
{
    va_list va;
    int length;
    char buff[1024];

    va_start(va, format);
    length = vsnprintf(buff, sizeof(buff), format, va);
    va_end(va);

    Drv_USART_Send(&tUSART, (uint8_t*)cond, strlen(cond));
    Drv_USART_Send(&tUSART, (uint8_t*)buff, length);
    Drv_USART_Send(&tUSART, (uint8_t*)MSG_Color_Off, strlen(MSG_Color_Off));

    return length;
}