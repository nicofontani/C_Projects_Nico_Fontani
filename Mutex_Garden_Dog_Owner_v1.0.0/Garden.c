/******************************************************************************/
/*                                                                            */
/*                            GARDEN SIMULATION WITH DOG                      */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program simulates a garden where a dog and an owner interact. The     */
/* owner and the dog are represented by separate processes. The dog can      */
/* "poop" on the plates of the garden, and the owner maintains the garden.    */
/* The program uses mutexes for synchronization and shared memory for        */
/* storing the garden's state.                                                */
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

#include "./mutex.h"
#include "./shared.h"

#define MTX_KEY 4242       // Mutex key for synchronization
#define SHM_KEY 4243       // Shared memory key for garden state

// Enum to represent the state of the plates (either CLEAN or POOP)
typedef enum {
    CLEAN, POOP
} Plate;

// Function to handle errors
void errore(int n, char* s);

int main(int argc, char* argv[]) {
    // Ensure the user provides the number of plates
    if (argc != 2) {
        printf("USAGE: %s #N_PLATES\n", argv[0]);
        return -1;
    }
    int n_plates = atoi(argv[1]);  // Number of plates
    char* cmd[] = { NULL, argv[1], NULL };  // Command for owner and dog processes

    // Create a mutex for synchronization
    int mtx_id = mutex_create(MTX_KEY, 1);
    if (mtx_id == -1) errore(-2, "mutex_create()");
    mutex_lock(mtx_id);  // Lock the mutex to control access to shared resources

    // Create shared memory for the garden state (plates)
    int shm_id;
    Plate* garden_path = shared_create(SHM_KEY, sizeof(Plate) * n_plates, &shm_id);
    if (!garden_path) errore(-3, "shared_create()");

    // Initialize all plates as CLEAN
    for (int i = 0; i < n_plates; i++) {
        *(garden_path + i) = CLEAN;
    }

    // Simulate placing the owner in the garden
    printf("Build the garden...\n");
    printf("Place the Owner...\n");
    cmd[0] = "./owner";  // Set the command to execute the owner process
    if (!fork()) {  // Create the owner process
        execvp(*cmd, cmd);
        errore(-2, "execvp()");  // If execvp fails, report error
    }

    // Simulate placing the dog in the garden
    printf("Place the dog...\n");
    cmd[0] = "./dog";  // Set the command to execute the dog process
    if (!fork()) {  // Create the dog process
        execvp(*cmd, cmd);
        errore(-2, "execvp()");  // If execvp fails, report error
    }

    // Release the dog to start interacting with the garden
    printf("Release the dog...\n\n");
    mutex_unlock(mtx_id);  // Unlock the mutex to allow processes to proceed

    // Wait for the owner and dog processes to finish
    wait(NULL);
    wait(NULL);

    // Print the final state of the garden
    printf("\n[");
    for (int i = 0; i < n_plates; i++) {
        printf("%c ", (*(garden_path + i) == CLEAN) ? '.' : 'P');  // Print clean or pooped plates
    }
    printf("]\n");

    // Clean up the resources
    printf("Clean everything...\n");
    mutex_remove(mtx_id);  // Remove the mutex
    shared_remove(shm_id);  // Remove the shared memory

    return 0;
}

// Error handling function
void errore(int n, char* s) {
    // Print the error message and exit
    printf("ERROR %d: %s ", errno, strerror(errno));
    printf("\tin calling %s.\nExit with return code %d\n", s, n);
    exit(n);
}
