/******************************************************************************/
/*                                                                            */
/*                            LED Blink Example                               */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program blinks the onboard LED of the Raspberry Pi Pico on and off    */
/* every 500 milliseconds. The LED is controlled using the GPIO pins,         */
/* and the program prints "Acceso" (on) and "Spento" (off) to the console     */
/* for each LED state change.                                                 */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 13 Nov 2024                                                 */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "pico/stdlib.h"

int main() {

    stdio_init_all();  // Initialize input/output, including the serial port

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;  // Define the pin for the onboard LED
    const uint ON = 1;  // LED on state
    const uint OFF = 0;  // LED off state

    gpio_init(LED_PIN);  // Initialize the LED pin
    gpio_set_dir(LED_PIN, GPIO_OUT);  // Set the LED pin as an output

    while (1) {
        gpio_put(LED_PIN, ON);  // Turn the LED on
        printf("ON\n");  // Print "ON" to the console
        sleep_ms(500);  // Wait for 500 milliseconds

        gpio_put(LED_PIN, OFF);  // Turn the LED off
        printf("OFF\n");  // Print "OFF" to the console
        sleep_ms(500);  // Wait for 500 milliseconds
    }

    return 0;
}
