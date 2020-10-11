#ifndef __DRV_RCC__H__
#define __FRV_RCC__H__

#ifndef LSE_CLOCK_VALUE
#define LSE_CLOCK_VALUE (32768U)
#endif  /* LSE_CLOCK_VALUE */

#ifndef HSI_CLOCK_VALUE
#define HSI_CLOCK_VALUE (8000000U)
#endif  /* HSI_CLOCK_VALUE */

#ifndef HSE_CLOCK_VALUE
#define HSE_CLOCK_VALUE (16000000U)
#endif  /* HSE_CLOCK_VALUE */

/* RCC->CFGR - PLLSRC */
typedef enum { 
    PLLSource_HSI_Half  = 0x0U,     /* HSI/2 used as PREDIV1 entry and PREDIV1 forced to div by 2. */
    PLLSource_HSI       = 0x1U, 
    PLLSource_HSE       = 0x2U
} PLLSource_t;

/* RCC->CFGR2 - PREDIV */
typedef enum {  
    PllPreviousDivider_1    = 0x0U,
    PllPreviousDivider_2    = 0x1U,
    PllPreviousDivider_3    = 0x2U,
    PllPreviousDivider_4    = 0x3U,
    PllPreviousDivider_5    = 0x4U,
    PllPreviousDivider_6    = 0x5U,
    PllPreviousDivider_7    = 0x6U,
    PllPreviousDivider_8    = 0x7U,
    PllPreviousDivider_9    = 0x8U,
    PllPreviousDivider_10   = 0x9U,
    PllPreviousDivider_11   = 0xAU,
    PllPreviousDivider_12   = 0xBU,
    PllPreviousDivider_13   = 0xCU,
    PllPreviousDivider_14   = 0xDU,
    PllPreviousDivider_15   = 0xEU,
    PllPreviousDivider_16   = 0xFU,
} PllPreviousDivider_t;

/* RCC->CFGR - PLLMUL */
typedef enum {  
    PllMultiplier_2    = 0x0U,
    PllMultiplier_3    = 0x1U,
    PllMultiplier_4    = 0x2U,
    PllMultiplier_5    = 0x3U,
    PllMultiplier_6    = 0x4U,
    PllMultiplier_7    = 0x5U,
    PllMultiplier_8    = 0x6U,
    PllMultiplier_9    = 0x7U,
    PllMultiplier_10   = 0x8U,
    PllMultiplier_11   = 0x9U,
    PllMultiplier_12   = 0xAU,
    PllMultiplier_13   = 0xBU,
    PllMultiplier_14   = 0xCU,
    PllMultiplier_15   = 0xDU,
    PllMultiplier_16   = 0xEU,
} PllMultiplier_t;

/* RCC->CFGR - SWS */
typedef enum { 
    SystemClockSource_HSI = 0x0, 
    SystemClockSource_HSE = 0x1,
    SystemClockSource_PLL = 0x2,
} SystemClockSource_t;

/* RCC->CFGR - HPRE */
typedef enum {  
    AHBPrescaler_1     = 0x0U,
    AHBPrescaler_2     = 0x8U,
    AHBPrescaler_4     = 0x9U,
    AHBPrescaler_8     = 0xAU,
    AHBPrescaler_16    = 0xBU,
    AHBPrescaler_64    = 0xCU,
    AHBPrescaler_128   = 0xDU,
    AHBPrescaler_256   = 0xEU,
    AHBPrescaler_512   = 0xFU,
} AHBPrescaler_t;

typedef enum {  
    APBNumber_1         = 0,
    APBNumber_2         = 1,
} APBNumber_t;

/* RCC->CFGR - PPRE1/2 */
typedef enum {  
    APBPrescaler_1     = 0x0,
    APBPrescaler_2     = 0x4,
    APBPrescaler_4     = 0x5,
    APBPrescaler_8     = 0x6,
    APBPrescaler_16    = 0x7,
} APBPrescaler_t;

typedef enum {
    BUS_Control_Disable = 0,
    BUS_Control_Enable  = 1,
    BUS_Control_Reset   = 0,
} BUS_Control_t;

typedef enum {
    APB2Peripheral_SYSCFG   = 0U,
    APB2Peripheral_TIMER1   = 11U,
    APB2Peripheral_SPI1     = 12U,
    APB2Peripheral_TIMER8   = 13U,
    APB2Peripheral_USART1   = 14U,
    APB2Peripheral_SPI4     = 15U,
    APB2Peripheral_TIMER15  = 16U,
    APB2Peripheral_TIMER16  = 17U,
    APB2Peripheral_TIMER17  = 18U,
    APB2Peripheral_TIMER20  = 20U
} APB2Peripheral_t;

typedef enum {
    APB1Peripheral_TIMER2   = 0U,
    APB1Peripheral_TIMER3   = 1U,
    APB1Peripheral_TIMER4   = 2U,
    APB1Peripheral_TIMER6   = 4U,
    APB1Peripheral_TIMER7   = 5U,
    APB1Peripheral_WWDG     = 11U,
    APB1Peripheral_SPI2     = 14U,
    APB1Peripheral_SPI3     = 15U,
    APB1Peripheral_USART2   = 17U,
    APB1Peripheral_USART3   = 18U,
    APB1Peripheral_USART4   = 19U,
    APB1Peripheral_USART5   = 20U,
    APB1Peripheral_I2C1     = 21U,
    APB1Peripheral_I2C2     = 22U,
    APB1Peripheral_USB      = 23U,
    APB1Peripheral_CAN      = 25U,
    APB1Peripheral_DAC2     = 26U,
    APB1Peripheral_PWR      = 28U,
    APB1Peripheral_DAC1     = 29U,
    APB1Peripheral_I2C3     = 30U,
} APB1Peripheral_t;

typedef enum {
    AHBPeripheral_DMA1      = 0U,
    AHBPeripheral_DMA2      = 1U,
    AHBPeripheral_SRAM      = 2U,
    AHBPeripheral_FLTF      = 4U,
    AHBPeripheral_FMC       = 5U,
    AHBPeripheral_CRC       = 6U,
    AHBPeripheral_IOPH      = 16U,
    AHBPeripheral_IOPA      = 17U,
    AHBPeripheral_IOPB      = 18U,
    AHBPeripheral_IOPC      = 19U,
    AHBPeripheral_IOPD      = 20U,
    AHBPeripheral_IOPE      = 21U,
    AHBPeripheral_IOPF      = 22U,
    AHBPeripheral_IOPG      = 23U,
    AHBPeripheral_TSCEN     = 24U,
    AHBPeripheral_ADC12     = 28U,
    AHBPeripheral_ADC34     = 29U,
} AHBPeripheral_t;

typedef enum {
    RCC_USART_SourceClock_PCLK      = 0U,
    RCC_USART_SourceClock_SYSCLK    = 1U,
    RCC_USART_SourceClock_LSE       = 2U,
    RCC_USART_SourceClock_HSI       = 3U
} RCC_USART_SourceClock_t;

typedef enum {
    RCC_TIMER_SourceClock_PCLK2     = 0U,
    RCC_TIMER_SourceClock_PLLx2     = 1U,
} RCC_TIMER_SourceClock_t;

typedef enum {
    RCC_I2C_SourceClock_HSI         = 0U,
    RCC_I2C_SourceClock_SYSCLK      = 1U,
} RCC_I2C_SourceClock_t;

/* PLLClock = PLLSource * PllPreviousDivider * PllMultiplier */
void Drv_RCC_PLL_SetClock(PLLSource_t ePLLSource, PllPreviousDivider_t ePllPreviousDivider, PllMultiplier_t ePllMultiplier);
void Drv_RCC_AHB_SetClock(SystemClockSource_t eSystemClockSource, AHBPrescaler_t eAHBPrescaler);
void Drv_RCC_APB_SetClock(APBNumber_t eAPBNumber, APBPrescaler_t eAPBPrescaler);

uint32_t Drv_RCC_PLL_GetClock(void);
uint32_t Drv_RCC_System_GetClock(void);
uint32_t Drv_RCC_AHB_GetClock(void);
uint32_t Drv_RCC_APB_GetClock(APBNumber_t eAPBNumber);

void Drv_RCC_APB2_ControlPeripheral(BUS_Control_t eBUS_Control, APB2Peripheral_t eAPB2Peripheral);
void Drv_RCC_APB1_ControlPeripheral(BUS_Control_t eBUS_Control, APB1Peripheral_t eAPB1Peripheral);
void Drv_RCC_AHB_ControlPeripheral(BUS_Control_t eBUS_Control, AHBPeripheral_t eAHBPeripheral);

void Drv_RCC_USART_SetSourceClock(uint32_t Channel, RCC_USART_SourceClock_t eRCC_USART_SourceClock);
void Drv_RCC_TIMER_SetSourceClock(uint32_t Channel, RCC_TIMER_SourceClock_t eRCC_TIMER_SourceClock);
void Drv_RCC_I2C_SetSourceClock(uint32_t Channel, RCC_I2C_SourceClock_t eRCC_I2C_SourceClock);

#endif  //!__DRV_RCC__H__