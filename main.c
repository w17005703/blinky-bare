#include <stdint.h>
#include <stdbool.h>

/* Register address and mask definitions for the 
 * System Clock Gating Control Register 5 
 * See reference manual, chapter 12, pp 273ff
 */
#define SIM_SCGC5            (*((volatile uint32_t *)(0x40048038u)))
#define SIM_SCGC5_PORTB_MASK (1u << 10)
#define SIM_SCGC5_PORTE_MASK (1u << 13)

/* Register address and mask definitions for the Pin Control Register for
 * pins 21 and 22 in PORT B and pin 26 in PORTE
 * See the reference manual, chapter 10, pp 243ff, and chapter 11, pp 273ff
 */ 
#define PORTB_PCR21          (*((volatile uint32_t *)(0x4004A054u)))
#define PORTB_PCR22          (*((volatile uint32_t *)(0x4004A058u)))
#define PORTE_PCR26          (*((volatile uint32_t *)(0x4004D068u)))
#define PORT_PCR_MUX_MASK    (0x0700u)
#define PORT_PCR_MUX_SHIFT   (8u)

/* Register address and mask definitions for GPIO PORTs B and E 
 * Port Data Direction Register and Port Data Output Register
 * See the reference manual, chapter 55, pp 1757ff
 */ 
#define GPIOB_PDDR           (*((volatile uint32_t *)(0x400FF054u)))
#define GPIOB_PDOR           (*((volatile uint32_t *)(0x400FF040u)))
#define GPIOE_PDDR           (*((volatile uint32_t *)(0x400FF114u)))
#define GPIOE_PDOR           (*((volatile uint32_t *)(0x400FF100u)))
#define PIN21_MASK           (1u << 21)
#define PIN22_MASK           (1u << 22)
#define PIN26_MASK           (1u << 26)


void delay(int count);

int main(void)
{
    /* Enable the clock to PORTs B and E */
    SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK);

    /* Select the GPIO function (Alternative 1) for pins 21 and 22 of PORT B 
     * and pin 26 of PORT E 
     */
    PORTB_PCR21 &= ~PORT_PCR_MUX_MASK;
    PORTB_PCR21 |= (1u << PORT_PCR_MUX_SHIFT);
    PORTB_PCR22 &= ~PORT_PCR_MUX_MASK;
    PORTB_PCR22 |= (1u << PORT_PCR_MUX_SHIFT);
    PORTE_PCR26 &= ~PORT_PCR_MUX_MASK;
    PORTE_PCR26 |= (1u << PORT_PCR_MUX_SHIFT);

    /* Set the data direction for pins 21 and 22 of PORT B to output */
    GPIOB_PDDR |= (PIN21_MASK | PIN22_MASK);
    /* Set the data direction for pins 26 of PORT E to output        */
    GPIOE_PDDR |= PIN26_MASK;

    while (true) {
        /* RED on, GREEN off, BLUE off  */
        GPIOB_PDOR &= ~PIN22_MASK;
        GPIOB_PDOR |= PIN21_MASK;
        GPIOE_PDOR |= PIN26_MASK;
        /* Wait for about 1 second */
    	delay(1000);
        /* RED off, GREEN on, BLUE off  */
        GPIOB_PDOR |= PIN22_MASK;
        GPIOB_PDOR |= PIN21_MASK;
        GPIOE_PDOR &= ~PIN26_MASK;
        /* Wait for about 1 second */
    	delay(1000);
        /* RED off, GREEN off, BLUE on  */
        GPIOB_PDOR |= PIN22_MASK;
        GPIOB_PDOR &= ~PIN21_MASK;
        GPIOE_PDOR |= PIN26_MASK;
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
