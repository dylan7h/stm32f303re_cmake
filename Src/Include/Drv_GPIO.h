#ifndef __DRV_GPIO__H__
#define __DRV_GPIO__H__

typedef enum {
    GPIO_PORT_A                 = 0U,
    GPIO_PORT_B                 = 1U,
    GPIO_PORT_C                 = 2U,
    GPIO_PORT_D                 = 3U,
    GPIO_PORT_E                 = 4U,
    GPIO_PORT_F                 = 5U,
    GPIO_PORT_G                 = 6U,
    GPIO_PORT_H                 = 7U
} GPIO_PORT_t;

typedef enum {
    GPIO_Mode_Input             = 0U,
    GPIO_Mode_Output            = 1U,
    GPIO_Mode_AlternateFunction = 2U,
    GPIO_Mode_Analog            = 3U
} GPIO_Mode_t;

typedef enum {
    GPIO_OutputType_PushPull    = 0U,
    GPIO_OutputType_OpenDrain   = 1U
} GPIO_OutputType_t;

typedef enum {
    GPIO_OutputSpeed_Low        = 0U,
    GPIO_OutputSpeed_Medium     = 1U,
    GPIO_OutputSpeed_High       = 3U,
} GPIO_OutputSpeed_t;

typedef enum {
    GPIO_DriveStrength_None     = 0U,
    GPIO_DriveStrength_PullUp   = 1U,
    GPIO_DriveStrength_PullDown = 2U
} GPIO_DriveStrength_t;

typedef enum {
    GPIO_AlternateFunction_0    = 0,
    GPIO_AlternateFunction_1    = 1,
    GPIO_AlternateFunction_2    = 2,
    GPIO_AlternateFunction_3    = 3,
    GPIO_AlternateFunction_4    = 4,
    GPIO_AlternateFunction_5    = 5,
    GPIO_AlternateFunction_6    = 6,
    GPIO_AlternateFunction_7    = 7,
    GPIO_AlternateFunction_8    = 8,
    GPIO_AlternateFunction_9    = 9,
    GPIO_AlternateFunction_10   = 10,
    GPIO_AlternateFunction_11   = 11,
    GPIO_AlternateFunction_12   = 12,
    GPIO_AlternateFunction_13   = 13,
    GPIO_AlternateFunction_14   = 14,
    GPIO_AlternateFunction_15   = 15
} GPIO_AlternateFunction_t;

typedef enum {
    GPIO_PIN_0  = 0x0001U,
    GPIO_PIN_1  = 0x0002U,
    GPIO_PIN_2  = 0x0004U,
    GPIO_PIN_3  = 0x0008U,
    GPIO_PIN_4  = 0x0010U,
    GPIO_PIN_5  = 0x0020U,
    GPIO_PIN_6  = 0x0040U,
    GPIO_PIN_7  = 0x0080U,
    GPIO_PIN_8  = 0x0100U,
    GPIO_PIN_9  = 0x0200U,
    GPIO_PIN_10 = 0x0400U,
    GPIO_PIN_11 = 0x0800U,
    GPIO_PIN_12 = 0x1000U,
    GPIO_PIN_13 = 0x2000U,
    GPIO_PIN_14 = 0x4000U,
    GPIO_PIN_15 = 0x8000U,
} GPIO_PIN_t;

typedef struct {
    GPIO_PORT_t                 ePort;
    GPIO_Mode_t                 eMode;
    GPIO_OutputType_t           eOutputType;
    GPIO_OutputSpeed_t          eOutputSpeed;
    GPIO_DriveStrength_t        eDriveStrength;
    GPIO_AlternateFunction_t    eGPIO_AlternateFunction;
    GPIO_PIN_t                  eGPIO_Pins;
} GPIO_t;

void Drv_GPIO_Initialize(GPIO_t* pGPIO);
void Drv_GPIO_SetPins(GPIO_PORT_t eGPIO_PORT, GPIO_PIN_t eGPIO_Pins);

#endif  //!__DRV_GPIO__H__