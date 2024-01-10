#include "m32_gpio.h"
#include "m32_gpio.c"



// driver code
int main(void)
{
    gpio_setout(PIN0,PORTA);

    while (1)
    {
        gpio_set_output(PIN0,PORTA,VCC);
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        gpio_set_output(PIN0,PORTA,GND);
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
    

    return 0;
}