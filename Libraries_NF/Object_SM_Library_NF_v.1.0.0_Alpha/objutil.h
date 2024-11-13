/******************************************************************************/
/*                                                                            */
/*                    Object Simulation Library in C                          */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This library simulates objects and classes in C. It provides an approach   */
/* for managing attributes and methods for data structures, mimicking object  */
/* orientation in C.                                                          */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 10 Nov 2024                                                 */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/* Supported by C Programming                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef OBJUTIL_H
#define OBJUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define a macro for the maximum number of attributes per object */
#define MAX_ATTRIBUTES 10

/* Structure to simulate a class in C */
typedef struct {
    char* name;
    int attributes[MAX_ATTRIBUTES]; /* Example: integers as attributes */
    int num_attributes;
} Object;

/* Function prototypes */

/* Initialize an object (like a constructor) */
void obj_init(Object* obj, const char* name);

/* Set an attribute value for an object */
void obj_set_attribute(Object* obj, int index, int value);

/* Get an attribute value from an object */
int obj_get_attribute(Object* obj, int index);

/* Print the object's details */
void obj_print(Object* obj);

#endif /* OBJUTIL_H */
