/******************************************************************************/ 
/*                                                                            */
/*                             Memory Management Utility                      */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This library provides utility functions for safe dynamic memory            */
/* management. It includes functions for allocating, reallocating, and        */
/* freeing memory with error handling. It logs memory allocation failures     */
/* and tracks memory usage to help debug memory leaks.                        */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 13 Nov 2024                                                 */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/* Supported by GCC and C99                                                   */
/*                                                                            */
/******************************************************************************/ 

#include "memutil.h"

// Memory usage tracker
static size_t total_allocated_memory = 0;

// Function to safely allocate memory
void* mem_alloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed. Requested size: %zu bytes\n", size);
        exit(EXIT_FAILURE);  // Exit if allocation fails
    }
    
    total_allocated_memory += size;
    printf("Allocated %zu bytes, Total memory: %zu bytes\n", size, total_allocated_memory);
    return ptr;
}

// Function to safely reallocate memory
void* mem_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "ERROR: Memory reallocation failed. Requested size: %zu bytes\n", size);
        exit(EXIT_FAILURE);  // Exit if reallocation fails
    }
    
    // Adjust memory usage tracker
    total_allocated_memory += size;
    printf("Reallocated memory to %zu bytes, Total memory: %zu bytes\n", size, total_allocated_memory);
    return new_ptr;
}

// Function to safely free memory
void mem_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
        printf("Memory freed successfully.\n");
    } else {
        printf("ERROR: Attempted to free a NULL pointer!\n");
    }
}

// Function to log current memory usage
void log_memory_usage(void) {
    printf("Total allocated memory: %zu bytes\n", total_allocated_memory);
}
