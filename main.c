#include <stdint.h>
#include <stdbool.h>

/* Register address and mask definitions for the 
 * System Clock Gating Control Register 5 
 * See reference manual, chapter 12, pp 314
 */
#define SIM_SCGC5            (*((volatile uint32_t *)(0x40048038u)))
#define SIM_SCGC5_PORTB_MASK (1u << 10)

/* Register address and mask definitions for the Pin Control Register for
 * pin 21 in PORT B
 * See the reference manual, chapter 11, pp 277, and chapter 11, pp 283
 */ 
#define PORTB_PCR21          (*((volatile uint32_t *)(0x4004A054u)))  //Ch11 pp277
#define PORTB_PCR22	     (*((volatile uint32_t *)(0x4004A058u)))
#define PORT_PCR_MUX_MASK    (0x0700u)   /*Ch11 pp283      */ 
#define PORT_PCR_MUX_SHIFT   (8u)        /*ch11 pp283      */ 

/* Register address and mask definitions for GPIO PORT B 
 * Port Data Direction Register and Port Data Output Register
 * See the reference manual, chapter 55, pp 1760ff
 */ 
#define GPIOB_PDDR           (*((volatile uint32_t *)(0x400FF054u)))  /*ch55 pp1760 */
#define GPIOB_PDOR           (*((volatile uint32_t *)(0x400FF040u)))  /*ch55 pp1759 */
#define PIN21_MASK           (1u << 21)                               /*schematic pp3 RGB LED Feature PTB21 */
#define PIN22_MASK           (1u << 22)
void delay(int count);

int main(void)
{
    /* Enable the clock to PORT B */
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;           /*or the value at *0x40048038 with ... 0100 0000 0000*/

    /* Select the GPIO function (Alternative 1) for pin 21 of PORT B */
    PORTB_PCR21 &= ~PORT_PCR_MUX_MASK;           /*zero bits 8,9,10      */
    PORTB_PCR21 |= (1u << PORT_PCR_MUX_SHIFT);
    PORTB_PCR22 &= ~PORT_PCR_MUX_MASK;
    PORTB_PCR22 |= (1u << PORT_PCR_MUX_SHIFT);   /*set them to 001 Alternative 1(GPIO)  */

    /* Set the data direction for pin 21 of PORT B to output */
    GPIOB_PDDR |= PIN21_MASK;		    /*or the value at *0x400FF054 with 0000 0000 0010 0000 0000 0000 0000 0000 */
    GPIOB_PDDR |= PIN22_MASK;

    while (true) {
        /* Turn on the blue LED */
        GPIOB_PDOR &= ~PIN21_MASK;
	GPIOB_PDOR |= PIN22_MASK;		/*And the value in *0x400FF040 with 1111 1111 1101 1111 1111 1111 1111 1111
		                                 setting to 0 sinks the current through the LED.*/
        /* Wait for about 1 second */
        delay(1000);
        /* Turn off the blue LED */
        GPIOB_PDOR |= PIN21_MASK; 
	GPIOB_PDOR &= ~PIN22_MASK;      /*Or the value in *0x400FF040 with 0000 0000 0010 0000 0000 0000 0000 0000
		                                seeting to 1 stops current flowing through the LED.*/   
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

