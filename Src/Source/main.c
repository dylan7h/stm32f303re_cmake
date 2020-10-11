#include <stdio.h>
#include <string.h>

#include "autoconfig.h"
#include "stm32f3xx.h"
#include "Drv_RCC.h"
#include "Drv_Systick.h"
#include "Drv_GPIO.h"
#include "Svc_Debug.h"

int main(void)
{
    volatile uint32_t PLL_Clock = 0;
    volatile uint32_t System_Clock = 0;
    volatile uint32_t AHB_Clock = 0;
    volatile uint32_t APB1_Clock = 0;
    volatile uint32_t APB2_Clock = 0;
    GPIO_t tGPIO = {
        .ePort = GPIO_PORT_A,
        .eMode = GPIO_Mode_Output,
        .eOutputType = GPIO_OutputType_PushPull,
        .eOutputSpeed = GPIO_OutputSpeed_High,
        .eDriveStrength = GPIO_DriveStrength_None,
        .eGPIO_Pins = GPIO_PIN_5
    };
    volatile uint32_t bFlag = 0;


    Drv_RCC_PLL_SetClock(PLLSource_HSI, PllPreviousDivider_1, PllMultiplier_9);
    Drv_RCC_AHB_SetClock(SystemClockSource_PLL, AHBPrescaler_1);
    Drv_RCC_APB_SetClock(APBNumber_1, APBPrescaler_2);
    Drv_RCC_APB_SetClock(APBNumber_2, APBPrescaler_1);

    PLL_Clock       = Drv_RCC_PLL_GetClock();
    System_Clock    = Drv_RCC_System_GetClock();
    AHB_Clock       = Drv_RCC_AHB_GetClock();
    APB1_Clock      = Drv_RCC_APB_GetClock(APBNumber_1);
    APB2_Clock      = Drv_RCC_APB_GetClock(APBNumber_2);

    Drv_Systick_Initialize(AHB_Clock);
    Drv_GPIO_Initialize(&tGPIO);
    Svc_Debug_Initialize();

    Svc_Debug_Printf("=====================================================\r\n");
    Svc_Debug_Printf("           STM32F303RE System Information            \r\n");
    Svc_Debug_Printf("=====================================================\r\n");
    Svc_Debug_Printf("PLL : %ld [MHz]\r\n", PLL_Clock / 1000000);
    Svc_Debug_Printf("SYS : %ld [MHz]\r\n", System_Clock / 1000000);
    Svc_Debug_Printf("AHB : %ld [MHz]\r\n", AHB_Clock / 1000000);
    Svc_Debug_Printf("APB1: %ld [MHz]\r\n", APB1_Clock / 1000000);
    Svc_Debug_Printf("APB2: %ld [MHz]\r\n", APB2_Clock / 1000000);

    while(1)
    {
        Drv_Systick_Delau_ms(1000);
        if(bFlag) {
            Drv_GPIO_SetPins(GPIO_PORT_A, GPIO_PIN_5);
            bFlag = !bFlag;
        }
        else {
            Drv_GPIO_SetPins(GPIO_PORT_A, 0);
            bFlag = !bFlag;
        }
    }

    return 0;
}