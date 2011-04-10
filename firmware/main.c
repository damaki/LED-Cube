/*
 * main.c
 *
 *  Created on: 26 Feb 2011
 *      Author: Daniel king
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "cube.h"
#include "comms.h"


int main(void)
{
    cube_init();
    comms_init();

	sei(); /* Enable interrupts */

	/* Everything is interrupt-driven (cube drawing & comms) so there's no need
	 * for the main loop to do anything.
	 */
	for(;;);

	return 0;
}
