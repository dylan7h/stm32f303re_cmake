#ifndef __DRV_SYSTICK__H__
#define __DRV_SYSTICK__H__

void Drv_Systick_Initialize(uint32_t AHBClockValue);
void Drv_Systick_Delau_ms(uint32_t ms);
void Drv_Systick_Delau_us(uint32_t us);

#endif  //!__DRV_SYSTICK__H__