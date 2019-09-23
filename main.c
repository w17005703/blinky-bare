#include <stdint.h>
#include <stdbool.h>

/* Register address and mask definitions for the 
 * System Clock Gating Control Register 5 
 * See reference manual, chapter 12, pp 273ff
 */
#define SIM_SCGC5            (*((volatile uint32_t *)(0x40048038u)))
#define SIM_SCGC5_PORTB_MASK (1u << 10)

/* Register address and mask definitions for the Pin Control Register for
 * pin 21 in PORT B
 * See the reference manual, chapter 10, pp 243ff, and chapter 11, pp 273ff
 */ 
#define PORTB_PCR21          (*((volatile uint32_t *)(0x4004A054u)))
#define PORT_PCR_MUX_MASK    (0x0700u)
#define PORT_PCR_MUX_SHIFT   (8u)

/* Register address and mask definitions for GPIO PORT B 
 * Port Data Direction Register and Port Data Output Register
 * See the reference manual, chapter 55, pp 1757ff
 */ 
#define GPIOB_PDDR           (*((volatile uint32_t *)(0x400FF054u)))
#define GPIOB_PDOR           (*((volatile uint32_t *)(0x400FF040u)))
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
    int i = 0;
    for (i = count*1000 ; i !=0; i--) {
	/* skip */
    }
}
