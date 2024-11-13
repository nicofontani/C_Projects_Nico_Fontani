/******************************************************************************/
/*                                                                            */
/*                               Keypad Reader                               */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program reads input from a 4x4 matrix keypad connected to a Raspberry  */
/* Pi Pico using GPIO pins. It initializes the GPIO pins for the keypad and   */
/* detects which key is pressed. The keypress is then printed to the serial  */
/* console.                                                                   */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 13 Nov 2024                                                 */
/*                                                                            */
/* This code was developed by Nico Fontani. Its use and modification are      */
/* permitted, provided that any changes are documented, and the author        */
/* and date are updated to recognize each developer's contribution            */
/* and maintain clear version tracking.                                       */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define ROWS 4
#define COLS 4

// Row and column pins of the keypad
const uint8_t row_pins[ROWS] = {2, 3, 4, 5};
const uint8_t col_pins[COLS] = {6, 7, 8, 9};

// Keypad matrix layout
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Setup function to initialize the GPIO pins
void setup() {
    stdio_init_all(); // Initialize UART for printing to console
    
    // Initialize rows as input with pull-up resistors
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_IN);
        gpio_pull_up(row_pins[i]);
    }
    
    // Initialize columns as output and set them high (inactive)
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_OUT);
        gpio_put(col_pins[i], 1);  // Set columns high (not active)
    }
}

// Function to read the key pressed on the keypad
char read_key() {
    for (int i = 0; i < ROWS; i++) {
        gpio_put(col_pins[i], 0); // Activate the current column by setting it low
        
        for (int j = 0; j < COLS; j++) {
            // Check if the corresponding row pin is low (indicating a key press)
            if (!gpio_get(row_pins[j])) {
                gpio_put(col_pins[i], 1); // Deactivate the column
                return keys[j][i];        // Return the pressed key
            }
        }
        
        gpio_put(col_pins[i], 1); // Deactivate the column if no key is pressed
    }
    
    return '\0';  // Return null character if no key is pressed
}

int main(int argc, char **argv) {
    setup();  // Initialize the keypad and GPIO pins

    while (1) {
        // Continuously check for keypresses
        char key = read_key();
        if (key != '\0') {  // If a key is pressed, print it to the console
            printf("Key pressed: %c\n", key);
        }
        sleep_ms(100); // Delay to debounce and reduce CPU load
    }

    return 0;
}
