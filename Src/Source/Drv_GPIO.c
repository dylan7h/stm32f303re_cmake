#include <stdbool.h>
#include <stdint.h>
#include "autoconfig.h"
#include "stm32f3xx.h"
#include "Drv_RCC.h"
#include "Drv_GPIO.h"

void Drv_GPIO_Initialize(GPIO_t* pGPIO)
{
    uint32_t i, pos;
    GPIO_TypeDef* pGPIOX;
    AHBPeripheral_t eAHBPeripheral;

    switch (pGPIO->ePort)
    {
    case GPIO_PORT_A:
        eAHBPeripheral = AHBPeripheral_IOPA;
        pGPIOX = GPIOA;
        break;
    case GPIO_PORT_B:
        eAHBPeripheral = AHBPeripheral_IOPB;
        pGPIOX = GPIOB;
        break;
    case GPIO_PORT_C:
        eAHBPeripheral = AHBPeripheral_IOPC;
        pGPIOX = GPIOC;
        break;
    case GPIO_PORT_D:
        eAHBPeripheral = AHBPeripheral_IOPD;
        pGPIOX = GPIOD;
        break;
    case GPIO_PORT_E:
        eAHBPeripheral = AHBPeripheral_IOPE;
        pGPIOX = GPIOE;
        break;
    case GPIO_PORT_F:
        eAHBPeripheral = AHBPeripheral_IOPF;
        pGPIOX = GPIOF;
        break;
    case GPIO_PORT_G:
        eAHBPeripheral = AHBPeripheral_IOPG;
        pGPIOX = GPIOG;
        break;
    case GPIO_PORT_H:
        eAHBPeripheral = AHBPeripheral_IOPH;
        pGPIOX = GPIOH;
        break;
    default:
        break;
    }

    Drv_RCC_AHB_ControlPeripheral(BUS_Control_Enable, eAHBPeripheral);

    pGPIOX->MODER   = (uint32_t)pGPIO->eMode;
    pGPIOX->OTYPER  = (uint32_t)pGPIO->eOutputType;
    pGPIOX->OSPEEDR = (uint32_t)pGPIO->eOutputSpeed;
    pGPIOX->PUPDR   = (uint32_t)pGPIO->eDriveStrength;

    if(pGPIO->eMode == GPIO_Mode_AlternateFunction)
    {
        for(i = 0; i < 16; i++)
        {
            if(( ( (uint32_t)pGPIO->eGPIO_Pins >> i ) & 0x1U ) == 0x1U)
            {
                if(i < 8) {
                    pos = i * 4U;
                    pGPIOX->AFR[0] &= ~(0xF << pos);
                    pGPIOX->AFR[0] |= ((uint32_t)pGPIO->eGPIO_AlternateFunction << pos);
                }
                else {
                    pos = (i - 8) * 4U;
                    pGPIOX->AFR[1] &= ~(0xF << pos);
                    pGPIOX->AFR[1] |= ((uint32_t)pGPIO->eGPIO_AlternateFunction << pos);
                }
            }
        }
    }
}

void Drv_GPIO_SetPins(GPIO_PORT_t eGPIO_PORT, GPIO_PIN_t eGPIO_Pins)
{
    GPIO_TypeDef* pGPIOX;

    switch (eGPIO_PORT)
    {
    case GPIO_PORT_A:
        pGPIOX = GPIOA;
        break;
    case GPIO_PORT_B:
        pGPIOX = GPIOB;
        break;
    case GPIO_PORT_C:
        pGPIOX = GPIOC;
        break;
    case GPIO_PORT_D:
        pGPIOX = GPIOD;
        break;
    case GPIO_PORT_E:
        pGPIOX = GPIOE;
        break;
    case GPIO_PORT_F:
        pGPIOX = GPIOF;
        break;
    case GPIO_PORT_G:
        pGPIOX = GPIOG;
        break;
    case GPIO_PORT_H:
        pGPIOX = GPIOH;
        break;
    default:
        break;
    }

    pGPIOX->BSRR = (( (~((uint32_t)eGPIO_Pins)) << 16U ) | (uint32_t)eGPIO_Pins);
}
