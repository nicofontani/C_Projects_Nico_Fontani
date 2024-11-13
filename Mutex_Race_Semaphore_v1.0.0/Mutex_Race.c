/******************************************************************************/
/*                                                                            */
/*                              SEMAPHORE DEMO                               */
/*                                                                            */
/* DESCRIZIONE:                                                               */
/* This program demonstrates the usage of semaphores for process synchronization. */
/* It creates multiple child processes that enter a critical section, ensuring  */
/* mutual exclusion using a semaphore (mutex) for synchronization.             */
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
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MUTEX_INITIAL_VALUE 1  // Initial value for the semaphore (mutex)

int main(int argc, char *argv[]) {
  srand(time(NULL));  // Initialize the random number generator

  // Generate a unique key for the semaphore
  key_t key = 69;
  if (key == -1) {
    perror("Error creating key");
    exit(1);
  }

  // Create the semaphore
  int sem_id = semget(key, 1, IPC_CREAT | 0666);
  if (sem_id == -1) {
    perror("Error creating semaphore");
    exit(1);
  }

  // Initialize the semaphore to 1 (mutex)
  if (semctl(sem_id, 0, SETVAL, MUTEX_INITIAL_VALUE) == -1) {
    perror("Error initializing semaphore");
    exit(1);
  }
  
  int pid = 1;
  struct sembuf lock_op = {0, -1, 0};  // Decrement (lock) operation
  struct sembuf unlock_op = {0, 1, 0};  // Increment (unlock) operation

  // Create 16 child processes
  for (int i = 0; i < 16 && pid > 0; i++) {
    pid = fork();  // Fork a new child process
  }

  if (pid == 0) {  // Child process code
    printf("Initial pid = %d\n", getpid());

    // Enter the critical section (lock the semaphore)
    if (semop(sem_id, &lock_op, 1) == -1) {
      perror("Error locking semaphore");
      exit(1);
    }

    usleep(rand() % 2000000 + 1);  // Sleep for a random amount of time

    // Exit the critical section (unlock the semaphore)
    if (semop(sem_id, &unlock_op, 1) == -1) {
      perror("Error unlocking semaphore");
      exit(1);
    }

    printf("Arrived pid = %d\n", getpid());
    exit(0);  // Terminate the child process
  }

  // Parent process code
  while (wait(NULL) > 0);  // Wait for all child processes to terminate

  // Remove the semaphore
  if (semctl(sem_id, 0, IPC_RMID) == -1) {
    perror("Error removing semaphore");
    exit(1);
  }

  return 0;
}
