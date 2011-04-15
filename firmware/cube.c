/*
 * cube.c
 *
 *  Created on: 3 Apr 2011
 *      Author: Daniel King
 */
#include "cube.h"
#include <avr/interrupt.h>

uint8_t g_cube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

static uint8_t g_layer   = CUBE_SIZE;
static uint8_t g_counter = MAX_BRIGHTNESS;
static uint8_t g_curr_layer[CUBE_SIZE][CUBE_SIZE];

/* PORT K = 8 bit data bus (connected to D0 to D7 of all 74HC latches) */
/* PORT E = Bit 4 controls the Output Enable (OE) pin on all 74HC chips. HIGH means that output is disabled */
/* PORT F = Controls the Chip Select (CP) pin on each 74HC. Bit 0 = 74HC #0. Move from LOW to HIGH to latch in data from PORTK */
/* PORT A = Controls the 8 MOSFETs which drive the 8 LED layers. Bit 0 = bottom layer. HIGH = layer on */

/**
 * \brief Initialises the cube and
 */
void cube_init()
{
    /* Initialise the hardware/pins */
    DDRK  = 0xFF; /* 8-bit data bus pins initialised to output */
    PORTK = 0;    /* Set data bus to 0 */
    DDRA  = 0xFF; /* Set layer pins to output */
    PORTA = 0;    /* Turn off all layers */
    DDRF  = 0xFF; /* Set chip select pins to output */
    PORTF = 0;    /* Chip select LOW for all chips */
    DDRE  = (1 << PE4); /* Set the Output Enable line to output */
    PORTE = (1 << PE4); /* Set Output Enable to HIGH */
    PORTE = 0; /* Set Output Enable to LOW */

    PORTF = 0xFF; /* Pulse all chip selects to latch in 0 into the chips */
    PORTF = 0;

    /* Initialise the cube */
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t y = 0; y < CUBE_SIZE; ++y)
        {
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                g_cube[x][y][z] = 0;
            }
        }
    }

    /* Timer 1 - Cube update timer */
    TIMSK1 = (1U << OCIE1A); /* Output Capture Interrupt Enable */
    OCR1A  = CPU_SPEED/(REFRESH_RATE_HZ*CUBE_SIZE*MAX_BRIGHTNESS); /* Set the max timer value */
    ICR1   = OCR1A + 1U;        /* Set counter TOP value */
    TCCR1B = (1U << WGM12) |
             (1U << CS10);      /* Start timer, with no prescaling (16MHz)*/
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
    PORTE = (1 << PE4);  /* Set Output Enable to HIGH while we do stuff */

    if (g_counter >= (MAX_BRIGHTNESS - 1)) /* Finished updating the current layer? */
    {
        g_counter = 0;

        /* Go to the next layer */
        ++g_layer;
        if (g_layer >= CUBE_SIZE) /* Gone over the top of the cube? */
        {
            g_layer = 0;
        }

        /* Turn off all LEDs while we change layers */
        PORTA = 0;           /* Turn off all layers */

        /* Go through each row in the layer */
        for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        {
            uint8_t row_bitmask = 0;

            /* Go through each LED in the row */
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                g_curr_layer[x][z] = g_cube[x][g_layer][z];
                if (g_curr_layer[x][z] > 0)
                {
                    --g_curr_layer[x][z];
                    row_bitmask |= (1 << z);
                }
            }

            PORTK = row_bitmask; /* Put LED states to data bus */
            PORTF = (1 << x);    /* Set chip select for this row to HIGH to latch in the data on the bus */
            PORTF = 0;           /* Data has been latched - deselect the chip */
            PORTK = 0;
        }

        PORTA = (1 << g_layer); /* Turn on the current layer only */
    }
    else /* Update the current layer */
    {
        ++g_counter;

        /* Go through each row/latch chip */
        for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        {
            uint8_t row_bitmask = 0;
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                if (g_curr_layer[x][z] > 0) /* Is the LED on? */
                {
                    --g_curr_layer[x][z];   /* Decay the brightness - LED will be off when it reaches 0*/
                    row_bitmask |= (1 << z);
                }
            }

            PORTK = row_bitmask; /* Put LED states for this row to the data bus */
            PORTF = (1 << x);    /* Set chip select for this row to HIGH to latch in the data on the bus */
            PORTF = 0;           /* Data has been latched - deselect the chip */
            PORTK = 0;
        }
    }

    PORTE = 0;              /* Enable the output */

    /* Since this ISR is ISR_NAKED, we need to explicitly return from the ISR ourselves */
    reti();
}
