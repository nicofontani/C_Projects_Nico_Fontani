/******************************************************************************/
/*                                                                            */
/*                                SHARED READER                               */
/*                                                                            */
/* DESCRIZIONE:                                                               */
/* This program demonstrates how to access shared memory and read a value    */
/* from it. It finds the shared memory segment using a predefined key, and   */
/* prints the value stored in it.                                             */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Data di creazione: 13 Nov 2024                                             */
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

#include "shared.h"  // Include the shared memory header
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 4242  // Shared memory key

void errore(int n, char* s);

int main(void) {
    int shm_id;
    
    // Find the shared memory using the 'shared_find' function
    int* shared = (int*) shared_find(SHM_KEY, &shm_id);
    if (!shared) {
        errore(-1, "shared_find()");  // Error accessing shared memory
        return -1;
    }

    // Print the value read from shared memory
    printf("Process %d: I read %d\n", getpid(), *shared);

    return 0;
}

void errore(int n, char* s) {
    // Print the error with the error code
    printf("%d - %s\n", n, s);
    printf("%s (%d)\n", strerror(errno), errno);
    exit(n);
}
