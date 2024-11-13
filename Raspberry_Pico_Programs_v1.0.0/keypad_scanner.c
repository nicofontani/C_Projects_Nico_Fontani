/******************************************************************************/
/*                                                                            */
/*                          Keypad Scanning Example                           */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program is designed to scan a 4x4 matrix keypad. It scans the rows    */
/* and columns of the keypad by activating each column one by one and         */
/* checking if any row pin is pulled low (button pressed). It prints the      */
/* row and column of the pressed key to the console.                          */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 13 Nov 2024                                                 */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/* Supported by Raspberry Pi Pico                                             */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define ROWS 4  // Number of rows on the keypad
#define COLS 4  // Number of columns on the keypad

// Define the GPIO pins for the rows and columns of the keypad
const uint ROW_PINS[ROWS] = {0, 1, 2, 3};  // Modify these according to your wiring
const uint COL_PINS[COLS] = {4, 5, 6, 7};  // Modify these according to your wiring

// Function to initialize the GPIO pins
void init_gpio() {
    // Initialize the row pins as input with pull-up resistors
    for (int i = 0; i < ROWS; i++) {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_up(ROW_PINS[i]);
    }
    
    // Initialize the column pins as output and set them to high (1)
    for (int i = 0; i < COLS; i++) {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_put(COL_PINS[i], 1);  // Initially set to high (inactive state)
    }
}

// Function to scan the keypad and detect button presses
void scan_keypad() {
    for (int col = 0; col < COLS; col++) {
        gpio_put(COL_PINS[col], 0);  // Activate the current column (set it low)
        
        // Scan all rows to see if a button is pressed
        for (int row = 0; row < ROWS; row++) {
            if (!gpio_get(ROW_PINS[row])) {  // Check if the row is pulled low (button pressed)
                printf("Key pressed: Row %d, Col %d\n", row, col);  // Print the row and column of the pressed key
                // Include logic here for LED control or other actions upon key press
                
                // Wait for the button to be released before continuing
                while (!gpio_get(ROW_PINS[row]));  // Wait until the key is released
            }
        }
        
        gpio_put(COL_PINS[col], 1);  // Deactivate the current column (set it high)
    }
}

int main() {
    stdio_init_all();  // Initialize the serial interface for debugging output
    init_gpio();  // Initialize the GPIO pins for the keypad

    while (1) {
        scan_keypad();  // Continuously scan the keypad
        sleep_ms(100);  // Add a short delay to avoid overly fast scanning
    }

    return 0;
}
