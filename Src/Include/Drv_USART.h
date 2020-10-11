#ifndef __DRV_USART__H__
#define __DRV_USART__H__

typedef struct
{
    uint32_t    Channel;
    uint32_t    Interrupt;
    uint32_t    Baudrate;
    uint32_t    TxPinNumber;
    uint32_t    RxPinNumber;
} USART_t;

void Drv_USART_Initialize(USART_t* pUSART);
void Drv_USART_Send(USART_t* pUSART, uint8_t* buffer, uint32_t length);
void Drv_USART_Recv(USART_t* pUSART, uint8_t* buffer, uint32_t length);

#endif  //!__DRV_USART__H__