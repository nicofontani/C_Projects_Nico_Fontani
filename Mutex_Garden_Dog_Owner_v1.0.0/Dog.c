/******************************************************************************/
/*                                                                            */
/*                              DOG GARDEN SIMULATION                        */
/*                                                                            */
/* DESCRIZIONE:                                                               */
/* This program simulates a dog running around a garden, represented by a     */
/* shared array of plates. Each plate can either be clean or contain a poop.  */
/* The program uses a mutex for synchronization to ensure only one dog can   */
/* "poop" on a plate at a time. The dog runs around and randomly "poops"     */
/* on the plates.                                                              */
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

#include <stdio.h>
#include <unistd.h>
#include "./mutex.h"
#include "./shared.h"

#define N_CICLES 100        // Number of cycles the dog will run
#define MTX_KEY 4242        // Key for the mutex
#define SHM_KEY 4243        // Key for the shared memory

// Enum to represent the plate state (either CLEAN or POOP)
typedef enum {
    CLEAN, POOP
} Plate;

int main(int argc, char* argv[]) {

    // Check if the number of plates is passed as an argument
    if (argc != 2) {
        printf("USAGE: %s #N_PLATES\n", argv[0]);
        return -1;
    }
    int n_plates = atoi(argv[1]);  // Number of plates
    int mtx_id = mutex_find(MTX_KEY);  // Get the mutex using the key
    int shm_id;
    Plate* garden_path = shared_find(SHM_KEY, &shm_id);  // Get the shared memory area for the plates

    srand(getpid());  // Seed the random number generator using the process ID
     
    int position = n_plates / 2;  // Start at the middle of the plates

    printf("[%d] Dog is running around...\n", getpid());

    // Run the simulation for N_CICLES cycles
    for (int i = 0; i < N_CICLES; i++) {
        position++;  // Move to the next position
        if (position >= n_plates) position = 0;  // Wrap around if the position exceeds the number of plates
        
        mutex_lock(mtx_id);  // Lock the mutex to ensure exclusive access to the garden
        if (rand() % 2) {  // Randomly decide if the dog will poop on the plate
            *(garden_path + position) = POOP;        
        }
        mutex_unlock(mtx_id);  // Unlock the mutex after accessing the shared memory
        
        usleep(100);  // Simulate a short delay before the next action
    }

    printf("[%d] Dog is calm now...\n", getpid());  // Print when the dog has finished
    return 0;
}
