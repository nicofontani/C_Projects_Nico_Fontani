/******************************************************************************/
/*                                                                            */
/*                                Owner Program                               */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program simulates the behavior of the owner cleaning up after a dog.  */
/* It accesses a shared memory segment representing a garden with plates.     */
/* The owner cleans up the plates marked as 'POOP' and restores them to 'CLEAN'. */
/* It uses a mutex to ensure that only one process can clean a plate at a time. */
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
#include <unistd.h>

#include "./mutex.h"
#include "./shared.h"

#define N_CICLES 100
#define MTX_KEY 4242
#define SHM_KEY 4243

typedef enum {
	CLEAN, POOP
} Plate;

int main(int argc, char* argv[]) {
	// Check if the correct number of arguments is passed
	if (argc != 2) {
		printf("USAGE: %s #N_PLATES\n", argv[0]);
		return -1;
	}

	// Convert the number of plates from string to integer
	int n_plates = atoi(argv[1]);

	// Find the mutex and shared memory segment
	int mtx_id = mutex_find(MTX_KEY);
	int shm_id;
	Plate* garden_path = shared_find(SHM_KEY, &shm_id);

	// Initialize the owner's position
	int position = 0;

	// Owner's cleaning loop
	printf("[%d] Owner is cleaning around...\n", getpid());
	for (int i = 0; i < N_CICLES; i++) {
		position++;  // Move to the next plate
		if (position > n_plates) position = 0;  // Wrap around if we exceed the number of plates
		
		// Lock the mutex before modifying shared memory
		mutex_lock(mtx_id);
		
		// If the plate is marked as 'POOP', clean it
		if (*(garden_path + position) == POOP) {
			*(garden_path + position) = CLEAN;
		}
		
		// Unlock the mutex after modifying shared memory
		mutex_unlock(mtx_id);

		// Simulate the cleaning process with a small delay
		usleep(100);
	}

	// Print a message when the owner is done cleaning
	printf("[%d] Owner can take a break, now.\n", getpid());
	return 0;
}
