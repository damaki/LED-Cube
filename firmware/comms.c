/*
 * comms.c
 *
 *  Created on: 4 Apr 2011
 *      Author: Daniel King
 */
#include "comms.h"
#include "cube.h"
#include <avr/interrupt.h>

typedef enum
{
    STATE_IDLE,
    STATE_RECEIVING
} State;

static State g_state = STATE_IDLE;
static uint16_t g_frame_count = 0;

#define FOSC 16000000
#define BAUD_RATE 125000

/**
 * \brief Initialises UART0 for communications with the PC tool to receive
 * cube frames.
 *
 * @author Daniel King
 */
void comms_init()
{
    g_state = STATE_IDLE;

    /* Initialise the UART */
    UBRR0  = (FOSC/(16*BAUD_RATE))-1;
    UCSR0C = (0x3 << 1);    /* 8 data bits */
    UCSR0B = (1 << RXEN0) | /* Enable Rx */
             (1 << RXCIE0); /* Enable Interrupt on Rx*/
}

/**
 * \brief ISR for the UART Receiver
 *
 * This is declared as ISR_NAKED (no epilogue/prologue) since there's no main loop or
 * nested interrupts, so there's no need to preserve any registers.
 *
 * @author Daniel King
 */
ISR(USART0_RX_vect, ISR_NAKED)
{
    if ((UCSR0A & 0x1C) == 0) /* Check if any reception errors have occurred */
    {
        const uint8_t byte = UDR0;

        if (0xFF == byte) /* Have we received the start character? */
        {
            g_state = STATE_RECEIVING;
            g_frame_count = 0;
        }
        else if (STATE_RECEIVING == g_state)
        {
            /* The received byte has 2 LEDs worth of data packed into it */
            ((uint8_t*)g_cube)[g_frame_count++] = byte & 0x0F;
            ((uint8_t*)g_cube)[g_frame_count++] = (byte & 0xF0) >> 4;

            if (g_frame_count >= 512) /* Have we updated the whole cube? */
            {
                /* Wait for the next start character */
                g_state = STATE_IDLE;
                g_frame_count = 0;
            }
        }
    }
    else
    {
        /* Frame error, data overrun, or parity error - drop the current frame & wait for the next one */
        g_state = STATE_IDLE;
        g_frame_count = 0;
    }

    /* Since this ISR is ISR_NAKED, we need to explicitly return from the ISR ourselves */
    reti();
}
