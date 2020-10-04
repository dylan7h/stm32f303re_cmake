#include "stm32f3xx.h"

int main(void)
{
    volatile int i = 1;

    i += 1;

    while(1)
    {
        i += 1;
    }

    return 0;
}