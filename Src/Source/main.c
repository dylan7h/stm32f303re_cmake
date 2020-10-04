#include <stdio.h>
#include "stm32f3xx.h"

extern void initialise_monitor_handles(void);

int main(void)
{
    volatile int i = 1;

    i += 1;

    initialise_monitor_handles();

    while(1)
    {
        i += 1;
        printf("hello world!\n");
    }

    return 0;
}