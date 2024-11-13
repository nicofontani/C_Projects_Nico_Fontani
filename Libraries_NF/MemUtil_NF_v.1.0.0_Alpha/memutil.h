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

#ifndef MEMUTIL_H
#define MEMUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Memory tracking structure
typedef struct {
    void* address;
    size_t size;
} MemoryBlock;

// Function to safely allocate memory and log errors
void* mem_alloc(size_t size);

// Function to safely reallocate memory and log errors
void* mem_realloc(void* ptr, size_t size);

// Function to safely free memory and log errors
void mem_free(void* ptr);

// Function to log the current memory usage
void log_memory_usage(void);

#endif // MEMUTIL_H
