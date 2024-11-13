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
/* Creation Date: 11 Nov 2024                                                 */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/* Supported by C Programming                                                 */
/*                                                                            */
/******************************************************************************/

#include "objutil.h"

/* Initialize an object (like a constructor) */
void obj_init(Object* obj, const char* name) {
    obj->name = strdup(name);  /* Dynamically allocate memory for name */
    obj->num_attributes = 0;   /* Initialize number of attributes */
    for (int i = 0; i < MAX_ATTRIBUTES; i++) {
        obj->attributes[i] = 0; /* Initialize all attributes to 0 */
    }
}

/* Set an attribute value for an object */
void obj_set_attribute(Object* obj, int index, int value) {
    if (index >= 0 && index < MAX_ATTRIBUTES) {
        obj->attributes[index] = value;
        if (index >= obj->num_attributes) {
            obj->num_attributes = index + 1; /* Update num_attributes */
        }
    }
}

/* Get an attribute value from an object */
int obj_get_attribute(Object* obj, int index) {
    if (index >= 0 && index < obj->num_attributes) {
        return obj->attributes[index];
    }
    return -1; /* Return -1 if index is invalid */
}

/* Print the object's details */
void obj_print(Object* obj) {
    printf("Object: %s\n", obj->name);
    printf("Attributes:\n");
    for (int i = 0; i < obj->num_attributes; i++) {
        printf("  Attribute %d: %d\n", i, obj->attributes[i]);
    }
}
