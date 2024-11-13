/******************************************************************************
/*                                                                            */
/*                                ILLUSION                                    */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program generates a "bit cascade" illusion in the console.            */
/* It simulates a screen where rows of random '0's and '1's scroll down,      */
/* creating an effect similar to a waterfall of binary characters.            */
/*                                                                            */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 12 Nov 2024                                                 */
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
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 120    // Width of the cascade (number of columns)
#define HEIGHT 50    // Height of the cascade (number of rows)
#define DELAY 80000  // Delay between updates (in microseconds)

// Clears the screen using an ANSI escape code
void clear_screen() {
    printf("\033[H\033[J");  // ANSI code to clear the screen
}

// Generates a new row of random '0's and '1's
void generate_row(char row[]) {
    for (int i = 0; i < WIDTH; i++) {
        row[i] = (rand() % 2) ? '1' : '0';  // Randomly assign '0' or '1'
    }
}

// Shifts all rows in the screen array down by one position
void shift_screen(char screen[HEIGHT][WIDTH]) {
    for (int i = HEIGHT - 1; i > 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = screen[i - 1][j];  // Move the row above downward
        }
    }
}

// Prints the entire screen array to the console
void print_screen(char screen[HEIGHT][WIDTH]) {
    clear_screen();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char screen[HEIGHT][WIDTH] = {0};  // 2D array to simulate the screen
    srand(time(NULL));  // Initialize random number generator with current time

    while (1) {
        char new_row[WIDTH];
        generate_row(new_row);         // Generate a new random row of '0's and '1's
        shift_screen(screen);          // Shift the screen content downward

        // Add the newly generated row at the top of the screen
        for (int i = 0; i < WIDTH; i++) {
            screen[0][i] = new_row[i];
        }

        print_screen(screen);          // Display the screen
        usleep(DELAY);                 // Delay before the next update
    }

    return 0;
}
