/******************************************************************************
/*                                                                            */
/*                          DOG AND OWNER IN GARDEN                           */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This program simulates the interaction between a dog and its owner         */
/* in a garden using threads and semaphores. The dog randomly dirties         */
/* clean spaces, while the owner cleans up the dirty spaces.                  */
/* The program uses POSIX threads and semaphores to synchronize the           */
/* activities and prevent race conditions.                                    */
/*                                                                            */
/*                                                                            */
/* Copyright (c) 2025, Nico Fontani                                           */
/* Creation Date: 01 Apr 2025                                                 */
/*                                                                            */
/* This code was developed by Nico Fontani. Its use and modification are      */
/* permitted, provided that any changes are documented, and the author        */
/* and date are updated to recognize each developer's contribution            */
/* and maintain clear version tracking.                                       */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 01 Apr 2025                                                 */
/*                                                                            */
/******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// Garden structure definition
#define GARDEN_SIZE 10
int garden[GARDEN_SIZE];  // 0 = clean, 1 = dirty

// Semaphores
sem_t sem_dirty_spaces;    // Counts how many spaces are dirty (for the owner)
sem_t sem_clean_spaces;    // Counts how many spaces are clean (for the dog)
sem_t sem_mutex;           // Protects access to the garden

// Thread functions
void* dog_thread(void* arg);
void* owner_thread(void* arg);

// Function to print the garden state
void print_garden() {
    printf("Garden state: ");
    for (int i = 0; i < GARDEN_SIZE; i++) {
        if (garden[i] == 0) {
            printf("🌱 ");  // Clean space
        } else {
            printf("💩 ");  // Dirty space
        }
    }
    printf("\n");
}

// Dog thread
void* dog_thread(void* arg) {
    int dirt_count = *((int*)arg);
    
    for (int i = 0; i < dirt_count; i++) {
        // Wait for at least one clean space
        sem_wait(&sem_clean_spaces);
        
        // Wait a bit before making a mess
        int wait_time = (rand() % 3) + 1;
        printf("The dog is looking for a place to make a mess... (waiting: %d seconds)\n", wait_time);
        sleep(wait_time);
        
        // Protect access to the garden
        sem_wait(&sem_mutex);
        
        // Find a clean space and make it dirty
        int position;
        do {
            position = rand() % GARDEN_SIZE;
        } while (garden[position] != 0);
        
        garden[position] = 1;  // Dirty the space
        printf("The dog has made a mess at position %d!\n", position);
        print_garden();
        
        // Release the mutex
        sem_post(&sem_mutex);
        
        // Signal that there's a new dirty space
        sem_post(&sem_dirty_spaces);
    }
    
    printf("The dog has finished making messes and goes to sleep.\n");
    return NULL;
}

// Owner thread
void* owner_thread(void* arg) {
    int cleaning_count = *((int*)arg);
    
    for (int i = 0; i < cleaning_count; i++) {
        // Wait for at least one dirty space
        sem_wait(&sem_dirty_spaces);
        
        // Wait a bit before cleaning
        int wait_time = (rand() % 2) + 1;
        printf("The owner is looking for a mess to clean... (waiting: %d seconds)\n", wait_time);
        sleep(wait_time);
        
        // Protect access to the garden
        sem_wait(&sem_mutex);
        
        // Find a dirty space and clean it
        int position;
        do {
            position = rand() % GARDEN_SIZE;
        } while (garden[position] != 1);
        
        garden[position] = 0;  // Clean the space
        printf("The owner has cleaned position %d!\n", position);
        print_garden();
        
        // Release the mutex
        sem_post(&sem_mutex);
        
        // Signal that there's a new clean space
        sem_post(&sem_clean_spaces);
    }
    
    printf("The owner has finished cleaning and goes to rest.\n");
    return NULL;
}

int main() {
    pthread_t dog, owner;
    
    // Initialize the random number generator
    srand(time(NULL));
    
    // Initialize the garden (all clean at the beginning)
    for (int i = 0; i < GARDEN_SIZE; i++) {
        garden[i] = 0;
    }
    
    printf("Initial garden state:\n");
    print_garden();
    
    // Initialize semaphores
    sem_init(&sem_dirty_spaces, 0, 0);       // No dirty spaces at the beginning
    sem_init(&sem_clean_spaces, 0, GARDEN_SIZE); // All spaces are clean at the beginning
    sem_init(&sem_mutex, 0, 1);              // Mutex initially unlocked
    
    // How many actions to perform
    int dirt_count = 8;
    int cleaning_count = 8;
    
    // Create threads
    pthread_create(&dog, NULL, dog_thread, &dirt_count);
    pthread_create(&owner, NULL, owner_thread, &cleaning_count);
    
    // Wait for threads to complete
    pthread_join(dog, NULL);
    pthread_join(owner, NULL);
    
    // Destroy semaphores
    sem_destroy(&sem_dirty_spaces);
    sem_destroy(&sem_clean_spaces);
    sem_destroy(&sem_mutex);
    
    printf("Simulation completed!\n");
    return 0;
}