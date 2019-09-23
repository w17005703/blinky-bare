#include <stdint.h>
#include <stdbool.h>
#include "MK64F12.h"

#define PIN21_MASK           (1u << 21)

void delay(int count);

int main(void)
{
    /* Enable the clock to PORT B */
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

    /* Select the GPIO function (Alternative 1) for pin 21 of PORT B */
    PORTB_PCR21 &= ~PORT_PCR_MUX_MASK;
    PORTB_PCR21 |= (1u << PORT_PCR_MUX_SHIFT);

    /* Set the data direction for pin 21 of PORT B to output */
    GPIOB_PDDR |= PIN21_MASK;

    while (true) {
        /* Turn on the blue LED */
        GPIOB_PDOR &= ~PIN21_MASK;
        /* Wait for about 1 second */
    	delay(1000);
        /* Turn off the blue LED */
        GPIOB_PDOR |= PIN21_MASK; 
        /* Wait for about 1 second */
	delay(1000);
    }
    return 0;
}

void delay(int count) {
    volatile int i = 0;
    for (i = count*1000 ; i !=0; i--) {
	/* skip */
    }
}
