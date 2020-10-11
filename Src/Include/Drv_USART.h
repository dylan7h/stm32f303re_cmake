#ifndef __DRV_USART__H__
#define __DRV_USART__H__

typedef enum {
    USART_Channel_1 = 0,
    USART_Channel_2 = 1,
    USART_Channel_3 = 2,
    USART_Channel_4 = 3,
    USART_Channel_5 = 4,
} USART_Channel_t;

typedef enum {
    USART_Async_None            = 0,
    USART_Async_Interrupt_Base  = 1,
    USART_Async_DMA_Base        = 2
} USART_Async_t;

typedef enum {
    USART_Baudrate_110      = 110,
    USART_Baudrate_300      = 300,
    USART_Baudrate_600      = 600,
    USART_Baudrate_1200     = 1200,
    USART_Baudrate_2400     = 2400,
    USART_Baudrate_4800     = 4800,
    USART_Baudrate_9600     = 9600,
    USART_Baudrate_19200    = 19200,
    USART_Baudrate_38400    = 38400,
    USART_Baudrate_57600    = 57600,
    USART_Baudrate_115200   = 115200,
    USART_Baudrate_230400   = 230400,
    USART_Baudrate_460800   = 460800,
    USART_Baudrate_921600   = 921600
} USART_Baudrate_t;

typedef enum {
    USART_Parity_Even   = 0,
    USART_Parity_Odd    = 1,
    USART_Parity_None   = 2
} USART_Parity_t;

typedef enum {
    USART_Width_8 = 0,
    USART_Width_9 = 1,
    USART_Width_7 = 2
} USART_Width_t;
typedef enum {
    USART_Stop_1    = 0,
    USART_Stop_0_5  = 1,
    USART_Stop_2    = 2,
    USART_Stop_1_5  = 3
} USART_Stop_t;

typedef struct
{
    USART_Channel_t         eUSART_Channel;
    USART_Async_t           eUSART_Async;
    USART_Baudrate_t        eUSART_Baudrate;
    RCC_USART_SourceClock_t eRCC_USART_SourceClock;
    USART_Width_t           eUSART_Width;
    USART_Parity_t          eUSART_Parity;
    USART_Stop_t            eUSART_Stop;
} USART_t;

void Drv_USART_Initialize(USART_t* pUSART);
void Drv_USART_Send(USART_t* pUSART, uint8_t* buffer, uint32_t length);
void Drv_USART_Recv(USART_t* pUSART, uint8_t* buffer, uint32_t length);

#endif  //!__DRV_USART__H__