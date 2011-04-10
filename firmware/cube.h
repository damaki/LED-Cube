/*
 * cube.h
 *
 *  Created on: 3 Apr 2011
 *      Author: Dan
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <avr/io.h>

#define CUBE_SIZE       8
#define REFRESH_RATE_HZ 100         /* Min = 2 */
#define MAX_BRIGHTNESS  14          /* Min = 1, Max = 14 */
#define CPU_SPEED       16000000    /* 16MHz */

extern uint8_t g_cube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

void cube_init();

#endif /* CUBE_H_ */
